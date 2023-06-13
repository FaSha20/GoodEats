#include "managers.hpp"
#include "command_checking.hpp"

bool is_question_mark(string s)
{
    if(s == "?") return true;
    else return false;
}

void Supplier_manager :: add_user(PSupplier new_sup)
{
    for(PSupplier sup : user_list)
        if(sup->get_email() == new_sup->get_email())
            throw Bad_request_err();
    user_list.push_back(new_sup);
}

void Chef_manager::check_command(string per_command,
    stringstream& data_buf,RecipeList& recipes,string& out_put)
{
    string command,ques_mark,next_command;
    ostringstream remained_buf;
    data_buf >> command >> next_command;
    remained_buf << data_buf.rdbuf();
    Chef_command_checking check(remained_buf.str(),recipes,active_user);

    if(is_question_mark(next_command)){
        if(per_command == "POST" && command == "recipes")
            check.post_recipe();
        else if(per_command == "DELETE" && command == "recipes")
            check.delete_recipe();
        else throw Permission_err();
    }
    else{
        if(per_command == "GET" && command == "my_recipes")
            check.get_my_recipes();
        else if(per_command == "POST" && command == "logout")
            check.post_logout();
        else throw Permission_err();
    }
    active_user = check.update_active_user();
    recipes = check.update_recipes();
    out_put = check.get_out_put();
}

void Common_user_manager::check_command(string per_command,stringstream&
     data_buf,RecipeList& recipes,ChefList& chefs,IngredList& ingreds,
     OfferList& offers,string& out_put)
{
    string command,ques_mark,next_command;
    ostringstream remained_buf;
    data_buf >> command >> next_command;
    remained_buf << data_buf.rdbuf();
    Common_command_checking check(remained_buf.str(),recipes,
        active_user,chefs,shelves);
    if(is_question_mark(next_command)){
        if(per_command == "POST" && command == "rates")
            check.post_rate();
        else if(per_command == "PUT" && command == "rates")
            check.put_rate();
        else if(per_command == "GET" && command == "recipes")
            check.get_recipes();
        else if(per_command == "GET" && command == "chefs")
            check.get_chefs();
        else if(per_command == "POST" && command == "shelves")
            check.post_shelves();
        else if(per_command == "GET" && command == "shelves")
            check.get_shelves(user_list);
        else if(per_command == "PUT" && command == "shelves_recipes")
            check.put_shelves_recipes();
        else if(per_command == "DELETE" && command == "shelves_recipes")
            check.delete_shelves_recipes();
        else if(per_command == "GET" && command == "shelves_recipes")
            check.get_shelves_recipes();
        else if(per_command == "PUT" && command == "credits")
            check.put_credit();
        else if(per_command == "POST" && command == "orders")
            check.post_order(ingreds,offers);
        else throw Permission_err();
    }
    else{
        if(per_command == "GET" && command == "recipes")
            check.get_complete_reicpes();
        else if(per_command == "GET" && command == "chefs")
            check.get_complete_chefs();
        else if(per_command == "GET" && command == "users")
            check.get_complete_users(user_list);
        else if(per_command == "GET" && command == "credits")
            check.get_credit();
        else if(per_command == "GET" && command == "orders")
            check.get_orders();
        else if(per_command == "POST" && command == "logout")
            check.post_logout();
        else throw Permission_err();
    }
    out_put = check.get_out_put();
    recipes = check.update_recipes();
    chefs = check.update_chefs();
    shelves = check.update_shelves();
    active_user = check.update_active_user();
}

void Supplier_manager::check_command(string per_command,stringstream&
     data_buf,RecipeList& recipes,string& out_put)
{
    string command,ques_mark,next_command;
    ostringstream remained_buf;
    data_buf >> command >> next_command;
    remained_buf << data_buf.rdbuf();
    Supplier_command_checking check(remained_buf.str(),recipes,
        active_user,all_offers);

    if(is_question_mark(next_command)){
        if(per_command == "POST" && command == "offers")
            check.post_offer(offered_ingredients);
        else if(per_command == "PUT" && command == "offers")
            check.put_offer();
        else if(per_command == "DELETE" && command == "offers")
            check.delete_offer();            
        else throw Permission_err();
    }
    else 
        if(per_command == "POST" && command == "logout")
            check.post_logout();
        if(per_command == "GET" && command == "credits")
            check.get_credit();
    active_user = check.update_active_user();
    recipes = check.update_recipes();
    all_offers = check.update_offers_list();
    out_put = check.get_out_put();
}