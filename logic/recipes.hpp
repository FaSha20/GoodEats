
#ifndef _RECIPES_H
#define _RECIPES_H

#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <sstream>
#include "users.hpp"
#include "recipes.hpp"
#include "my_errors.hpp"
#include "sort.hpp"
#include "finder.hpp"

using namespace std;
class Chef;class Common;class User;class Ingredient;class Offer;

class Recipe{
public:
    Recipe(string tl,string ingreds,string veg,string min,string _tags,string img,shared_ptr<Chef>& _my_chef,int _id_number);
    Recipe(string recipe_data,shared_ptr<Chef>& _my_chef,int _id_number);
    int get_id(){return id_number;};
    string get_name(){return title;};
    void add_rate(double how_much); 
    double get_rate(){return rate;};
    vector <string> get_ingredients(){return ingredients;};
    string get_compelet_properties();
    string get_properties_in_line();
private:
    shared_ptr<Chef> my_chef;
    string title;
    vector <string> ingredients;
    string vegetarian;
    string minutes_to_ready;
    vector <string> tags;
    string image_address;
    double rate;
    int id_number;
};


class Shelf{
public:
    Shelf(string name_,int id){name = name_,id_number = id;};
    void delete_recipe(int recipe_id);
    void add_recipe(shared_ptr<Recipe> new_recipe){my_recipes.push_back(new_recipe);};
    int get_id(){return id_number;};
    string get_name(){return name;};
    string get_properties_in_line();
    string get_compelet_properties();
    void add_to_recipes(string recipes);
private:
    string name;
    vector<shared_ptr<Recipe>> my_recipes;
    int id_number;
};

string show_all_recipes(vector<shared_ptr<Recipe>> recipes);
string show_user_shelves_upto(string username,int limit,
    vector<shared_ptr<Common>> commons);

typedef shared_ptr<Recipe> PRecipe;
typedef vector<shared_ptr<Recipe>> RecipeList;
typedef shared_ptr<Shelf> PShelf;
typedef vector<shared_ptr<Shelf>> ShelfList;

#endif //_RECIPES_H