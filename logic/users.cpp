#include "users.hpp"


void Chef::delete_recipe(int recipe_id)
{
    int index = find_index_by_id(recipe_id,my_recipes);
    my_recipes.erase(my_recipes.begin() + index);
}

double Chef::claculate_final_rate(vector<shared_ptr<Recipe>> recipes)
{
    int size = 0;
    for(int i = 0 ;i< my_recipes.size();i++){
        int index = find_index_by_id(my_recipes[i]->get_id(),recipes);
        if(recipes[index]->get_rate() != 0)
            size++;
    }
    if(my_recipes.size() == 0)
        return 0.0;
    else
        return sum_of_rates/size;
}

vector<string> Chef::get_recipes()
{
    vector<string> recipe_data_list;
    for(int r = 0; r < my_recipes.size(); r++){
        recipe_data_list.push_back(my_recipes[r]->get_compelet_properties());
    }   
    return recipe_data_list;
}

string Chef::get_properties_in_line(vector<shared_ptr<Recipe>> recipes)
{
    ostringstream properties;
    properties.precision(1);
    properties << username << " " << fixed << claculate_final_rate(recipes) ; 
    return properties.str();
}

string Chef::show_all_recipes_in_line()
{
    ostringstream os;
    os.precision(1);
    for(int r = 0; r < my_recipes.size();r++){
        os << my_recipes[r]->get_properties_in_line()  
           << " " << fixed << my_recipes[r]->get_rate();
        if(r != my_recipes.size() - 1)
            os << endl;
    }
    return os.str();
}

string Chef::get_compelet_properties(vector<shared_ptr<Recipe>> recipes)
{
    ostringstream properties;
    properties.precision(1);
    properties << username << endl 
               << fixed << claculate_final_rate(recipes) << endl
               << "recipes:" << endl
               << show_all_recipes_in_line(); 
    return properties.str();
}

string Common::get_properties_in_line()
{
    ostringstream properties;
    properties << username << endl; 
    return properties.str();
}

void Common::add_recipe_to_shelf(int shelf_id,shared_ptr<Recipe>& recipe)
{
    int shelf_index = find_index_by_id(shelf_id,my_shelves);
    if(shelf_index == IN_ACCESSIBLE)
        throw Permission_err();
    my_shelves[shelf_index]->add_recipe(recipe);    
}

void Common::remove_recipe_from_shelf(int shelf_id,int recipe_id)
{
    for( int i = 0;i < my_shelves.size();i++){
        if(my_shelves[i]->get_id() == shelf_id){
            my_shelves[i]->delete_recipe(recipe_id);
            return;
        }
    }
    throw Permission_err();
}

bool Common::have_already_rated_this_recipe(double recipe_id)
{
    for(auto pair : my_ratings_to_recipes){
        if(pair[RECIPES_ID] == recipe_id )
            return true;
    }   
    return false;
}

double Common::change_ratetorecipe_pair(double new_rate,double r_id)
{
    double difference_between_rates;
    for(int pair = 0; pair < my_ratings_to_recipes.size(); pair++){
        if(my_ratings_to_recipes[pair][RECIPES_ID] == r_id){
            difference_between_rates = new_rate - my_ratings_to_recipes[pair][RATING];
            return difference_between_rates;
        }
    }
    return 0.0;
} 

int find_minimum(int x,int y)
{
    if(x < y) return x;
    else      return y; 
}

string Common::show_shelves_upto(int limit)
{
    ostringstream shelves_data;
    if(my_shelves.size() == 0)
        return "Empty";
    int min = find_minimum(limit,my_shelves.size());
    for(int sh = 0; sh < min; sh++){
        shelves_data << my_shelves[sh]->get_properties_in_line();
        if(sh != min - 1)
            shelves_data << endl;
    }
    return shelves_data.str();
}

vector<string> Common::show_shelves()
{
    vector<string> shelf_data_list;
    for(int r = 0; r < my_shelves.size(); r++){
        shelf_data_list.push_back(my_shelves[r]->get_properties_in_line());
    }   
    return shelf_data_list;
}

void Common::remove_shelf(int shelf_id)
{
    int index = find_index_by_id(shelf_id,my_shelves);
    if(index == IN_ACCESSIBLE)
        throw Not_found_err();
    my_shelves.erase(my_shelves.begin() + index);
}

string show_all_chefs(vector<shared_ptr<Chef>>& chefs,vector<shared_ptr<Recipe>> recipes)
{
    ostringstream all_chefs;
    if(chefs.size() == 0)
        throw Permission_err("EMPTY");
    lexicographicalize(chefs);
    for(int c = 0 ;c < chefs.size();c++){
        all_chefs << chefs[c]->get_properties_in_line(recipes) ;
        if(c!= chefs.size() - 1)
            all_chefs << endl;
    }
    return all_chefs.str();
}

string show_all_common_users(vector<shared_ptr<Common>>& commons
    ,shared_ptr<Common> active_common)
{
    ostringstream all_commons;
    commons.erase(remove(commons.begin(),commons.end(),active_common)
        ,commons.end());
    if(commons.size() == 0)
        throw Permission_err("EMPTY");
    lexicographicalize(commons);
    for(auto common : commons)
        all_commons << common->get_properties_in_line() ;
    return all_commons.str();
}

