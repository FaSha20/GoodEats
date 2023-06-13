#include "supplier.hpp"

shared_ptr<Offer> Supplier::find_offer(string ingred_name)
{
    for(int i = 0; i < my_offers.size(); i++)
        if(my_offers[i]->get_name() == ingred_name)
            return my_offers[i];
    return NULL;
}

void Supplier::delete_offer(string ingred_name)
{
    int index = find_index_by_username(ingred_name,my_offers);
    if(index == IN_ACCESSIBLE)
        throw Not_found_err();
    my_offers.erase(my_offers.begin() + index);
}
