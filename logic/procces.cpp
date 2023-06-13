#include "procces.hpp"






bool Procces::is_per_command_valid(string per_command)
{
    if( per_command == "POST" || per_command == "DELETE" ||
        per_command == "PUT"  || per_command == "GET")
        return true;
    else
        return false;
}


void Procces::make_chef(string username,string password)
{
    PChef new_chef = make_shared<Chef>(username,password);
    chef_manager.set_active_user(new_chef);
    common_manager.set_active_user(NULL);
    sup_manager.set_active_user(NULL);
    chef_manager.add_user(new_chef);
    all_users.push_back(new_chef);
}

void Procces::make_common_user(string username,string password)
{
    PCommon new_common_user = 
            make_shared<Common>(username,password);
    common_manager.set_active_user(new_common_user);
    chef_manager.set_active_user(NULL);
    sup_manager.set_active_user(NULL);
    common_manager.add_user(new_common_user);
    all_users.push_back(new_common_user);
}

void Procces::signup(stringstream& data_buf)
{
    string username,password,type,command_word;
    data_buf >> command_word >>  username >> command_word 
             >> password  >> command_word >>  type;
    for(int i = 0 ; i < all_users.size(); i++)
        if(all_users[i]->get_name() == username)
            throw Bad_request_err();
    if(type == "chef")
        make_chef(username,password);
    else if(type == "user")
        make_common_user(username,password);
    else throw Bad_request_err();
}

void Procces::signup_supplier(stringstream& data_buf)
{
    string name,email,password,command_word;
    data_buf >> command_word >> name >> command_word 
             >> email  >> command_word >>  password;
    for(auto u : all_users)
        if(u->get_name() == name){
            throw Bad_request_err();
        }
    PSupplier new_sup = make_shared<Supplier>(name,password,email);
    sup_manager.set_active_user(new_sup);
    
    chef_manager.set_active_user(NULL);
    common_manager.set_active_user(NULL);
    sup_manager.add_user(new_sup);
    all_users.push_back(new_sup);
}

void Procces::login(stringstream& data_buf)
{
    string username,password,type,command_word;
    data_buf >> command_word >> username >> command_word >> password ;
    shared_ptr<User> user = find_user(username,password,all_users);
    if(user->get_type() == chef){
        PChef find_user = chef_manager.find_by_username(username);
        chef_manager.set_active_user(find_user);
        common_manager.set_active_user(NULL);
        sup_manager.set_active_user(NULL);
    }
    else if(user->get_type() == common_user){
        PCommon find_user = common_manager.find_by_username(username);
        common_manager.set_active_user(find_user);
        chef_manager.set_active_user(NULL);
        sup_manager.set_active_user(NULL);
    }
    else if(user->get_type() == supplier){
        PSupplier find_user = sup_manager.find_by_email(username);
        sup_manager.set_active_user(find_user);
        chef_manager.set_active_user(NULL);
        common_manager.set_active_user(NULL);
    }
    else return;
}

void Procces::first_login_or_signup(string per_command,stringstream& data_buf)
{
    string command,ques_mark;
    data_buf >> command >> ques_mark;
    if(per_command == "POST" && command == "signup" && ques_mark == "?"){
        signup(data_buf);
        out_put = CONFIRMED;
    }
    else if(per_command == "POST" && command == "signup_supplier" && ques_mark=="?"){
        signup_supplier(data_buf);
        out_put = CONFIRMED;
    }
    else if(per_command == "POST" && command == "login" && ques_mark=="?"){
        login(data_buf);
        out_put = CONFIRMED;
    }
    else throw Permission_err(); 
}

void Procces::check_commands(stringstream& data_buf)
{
    string per_command;
    data_buf >> per_command ;
    if(is_per_command_valid(per_command)){
        if(chef_manager.has_active_user()){
            chef_manager.check_command(per_command,data_buf,
                recipes,out_put);
        }
        else if(common_manager.has_active_user()){
            common_manager.check_command(per_command,data_buf,recipes,
                chef_manager.get_chefs_list(),
                sup_manager.get_ingredients_list(),
                sup_manager.get_offer_list(),out_put);
        }
        else if(sup_manager.has_active_user()){
            sup_manager.check_command(per_command,data_buf,
                recipes,out_put);
        }
        else
            first_login_or_signup(per_command,data_buf);
        
    }
    else throw Bad_request_err();
    
}