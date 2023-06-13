#include "orders.hpp"
#include <memory>

shared_ptr<OrderLine> Order::find_order_line_by_offeror
    (shared_ptr<Supplier> s)
{
    for(int i = 0; i < order.size(); i++){
        if(order[i]->supplier == s)
            return order[i];
    }
    return NULL;
}

bool Order::is_too_expensive_for(shared_ptr<Common>& active_u)
{
    active_user = active_u;
    shared_ptr<Offer> best_offer;
    for(int i = 0; i < wanted_ingreds.size(); i++){
        best_offer = wanted_ingreds[i]->find_best_offer();
        total_price += best_offer->find_final_price();
    }
    int price = static_cast<int>(total_price);
    int budget = static_cast<int>(active_user->get_credit());
    if(price > budget)
        return true;
    else
        return false;  
}

void Order::money_transfer(PIngredient& ingred,POffer best_offer,OfferList& offers)
{ 
    if(best_offer->count == 0){
        offers.erase(remove(offers.begin(),offers.end(),best_offer),offers.end());
        ingred->delete_offer(best_offer);
    }
    else
        (best_offer->count)--;
    best_offer->my_offeror->add_credit(best_offer->find_final_price());
}

void Order::make(OfferList& offers)
{
    for(auto ingred : wanted_ingreds){
        shared_ptr<Offer> best_offer = ingred->find_best_offer();
        money_transfer(ingred,best_offer,offers);
        shared_ptr<OrderLine> found_line = find_order_line_by_offeror(best_offer->my_offeror);
        if(found_line == NULL){
            shared_ptr<OrderLine> new_order_line;
            new_order_line = make_shared<OrderLine>
                (best_offer->my_offeror,ingred);
            order.push_back(new_order_line);
        }
        else{
            found_line->supplied_ingreds.push_back(ingred);
        }
    }
    active_user->add_credit((-1) * total_price);
}

string Order::to_string()
{
    lexicographicalize<shared_ptr<OrderLine>>(order);
    for(auto line : order){
        order_text << line->supplier->get_name();
        lexicographicalize<shared_ptr<Ingredient>>(line->supplied_ingreds);
        for(auto ingredinedt : line->supplied_ingreds){
            order_text << " " << ingredinedt->get_name();
        }
        order_text << endl;
    }
    order_text << total_price;
    return order_text.str();
}