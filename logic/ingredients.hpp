#ifndef _INGREDIENTS_H
#define _INGREDIENTS_H

#include "ingredients.hpp"
#include "users.hpp"
#include "supplier.hpp"
using namespace std;
class Supplier;class Order;class OrderLine;

class Offer{
public:
    Offer(string ingrd_name,shared_ptr<Supplier> of,double p,int c,double pp);
    string get_name(){return ingred_name;};
    void change_prices(double p,int c){price = p, count = c;};
    double find_final_price(){return (price + packaging_price);};
    friend class Order;
private:
    string ingred_name;
    shared_ptr<Supplier> my_offeror;
    int count;
    double price;
    double packaging_price;
};

class Ingredient{
public:
    Ingredient(string name_): name(name_){};
    shared_ptr<Offer> find_best_offer();
    string get_name(){return name;};
    void add_offer(shared_ptr<Offer> of){offers_about_me.push_back(of);};
    void delete_offer(shared_ptr<Offer> of);
    friend class Offer;
private:
    string name;
    vector<shared_ptr<Offer>> offers_about_me;
};

typedef shared_ptr<Offer> POffer;
typedef vector<POffer> OfferList;
typedef shared_ptr<Ingredient> PIngredient;
typedef vector<PIngredient> IngredList;

#endif //_INGREDIENTS_H