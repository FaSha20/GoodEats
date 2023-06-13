#ifndef _ERROR_H
#define _ERROR_H

#include <iostream>
#include <exception>
using namespace std;

class Permission_err : public runtime_error{
public:
    Permission_err(string err_msg = "Permission Dennied")
        :runtime_error(err_msg){};
};

class Bad_request_err: public runtime_error{
public:
    Bad_request_err(string err_msg = "Bad Request")       
        :runtime_error(err_msg){};
};

class Not_found_err: public runtime_error{
public:
    Not_found_err(string err_msg = "Not Found")       
        :runtime_error(err_msg){};
};

#endif //_ERROR_H