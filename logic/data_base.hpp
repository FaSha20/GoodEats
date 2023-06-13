#ifndef _DATA_H
#define _DATA_H

#include <iostream>
#include <map>
#include "managers.hpp"
#include <fstream>
using namespace std;

class DataBase{
public:
    int add_user(string type,string username,string password);
    int find_user_id(string username,string password);
    bool is_unique(string username);
    map <int,shared_ptr<User>> user_id_map;
    vector<shared_ptr<User>> all_users;
    CommonList commons;
    ChefList chefs;
    SupplierList suppliers;
    RecipeList recipes;
    ShelfList shelves;
    ofstream outfile;
    
};



#endif //_DATA_H