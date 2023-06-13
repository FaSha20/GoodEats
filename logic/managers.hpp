#ifndef _MANAGERS_H
#define _MANAGERS_H


#include "managers.hpp"
#include "users.hpp"
#include "recipes.hpp"
#include "my_errors.hpp"
#include "finder.hpp"
#include "ingredients.hpp"


using namespace std;


template <typename T>
class Manager{
public:
    Manager(){active_user = NULL;};
    void set_active_user(T user){active_user = user;};
    bool has_active_user(){return (active_user) ? true : false;};
    virtual void add_user(T new_user){user_list.push_back(new_user);};
    T find_by_username(string username)
        {return find_user(username,user_list);};
protected:
    vector <T> user_list;
    T active_user;
};

class Chef_manager : public Manager<PChef>{
public:
    Chef_manager():Manager(){};
    ChefList& get_chefs_list(){return user_list;};
    void check_command(string per_command,stringstream& data_buf,
        RecipeList& recipes,string& out_put);    
};


class Common_user_manager : public Manager<PCommon>{
public:
    Common_user_manager():Manager(){};
    void check_command(string per_command,stringstream& data_buf,
        RecipeList& recipes,ChefList& chefs,IngredList& ingreds,
        OfferList& offers,string& out_put);
private:
    ShelfList shelves;
};

class Supplier_manager : public Manager<PSupplier>{
public:
    Supplier_manager():Manager(){};
    void add_user(PSupplier new_sup);
    PSupplier find_by_email(string email)
        {return find_sup(email,user_list);};
    IngredList& get_ingredients_list(){return offered_ingredients;};
    OfferList& get_offer_list(){return all_offers;};
    void check_command(string per_command,stringstream& data_buf,
       RecipeList& recipes,string& out_put);
private:
    OfferList all_offers;
    IngredList offered_ingredients;
};

#endif //_MANAGERS_H