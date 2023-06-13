#ifndef _PROCCES_H
#define _PROCCES_H

#include <iostream>
#include "managers.hpp"

using namespace std;

class Procces{
public:
    string get_out_puts(){return out_put;};
    void check_commands(stringstream& data_buf);
private:
    Chef_manager chef_manager;
    Common_user_manager common_manager;
    Supplier_manager sup_manager;
    vector<shared_ptr<User>> all_users;
    RecipeList recipes;
    string out_put;
    bool is_per_command_valid(string per_command);
    bool is_there_any_active_user();
    void first_login_or_signup(string per_command,stringstream& data_buf);
    void signup(stringstream& buf);
    void signup_supplier(stringstream& buf);
    void login(stringstream& buf);
    void make_chef(string username,string password);
    void make_common_user(string username,string password);
    
};



#endif //_PROCCES_H