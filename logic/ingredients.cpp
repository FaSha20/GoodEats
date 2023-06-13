#include "ingredients.hpp"

Offer ::Offer(string in,shared_ptr<Supplier> of,double p,int c,double pp)
{
    my_offeror = of;
    price = p;
    count = c;
    packaging_price = pp;
    ingred_name = in;
}

void Ingredient::delete_offer(shared_ptr<Offer> of)
{
    int index = find_index_by_username(of->get_name(),offers_about_me);
    if(index == IN_ACCESSIBLE)
        throw Not_found_err("bad exception");
    offers_about_me.erase(offers_about_me.begin() + index);
}


shared_ptr<Offer> Ingredient::find_best_offer()
{
    shared_ptr<Offer>lowest_cost_offer = offers_about_me[0];
    double lowest_cost;int first_cost,other_cost;
    for( int i = 0; i < offers_about_me.size(); i++){
        first_cost =static_cast<int>(lowest_cost_offer->find_final_price());
        other_cost =static_cast<int>(offers_about_me[i]->find_final_price());
        lowest_cost_offer =
        (first_cost > other_cost)? offers_about_me[i]:lowest_cost_offer;
    }
    return lowest_cost_offer;
}
