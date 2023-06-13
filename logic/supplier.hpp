#ifndef _SUPPLIER_H
#define _SUPPLIER_H

#include "supplier.hpp"
#include "users.hpp"
#include "ingredients.hpp"
class Order;class OrderLine;class Ingredient;class Offer;

class Supplier :public User{
public:
    Supplier(string n,string p,string e):User(n,p){email = e,type = supplier;};
    string get_email(){return email;};
    shared_ptr<Offer> find_offer(string ingred_name);
    void delete_offer(string ingred_name);
    void add_offer(shared_ptr<Offer> new_offer){my_offers.push_back(new_offer);};
protected:
    string email;
    vector<shared_ptr<Offer>> my_offers;
};

typedef shared_ptr<Supplier> PSupplier;
typedef vector<PSupplier> SupplierList;

#endif //_SUPPLIER_H