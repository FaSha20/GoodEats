#include "command_checking.hpp"


void Chef_command_checking::post_recipe()
{
    int new_id = recipes.size() + 1;
    PRecipe new_recipe = make_shared<Recipe>
        (remained_data,active_user, new_id);
    active_user->add_to_my_recipes(new_recipe);
    recipes.push_back(new_recipe);
    out_put = to_string(new_id);
}

void Chef_command_checking::delete_recipe()
{
    char id[4];string command;
    stringstream r_data_buf(remained_data);
    r_data_buf >> command >> id;
    int index = find_index_by_id(atoi(id),recipes);
    if(index == IN_ACCESSIBLE)
        throw Permission_err();
    active_user->delete_recipe(atoi(id));
    recipes.erase(recipes.begin() + index);
    out_put = CONFIRMED;
}

void Common_command_checking::post_rate()
{
    char recipe_id[10], score[10];
    stringstream r_data_buf(remained_data);
    r_data_buf >> command >> recipe_id >> command >> score;
    int r_id = atoi(recipe_id);int rate = atoi(score);
    if(active_user->have_already_rated_this_recipe(r_id))
        throw Bad_request_err();
    index = find_index_by_id(r_id,recipes);
    if(index == IN_ACCESSIBLE)
        throw Not_found_err();
    recipes[index]->add_rate(rate);
    active_user->add_new_ratetorecipe_pair(rate,r_id);
    out_put = CONFIRMED;
}

void Common_command_checking::put_rate()
{
    char recipe_id[10], score[10];
    stringstream r_data_buf(remained_data);
    r_data_buf >> command >> recipe_id >> command >> score;
    int r_id = atoi(recipe_id);int rate = atoi(score);
    if(! active_user->have_already_rated_this_recipe(r_id))
        throw Bad_request_err();
    index = find_index_by_id(r_id,recipes);
    if(index == IN_ACCESSIBLE)
        throw Not_found_err();
    int how_much_more_add_to_rate = active_user->
        change_ratetorecipe_pair(rate,r_id);
    recipes[index]->add_rate(how_much_more_add_to_rate);
    out_put = CONFIRMED;
}

void Common_command_checking::get_recipes()
{
    char recipe_id[10];
    stringstream r_data_buf(remained_data);
    r_data_buf >> command >> recipe_id;
    index = find_index_by_id(atoi(recipe_id),recipes);
    if(index == IN_ACCESSIBLE)
        throw Not_found_err();
    out_put = recipes[index]->get_compelet_properties();
}

void Common_command_checking::get_chefs()
{
    stringstream r_data_buf(remained_data);
    string chef_username;
    r_data_buf >> command >> chef_username;
    index = find_index_by_username(chef_username,chefs);
    if(index == IN_ACCESSIBLE)
        throw Not_found_err();
    out_put = chefs[index]->get_compelet_properties(recipes);
}

void Common_command_checking::post_shelves()
{
    stringstream r_data_buf(remained_data);
    string shelf_name;
    r_data_buf >> command >> shelf_name;
    int new_id = shelves.size() + 1;
    PShelf new_shelf = make_shared<Shelf>(shelf_name,new_id);
    active_user->add_to_my_shelves(new_shelf);
    shelves.push_back(new_shelf);
    out_put = to_string(new_id);
}

void Common_command_checking::get_shelves(CommonList& commons)
{
    stringstream r_data_buf(remained_data);
    string username;char limit[4];
    r_data_buf >> command >> username >> command >> limit;
    out_put = show_user_shelves_upto(username,atoi(limit),commons);
}

void Common_command_checking::put_shelves_recipes()
{
    stringstream r_data_buf(remained_data);
    char recipe_id[4],shelf_id[4];
    r_data_buf >> command >> shelf_id >> command >> recipe_id;
    int r_id = atoi(recipe_id);int sh_id = atoi(shelf_id); 
    int recipe_inedx = find_index_by_id(r_id,recipes);
    int shelf_inedx = find_index_by_id(sh_id,shelves);
    if(recipe_inedx == IN_ACCESSIBLE || shelf_inedx == IN_ACCESSIBLE)
        throw Not_found_err();
    active_user->add_recipe_to_shelf(sh_id,recipes[recipe_inedx]);
    out_put = CONFIRMED;
}

void Common_command_checking::delete_shelves_recipes()
{
    stringstream r_data_buf(remained_data);
    char recipe_id[4],shelf_id[4];
    r_data_buf >> command >> shelf_id >> command >> recipe_id;
    int r_id = atoi(recipe_id);int sh_id = atoi(shelf_id); 
    active_user->remove_recipe_from_shelf(sh_id,r_id);
    out_put = CONFIRMED;
}

void Common_command_checking::get_shelves_recipes()
{
    stringstream r_data_buf(remained_data);
    int shelf_index;char shelf_id[4];
    r_data_buf >> command >> shelf_id ;
    shelf_index = find_index_by_id(atoi(shelf_id),shelves);
    if(shelf_index == IN_ACCESSIBLE )
        throw Not_found_err();
    out_put = shelves[shelf_index]->get_compelet_properties();
}

void Common_command_checking::put_credit()
{
    stringstream r_data_buf(remained_data);
    double how_much_money;
    r_data_buf >> command >> how_much_money;
    active_user->add_credit(how_much_money);
    out_put = CONFIRMED;
}

IngredList extract_available_ingreds(IngredList offered,vector<string> ingreds)
{
    int counter = 0,index;
    IngredList of_list = offered;
    vector<shared_ptr<Ingredient>> wanted_ingreds;
    for(string ingredient_name : ingreds){
        while(find_by_name(ingredient_name,of_list)){
            index = find_index_by_username(ingredient_name,of_list);
            wanted_ingreds.push_back(of_list[index]);
            of_list.erase(of_list.begin() + index);
            counter++;
        }
        if(counter == 0)
            throw Not_found_err();
    }
    return wanted_ingreds;
}

void Common_command_checking::post_order
    (IngredList& offered_ingredients,OfferList& offers)
{
    stringstream r_data_buf(remained_data);ostringstream os;
    IngredList wanted_ingreds;
    int recipe_id;
    r_data_buf >> command >> recipe_id;
    PRecipe found_recipe = find_by_id(recipe_id,recipes);
    wanted_ingreds = extract_available_ingreds(offered_ingredients,
        found_recipe->get_ingredients());
    POrder final_order = make_shared<Order>(wanted_ingreds);
    if(final_order->is_too_expensive_for(active_user))
        throw Bad_request_err();
    final_order->make(offers);
    out_put = final_order->to_string(); 
    os << recipe_id << endl << out_put;
    active_user->add_order_text(os.str());
}

void Common_command_checking::get_orders()
{
    vector<string> orders = active_user->get_orders_text();
    ostringstream out;
    for(int i = 0; i < orders.size(); i++){
        out << "====" << "order_" << i + 1 << "====" << endl;
        out << orders[i];
        if(i != orders.size() - 1)
            out << endl;
    }
    out_put = out.str();
}

void Supplier_command_checking::post_offer(IngredList& ingredients)
{
    stringstream r_data_buf(remained_data);
    string ingred_name;
    PIngredient found_ingred;
    double price,count,packaging;
    r_data_buf >> command >> ingred_name >> command >> price
               >> command >> count >> command >> packaging;
    if(active_user->find_offer(ingred_name))
        throw Bad_request_err();
    POffer new_offer = make_shared<Offer>
        (ingred_name,active_user,price,count,packaging);
    if(found_ingred = find_by_name(ingred_name,ingredients)){
        found_ingred->add_offer(new_offer);
    }
    else{
        PIngredient new_ingredient = make_shared<Ingredient>(ingred_name);
        new_ingredient->add_offer(new_offer);
        ingredients.push_back(new_ingredient);
    }
    active_user->add_offer(new_offer);
    offers.push_back(new_offer);
    out_put = CONFIRMED;
}

void Supplier_command_checking::put_offer()
{
    stringstream r_data_buf(remained_data);
    string ingred_name;
    double price,count;
    r_data_buf >> command >> ingred_name >> command >> price
               >> command >> count;
    POffer found_offer = active_user->find_offer(ingred_name);
    if(found_offer)
        found_offer->change_prices(price,count);
    else
        throw Not_found_err();
    out_put = CONFIRMED;
}

void Supplier_command_checking::delete_offer()
{
    stringstream r_data_buf(remained_data);
    string ingred_name;
    r_data_buf >> command >> ingred_name ;
    active_user->delete_offer(ingred_name);
    int index = find_index_by_username(ingred_name,offers);

    offers.erase(offers.begin() + index);
    out_put = CONFIRMED;
}