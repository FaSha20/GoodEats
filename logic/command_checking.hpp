#ifndef _COMMAND_CHECKING
#define _COMMAND_CHECKING

#include "users.hpp"
#include "recipes.hpp"
#include "ingredients.hpp"
#include "orders.hpp"
#include "command_checking.hpp"

using namespace std;

template<typename T>
class Command_checking{
public:
    Command_checking(string data,vector<shared_ptr<Recipe>>r,T active)
    {remained_data = data, recipes = r ,active_user = active;};
    string get_out_put(){return out_put;};
    vector<shared_ptr<Recipe>> update_recipes(){return recipes;};
    T update_active_user(){return active_user;};
    void post_logout(){active_user = NULL; out_put = CONFIRMED;} 
protected:
    string remained_data;
    vector<shared_ptr<Recipe>> recipes;
    string out_put;
    T active_user;
};

class Chef_command_checking : public Command_checking<PChef>{
public:
    Chef_command_checking(string data,vector<shared_ptr<Recipe>> r,PChef active)
        : Command_checking(data,r,active){};
    void post_recipe();
    void delete_recipe();
    void get_my_recipes(){out_put = active_user->get_recipes();};   
};

class Common_command_checking : public Command_checking<PCommon>{
public:
    Common_command_checking(string data,vector<shared_ptr<Recipe>> r,PCommon active
        ,vector<shared_ptr<Chef>> ch,vector<shared_ptr<Shelf>> sh): Command_checking(data,r,active)
        {shelves = sh, chefs = ch;};
    ChefList update_chefs(){return chefs;};
    ShelfList update_shelves(){return shelves;};
    void post_rate();
    void put_rate();
    void get_recipes();
    void get_chefs();
    void post_shelves();
    void get_shelves(vector<shared_ptr<Common>>& commons);
    void put_shelves_recipes();
    void delete_shelves_recipes();
    void put_credit();
    void post_order(IngredList& offerd_ingred,OfferList& offers);
    void get_shelves_recipes();
    void get_complete_reicpes(){out_put = show_all_recipes(recipes);};
    void get_complete_chefs(){out_put = show_all_chefs(chefs,recipes);};
    void get_complete_users(vector<shared_ptr<Common>> commons)
        {out_put = show_all_common_users(commons,active_user);};
    void get_credit(){out_put = to_string(active_user->get_credit());};
    void get_orders();
private:
    vector<shared_ptr<Chef>> chefs;
    vector<shared_ptr<Shelf>> shelves;
    string command;
    int index;
};

class Supplier_command_checking : public Command_checking<PSupplier>{
public:
    Supplier_command_checking(string d,vector<shared_ptr<Recipe>> r,shared_ptr<Supplier> ac,vector<shared_ptr<Offer>> of)
        :Command_checking(d,r,ac)
        {offers = of;};
    void post_offer(vector<shared_ptr<Ingredient>>& ingredients);
    void put_offer();
    void delete_offer();
    void get_credit(){out_put = to_string(active_user->get_credit());};
    vector<shared_ptr<Offer>> update_offers_list(){return offers;};
private:
    vector<shared_ptr<Offer>> offers;
    string command;
    int index;
};

#endif // COMMAND_CHECKING