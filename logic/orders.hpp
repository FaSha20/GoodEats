#ifndef _ORDERS_H
#define _ORDERS_H

#include "supplier.hpp"
#include "ingredients.hpp"
#include "orders.hpp"

class Ingredient;class Offer;class Supplier;

class OrderLine{
public:
    OrderLine(shared_ptr<Supplier> sup,shared_ptr<Ingredient> offered_ingred)
        {supplier = sup, supplied_ingreds.push_back(offered_ingred);};
    string get_name(){return supplier->get_name();};
    friend class Order;
private:
    shared_ptr<Supplier> supplier;
    vector<shared_ptr<Ingredient>> supplied_ingreds;
};


class Order{
public:
    Order(vector<shared_ptr<Ingredient>>& w){wanted_ingreds = w,total_price = 0.0;};
    void make(OfferList& offers);
    void money_transfer(PIngredient& ingred,POffer best,OfferList& offers);
    bool is_too_expensive_for(shared_ptr<Common>& active_user);
    string to_string();
private:
    shared_ptr<OrderLine>find_order_line_by_offeror(shared_ptr<Supplier> s);
    vector<shared_ptr<Ingredient>> wanted_ingreds;
    vector<shared_ptr<OrderLine>> order;
    ostringstream order_text;
    double total_price;
    shared_ptr<Common> active_user;
};

typedef shared_ptr<Order> POrder;


#endif //_ORDERS_H