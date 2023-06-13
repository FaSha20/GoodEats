#ifndef _MY_HANDLERS_
#define _MY_HANDLERS_

#include "../server/server.hpp"
#include "../logic/data_base.hpp"
#include <cstdlib> // for rand and srand
#include <ctime>   // for time
#include <iostream>
#include <fstream>
#include <exception>



class RandomNumberHandler : public RequestHandler {
public:
  Response *callback(Request *);
};

class LoginHandler : public RequestHandler {
  DataBase *database;
  ofstream outfile;
public:
  LoginHandler(DataBase *_dataBase){database = _dataBase;};
  Response *callback(Request *);
};

class SignupHandler : public RequestHandler {
  DataBase *database;
public:
  SignupHandler(DataBase *_dataBase){database = _dataBase;};
  Response *callback(Request *);
};

class ChefHandler : public RequestHandler {
  DataBase *database;
public:
  ChefHandler(DataBase *_dataBase){database = _dataBase;};
  Response *callback(Request *);
};

class ListHandler : public TemplateHandler {
  DataBase *database;
public:
  ListHandler(string filePath,DataBase *_database)
    :TemplateHandler(filePath){database = _database;};
  std::map<std::string, std::string> handle(Request *req);
};

class EditHandler : public RequestHandler {
  DataBase *database;
public:
  EditHandler(DataBase *_dataBase){database = _dataBase;};
  Response *callback(Request *);
};

class ShelfHandler : public RequestHandler {
  DataBase *database;
public:
  ShelfHandler(DataBase *_dataBase){database = _dataBase;};
  Response *callback(Request *);
};

class EditShelfHandler : public RequestHandler {
  DataBase *database;
public:
  EditShelfHandler(DataBase *_dataBase){database = _dataBase;};
  Response *callback(Request *);
};

class RecipeHandler : public RequestHandler {
  DataBase *database;
public:
  RecipeHandler(DataBase *_dataBase){database = _dataBase;};
  Response *callback(Request *);
};

class ShelfPageHandler : public RequestHandler {
  DataBase *database;
public:
  ShelfPageHandler(DataBase *_dataBase){database = _dataBase;};
  Response *callback(Request *);
};

class MyHandler : public RequestHandler {
  std::string path;
public:
  MyHandler(std::string _path):path(_path){};
  Response *callback(Request *);
};

class RedirectHandler : public RequestHandler {
  std::string path;
public:
  RedirectHandler(std::string _path):path(_path){};
  Response *callback(Request *);
};

class UploadHandler : public RequestHandler {
public:
  Response *callback(Request *);
};

class ColorHandler : public TemplateHandler {
public:
  ColorHandler(std::string filePath);
  std::map<std::string, std::string> handle(Request *req);
};

#endif
