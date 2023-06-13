#include "data_base.hpp"

bool DataBase::is_unique(string username)
{
    for(unsigned i = 1;i <= all_users.size() ;i++){
        shared_ptr<User> usr = user_id_map[i];
        if( usr->get_name() == username )
            return false;
    }
    return true;
}

int DataBase::add_user(string type,string username,string password)
{
    if (! is_unique(username))
        throw Bad_request_err();       
    int id = all_users.size() + 1;
    if(type == "chef"){
        PChef new_chef = make_shared<Chef>(username,password);
        new_chef->id = id;
        chefs.push_back(new_chef);
        all_users.push_back(new_chef);
        user_id_map.insert({id,new_chef});
    }
    else if(type == "common"){
        PCommon new_common = make_shared<Common>(username,password);
        new_common->id = id;
        commons.push_back(new_common);
        all_users.push_back(new_common);
        user_id_map.insert({id,new_common});
    }
    return id;    
}

int DataBase::find_user_id(string username,string password)
{ 
    for(unsigned i = 0; i < all_users.size(); i++){
        if(all_users[i]->username == username && 
           all_users[i]->password == password)
            return all_users[i]->id;  
    } 
    throw Not_found_err();
}