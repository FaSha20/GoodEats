#ifndef _USERS_H
#define _USERS_H

#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <algorithm>
#include "recipes.hpp"
#include "users.hpp"
#include "my_errors.hpp"
#include "finder.hpp"
#include "sort.hpp"


#define IN_ACCESSIBLE -1
#define RECIPES_ID 1
#define RATING 0
#define CONFIRMED "OK"

using namespace std;
class Recipe;class Shelf;class Offer;class Order;
enum user_type{chef,common_user,supplier};

class User{
public:
    User(string name = " ",string pas = " ")
    {username = name,password = pas,credit = 0.0;};
    virtual string get_name(){return username;};
    string get_password(){return password;};
    user_type get_type(){return type;};
    int get_id(){return id;};
    virtual string get_email(){return username;};
    int get_credit(){return static_cast<int>(credit);};
    void add_credit(double how_much){credit += how_much;};
    friend class DataBase;
protected:
    string username;
    string password;
    user_type type;
    int id;
    double credit;
};


class Chef : public User{
public:
    Chef(string name,string pas):User(name,pas)
    {sum_of_rates = 0,type = chef;};
    void add_rate(int how_much){sum_of_rates += how_much;};
    double claculate_final_rate(vector<shared_ptr<Recipe>> recipes);
    double get_rate(){return sum_of_rates;};
    void add_to_my_recipes(shared_ptr<Recipe> new_r){my_recipes.push_back(new_r);};
    void delete_recipe(int recipe_id);
    vector <string> get_recipes();
    string get_properties_in_line(vector<shared_ptr<Recipe>> recipes);
    string get_compelet_properties(vector<shared_ptr<Recipe>> recipes);
    string show_all_recipes_in_line();
private:
    vector<shared_ptr<Recipe>> my_recipes;
    int sum_of_rates;
};


class Common : public User{
public:
    Common(string name,string pas):User(name,pas){type = common_user;};
    void add_to_my_shelves(shared_ptr<Shelf> sh){my_shelves.push_back(sh);};
    void add_recipe_to_shelf(int shelf_id,shared_ptr<Recipe>& recipe);
    void remove_recipe_from_shelf(int shelf_id,int recipe_id);
    void remove_shelf(int shelf_id);
    string get_properties_in_line();
    bool have_already_rated_this_recipe(double recipe_id);
    double change_ratetorecipe_pair(double rate,double r_id);
    void add_new_ratetorecipe_pair(double rate,double r_id)
        {my_ratings_to_recipes.push_back({rate,r_id});};
    string show_shelves_upto(int limit);
    vector<string> show_shelves();
    void add_order_text(string ord){my_orders_text.push_back(ord);};
    vector<string> get_orders_text(){return my_orders_text;};
    
private:
    vector<string> my_orders_text;
    vector<shared_ptr<Shelf>> my_shelves;
    vector<vector<double>> my_ratings_to_recipes;
};


string show_all_chefs(vector<shared_ptr<Chef>>& chefs,vector<shared_ptr<Recipe>> recipes);
string show_all_common_users(vector<shared_ptr<Common>>& commons,
    shared_ptr<Common> active_common);

typedef shared_ptr<Chef> PChef;
typedef vector<shared_ptr<Chef>> ChefList;
typedef shared_ptr<Common> PCommon;
typedef vector<shared_ptr<Common>> CommonList;

#endif //_USERS_H