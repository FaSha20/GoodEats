#include "recipes.hpp"
#include <cstring>
#include <limits>
using namespace std;

Recipe ::Recipe(string recipe_data,shared_ptr<Chef>& _my_chef,int _id_num)
{
    rate = 0.0;
    my_chef = _my_chef;
    id_number = _id_num;
    string ingredients_,tags_,token,command_word;
    stringstream data(recipe_data);
    data >> command_word >> title >> 
            command_word >> ingredients_ >> 
            command_word >> vegetarian >>
            command_word >> minutes_to_ready >> 
            command_word >> tags_ >> 
            command_word >> image_address;
    stringstream stream(ingredients_),stream2(tags_);
    while (getline(stream,token,','))
        ingredients.push_back(token);
    
    while (getline(stream2,token,','))
        tags.push_back(token);
    
}

Recipe::Recipe(string tl,string ingreds,string veg,string min,
    string _tags,string img,shared_ptr<Chef>& _my_chef,int _id_num)
{
    rate = 0.0;my_chef = _my_chef;id_number = _id_num;
    title = tl;vegetarian = veg;minutes_to_ready = min;
    image_address = img;
    string token;
    stringstream stream(ingreds),stream2(_tags);
    while (getline(stream,token,','))
        ingredients.push_back(token);
    
    while (getline(stream2,token,','))
        tags.push_back(token);
}

string to_string(vector<string> vec)
{
    ostringstream os;
    for(int i = 0; i < vec.size() ; i++){
            os << vec[i];
        if( i != vec.size() - 1)
            os << ", ";
    }
    return os.str();  
}

void Recipe::add_rate(double how_much)
{
    rate += how_much;
    my_chef->add_rate(how_much);
}

string Recipe::get_compelet_properties()
{
    ostringstream properties;
    properties.precision(1);
    properties << "ID : " << to_string(id_number) << "<br />" 
               << "Title : " << title << "<br />"
               << "vegetarian : " << vegetarian << "<br />"
               << "ingredients : " << to_string(ingredients) << "<br />"
               << "minutes to ready : " << minutes_to_ready << "<br />"
               << "tags : " << to_string(tags)  << "<br />"
               << "rating :" << fixed << rate;
    return properties.str();
}

string Recipe::get_properties_in_line()
{
    ostringstream properties;
    properties << "ID : " << to_string(id_number) << "    #      " 
               << "Title : " << title << "   #    " << "<br />"
               << "vegetarian : " << vegetarian << "     #    "
               << "minutes to ready : " << minutes_to_ready << "<br />";
    return properties.str();
}

void Shelf::delete_recipe(int recipe_id)
{
    int recipe_index = find_index_by_id(recipe_id,my_recipes);
    if(recipe_index == IN_ACCESSIBLE)
        throw Bad_request_err();
    else
        my_recipes.erase(my_recipes.begin() + recipe_index);    
}

string Shelf::get_properties_in_line()
{
    ostringstream data;
    data << "ID : " << id_number << "<br />" 
            "Title : " << name;
    return data.str();
}



string Shelf::get_compelet_properties()
{
    ostringstream shelf_data;
    if(my_recipes.size() == 0)
        return "Empty";
    shelf_data << get_properties_in_line() << "<br />";
    shelf_data << "Recipes : "<< "<br />";
    for(int r = 0 ;r < my_recipes.size();r++){
        shelf_data<< my_recipes[r]->get_properties_in_line() << "<br />";        
    }
    return shelf_data.str();
}

string show_all_recipes(vector<shared_ptr<Recipe>> recipes)
{
    ostringstream all_recipes;
    if(recipes.size() == 0)
        return "Empty";
    lexicographicalize(recipes);
    for(int r = 0; r < recipes.size();r++){
        all_recipes << recipes[r]->get_properties_in_line();
        if(r != recipes.size() - 1)
            all_recipes << endl;
    }
    return all_recipes.str();
}

string show_user_shelves_upto(string username,int limit,
    vector<shared_ptr<Common>> commons)
{
    int index = find_index_by_username(username,commons);
    if(index == IN_ACCESSIBLE)
        throw Bad_request_err();
    return commons[index]->show_shelves_upto(limit);
}

