#ifndef _FINDER_H
#define _FINDER_H
#define IN_ACCESSIBLE -1

#include "my_errors.hpp"
#include <string>
#include <vector>
using namespace std;

template<typename T>
int find_index_by_username(string username, vector<T> list)
{
    for(unsigned i = 0 ;i < list.size() ;i++)
        if(list[i]->get_name() == username) return i;
    return IN_ACCESSIBLE;
}

template<typename T>
int find_index_by_id(int id, vector<T> list)
{
    for(unsigned i = 0 ;i < list.size() ;i++)
        if(list[i]->get_id() == id) return i;
    return IN_ACCESSIBLE;
}

template<typename T>
T find_by_id(int id, vector<T>& list)
{
    for(unsigned i = 0 ;i < list.size() ;i++)
        if(list[i]->get_id() == id) return list[i];
    throw Not_found_err();
}

template<typename T>
T find_by_name(string name, vector<T>& list)
{
    for(unsigned i = 0 ;i < list.size() ;i++)
        if(list[i]->get_name() == name) return list[i];
    return NULL;
}

template<typename T>
T find_user(string name,string pas,vector<T> user_list)
{    
    for(unsigned i = 0 ; i < user_list.size(); i++)
        if((user_list[i]->get_name() == name || 
           user_list[i]->get_email() == name)&&
           user_list[i]->get_password() == pas)
           return user_list[i];
    throw Bad_request_err();
}

template<typename T>
T find_user(string name,vector<T> user_list)
{
    for(unsigned i = 0 ; i < user_list.size(); i++)
        if(user_list[i]->get_name() == name)
           return user_list[i];
    throw Bad_request_err();
}

template<typename T>
T find_sup(string email,vector<T> user_list)
{
    for(int i = 0 ; i < (int)user_list.size(); i++)
        if(user_list[i]->get_email() == email)
           return user_list[i];
    throw Bad_request_err();
}

#endif // FINDER_H