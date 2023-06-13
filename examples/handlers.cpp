#include "handlers.hpp"

using namespace std;

Response *RandomNumberHandler::callback(Request *req) {
  Response *res = new Response;
  res->setHeader("Content-Type", "text/html");
  string body;
  body += "<!DOCTYPE html>";
  body += "<html>";
  body += "<body style=\"text-align: center;\">";
  body += "<h1>AP HTTP</h1>";
  body += "<p>";
  body += "a random number in [1, 10] is: ";
  body += to_string(rand() % 10 + 1);
  body += "</p>";
  body += "<p>";
  body += "SeddionId: ";
  body += req->getSessionId();
  body += "</p>";
  body += "</body>";
  body += "</html>";
  res->setBody(body);
  return res;
}
Response *ChefHandler::callback(Request* req)
{
  Response *res = new Response;
  int id = stoi(req->getSessionId());
  PChef chef = find_by_id(id,database->chefs);
  vector<string> recipes = chef->get_recipes();
  res->setHeader("Content-Type", "text/html");
  string body;
  body += "<!DOCTYPE html>";
  body += "<html>";
  body += "<head>";
  body += "<style>";
  body += ".p1 {font-family: \"Lucida Handwriting\", cursive;font-size: larger;}";
  body += ".p2 {font-family: Arial, Helvetica, sans-serif;text-align: left;}";
  body += "body  {background-color: #b38ca6;}";
  body += "</style>";
  body += "</head>";
  body += "<body style=\"text-align: center;\"> ";
  body += "<p class=\"p1\"> GOOD EATS :)</p>";
  body += "<h2>My Recipes</h2>";
  body += "<br />";
  body += "<div style=\"background-color: rgb(244, 245, 247);padding: 10%; max-width: 300px; border-radius: 10px; margin: auto; \">";
 // body += "<img src=\"cheff.png\" style=\"width: 150px;\">";
  for(unsigned i = 0;i < recipes.size();i++){
    body += "<p class=\"p1\">Number " + to_string(i + 1) + "</p>";
    body += "<div style=\"background-color: rgb(233, 222, 75);padding: 10%; max-width: 300px; border-radius: 10px; margin: auto; \">";
    body += "<p class=\"p2\">" + recipes[i] + "</p>";
    body += "<br />";
    body += "</div>";
  }
  if(recipes.size() == 0)
    body += "Empty!";
  body += "<br /><br />";
  body += "<form action=\"/EditPage\" method=\"get\">";
  body += "<button type=\"submit\" style=\"display:block; width: 100%; padding: 7px;\"><p \">Edit Recipes</p></button>";
  body += "</form> ";
  body += "<form action=\"/\" method=\"post\">";
  body += "<button type=\"submit\" style=\"display:block; width: 100%; padding: 7px;\"><p \">Exit</p></button>";
  body += "</form> ";
  body += "</div>";
  body += "</body>";
  body += "</html>";  
  res->setBody(body);
  return res;
}

Response *ShelfHandler::callback(Request* req)
{
  Response *res = new Response;
  try{
  int id = stoi(req->getSessionId());
  PCommon common = find_by_id(id,database->commons);
  vector<string> shelves = common->show_shelves();
  res->setHeader("Content-Type", "text/html");
  string body;
  body += "<!DOCTYPE html>";
  body += "<html>";
  body += "<head>";
  body += "<style>";
  body += ".p1 {font-family: \"Lucida Handwriting\", cursive;font-size: larger;}";
  body += ".p2 {font-family: Arial, Helvetica, sans-serif;text-align: left;}";
  body += "body  {background-color: #b38ca6;}";
  body += "</style>";
  body += "</head>";
  body += "<body style=\"text-align: center;\"> ";
  body += "<p class=\"p1\"> GOOD EATS :)</p>";
  body += "<h2>My Shelves</h2>";
  body += "<br />";
  body += "<div style=\"background-color: rgb(244, 245, 247);padding: 10%; max-width: 300px; border-radius: 10px; margin: auto; \">";
  for(unsigned i = 0;i < shelves.size();i++){
    body += "<p class=\"p1\">Shelf " + to_string(i + 1) + "</p>";
    body += "<div style=\"background-color: rgb(233, 222, 75);padding: 10%; max-width: 300px; border-radius: 10px; margin: auto; \">";
    body += "<p class=\"p2\">" + shelves[i] + "</p>";
    body += "<form action=\"/ShelfPage\"method=\"get\">";
    body += "<button type=\"submit\" name=\"show_compelet_info\" style=\"color: cornsilk;align-items: center;background-color: rgb(122, 83, 24);display:block; width: 100%; padding: 7px\" value=\"" + to_string(i) + "\">  Go to Shelf Page</button>";
    body += "</form>" ;
    body += "<br />";
    body += "</div>";
  }
  if(shelves.size() == 0)
    body += "Empty!";
  body += "<br /><br />";
  body += "<form action=\"/EditShelfPage\" method=\"get\">";
  body += "<button type=\"submit\" style=\"display:block; width: 100%; padding: 7px;\"><p \">Edit Shelves</p></button>";
  body += "</form> ";
  body += "<form action=\"/\" method=\"post\">";
  body += "<button type=\"submit\" style=\"display:block; width: 100%; padding: 7px;\"><p \">Exit</p></button>";
  body += "</form> ";
  body += "</div>";
  body += "</body>";
  body += "</html>";  
  res->setBody(body);
  }
  catch(Permission_err& perr){
    res = Response::redirect("/PermisionDenied");
  }
  catch(Bad_request_err& perr){
    res = Response::redirect("/UnCompeleteData");
  }
  catch(...){
    res = Response::redirect("/BadRequest");
  }
  return res;
}

map<string, string> ListHandler::handle(Request *req) {
  map<string, string> context ;
  RecipeList recipes = database->recipes;
  for(unsigned i = 0;i < recipes.size();i++ )
    context[to_string(i)] = recipes[i]->get_properties_in_line();
  return context;
}

Response *RecipeHandler::callback(Request* req)
{
  Response *res = new Response;
  try{
    int id = stoi(req->getSessionId());
    int index = stoi(req->getQueryParam("show_compelet_info"));
    double rate = stof(req->getQueryParam("rate"));
    PRecipe recipe = database->recipes[index];
    PCommon common = find_by_id(id,database->commons);
    if(common->have_already_rated_this_recipe(recipe->get_id()))
      recipe->add_rate(common->change_ratetorecipe_pair(rate,recipe->get_id()));
    else{
      recipe->add_rate(rate);
      common->add_new_ratetorecipe_pair(rate,recipe->get_id());
    }
    res->setHeader("Content-Type", "text/html");
    string body;
    body += "<!DOCTYPE html>";
    body += "<html>";
    body += "<head>";
    body += "<style>";
    body += ".p1 {font-family: \"Lucida Handwriting\", cursive;font-size: x-large;}";
    body += ".p2 {text-align: left;}";
    body += "body  {background-color: #b8925a;}";
    body += "</style>";
    body += "</head>";
    body += "<body style=\"text-align: center;\"> ";
    body += "<p class=\"p1\"> GOOD EATS :)</p>";
    body += "<br />";
    body += "<div style=\"background-color: rgb(244, 245, 247);padding: 10%; max-width: 300px; border-radius: 10px; margin: auto; \">";
    body += "<h2 class=\"p1\">" + recipe->get_name() + "</h2>";
    body += "<div style=\"background-color: rgb(233, 222, 75);padding: 10%; max-width: 300px; border-radius: 10px; margin: auto; \">";
    body += "<p class=\"p2\">" + recipe->get_compelet_properties() + "</p>";
    body += "</div>";
    body += "<br /><br />";
    body += "<form action=\"/RecipeListPage\" method=\"get\">";
    body += "<button type=\"submit\" style=\"display:block; width: 50%; padding: 2px;\"><p \">Back</p></button>";
    body += "</form> ";
    body += "<form action=\"/\" method=\"post\">";
    body += "<button type=\"submit\" style=\"display:block; width: 50%; padding: 2px;\"><p \">Exit</p></button>";
    body += "</form> ";
    body += "</div>";
    body += "</body>";
    body += "</html>";  
    res->setBody(body);
  }
  catch(Permission_err& perr){
    res = Response::redirect("/PermisionDenied");
  }
  catch(Bad_request_err& perr){
    res = Response::redirect("/UnCompeleteData");
  }
  catch(...){
    res = Response::redirect("/BadRequest");
  }
  return res;
  
}

Response *ShelfPageHandler::callback(Request* req)
{
  Response *res = new Response;
  try{
    int index = stoi(req->getQueryParam("show_compelet_info"));
    PShelf shelf = database->shelves[index];
    res->setHeader("Content-Type", "text/html");
    string body;
    body += "<!DOCTYPE html>";
    body += "<html>";
    body += "<head>";
    body += "<style>";
    body += ".p1 {font-family: \"Lucida Handwriting\", cursive;font-size: x-large;}";
    body += ".p2 {text-align: left;}";
    body += "body  {background-color: #b8925a;}";
    body += "</style>";
    body += "</head>";
    body += "<body style=\"text-align: center;\"> ";
    body += "<p class=\"p1\"> GOOD EATS :)</p>";
    body += "<br />";
    body += "<div style=\"background-color: rgb(244, 245, 247);padding: 10%; max-width: 300px; border-radius: 10px; margin: auto; \">";
    body += "<h2 class=\"p1\">" + shelf->get_name() + "</h2>";
    body += "<div style=\"background-color: rgb(233, 222, 75);padding: 10%; max-width: 300px; border-radius: 10px; margin: auto; \">";
    body += "<p class=\"p2\">" + shelf->get_compelet_properties() + "</p>";
    body += "</div>";
    body += "<br /><br />";
    body += "<form action=\"/ShelfManPage\" method=\"get\">";
    body += "<button type=\"submit\" style=\"display:block; width: 50%; padding: 2px;\"><p \">Back</p></button>";
    body += "</form> ";
    body += "<form action=\"/\" method=\"post\">";
    body += "<button type=\"submit\" style=\"display:block; width: 50%; padding: 2px;\"><p \">Exit</p></button>";
    body += "</form> ";
    body += "</div>";
    body += "</body>";
    body += "</html>";  
    res->setBody(body);
  }
  catch(Permission_err& perr){
    res = Response::redirect("/PermisionDenied");
  }
  catch(Bad_request_err& perr){
    res = Response::redirect("/UnCompeleteData");
  }
  catch(...){
    res = Response::redirect("/BadRequest");
  }
  return res;
  
}
Response *EditHandler::callback(Request* req)
{
  Response *res = new Response;
  int id = stoi(req->getSessionId());
  PChef chef = find_by_id(id,database->chefs);
  string title = req->getBodyParam("title");
  string ingreds = req->getBodyParam("ingredients");
  string min = req->getBodyParam("min_to_ready");
  string tags = req->getBodyParam("tags");
  string veg = req->getBodyParam("vegetarian");
  string img = " ";
  string removed_title = req->getBodyParam("r_title");
  string removed_id = req->getBodyParam("r_id");
  try{
    if(!title.empty() && !ingreds.empty() && !min.empty() &&
     !tags.empty() && !veg.empty())
    { 
      int add_id = database->recipes.size() + 1;
      PRecipe new_recipe = make_shared<Recipe>
        (title,ingreds,veg,min,tags,img,chef,add_id);
      database->recipes.push_back(new_recipe);
      chef->add_to_my_recipes(new_recipe);
      res = Response::redirect("/ChangePage");
    }
    else if(!removed_title.empty() && !removed_id.empty()){
      int recipe_id = stoi(removed_id);
      int recipe_index = find_index_by_id(recipe_id,database->recipes);
      if(recipe_index == IN_ACCESSIBLE)
        throw Permission_err();
      database->recipes.erase(database->recipes.begin() + recipe_index);
      chef->delete_recipe(recipe_id);
      res = Response::redirect("/ChangePage");
    }
    else{
      throw Bad_request_err();
    }  
  }
  catch(Permission_err& perr){
    res = Response::redirect("/PermisionDenied");
  }
  catch(Bad_request_err& perr){
    res = Response::redirect("/UnCompeleteData");
  }
  catch(...){
    res = Response::redirect("/BadRequest");
  }

  return res;
}

Response *EditShelfHandler::callback(Request* req)
{
  Response *res = new Response;
  int id = stoi(req->getSessionId());
  PCommon common = find_by_id(id,database->commons);
  string title = req->getBodyParam("title");
  string recipes = req->getBodyParam("recipes");
  string name;
  stringstream data(recipes);
  string removed_title = req->getBodyParam("r_title");
  string removed_id = req->getBodyParam("r_id");
  try{
    if(!title.empty())
    { 
      int add_id = database->shelves.size() + 1;
      PShelf new_shelf = make_shared<Shelf>(title,add_id);
      while (getline(data,name,',')){
        PRecipe recipe = find_by_name(name,database->recipes);
        if(recipe == NULL)
          throw Not_found_err();
        new_shelf->add_recipe(recipe);
      }
      database->shelves.push_back(new_shelf);
      common->add_to_my_shelves(new_shelf);
      res = Response::redirect("/ChangeshPage");
    }
    else if(!removed_title.empty() && !removed_id.empty()){
      int shelf_id = stoi(removed_id);
      int shelf_index = find_index_by_id(shelf_id,database->shelves);
      if(shelf_index == IN_ACCESSIBLE)
        throw Permission_err();
      database->shelves.erase(database->shelves.begin() + shelf_index);
      common->remove_shelf(shelf_id);
      res = Response::redirect("/ChangeshPage");
    }
    else{
      throw Bad_request_err();
    }  
  }
  catch(Permission_err& perr){
    res = Response::redirect("/PermisionDenied");
  }
  catch(Bad_request_err& perr){
    res = Response::redirect("/UnCompeleteData");
  }
  catch(...){
    res = Response::redirect("/BadRequest");
  }

  return res;
}

Response *MyHandler::callback(Request *req){
  Response *res = new Response;
  res = Response::redirect(path);
  res->setSessionId("0");
  return res;
}

Response *RedirectHandler::callback(Request *req){
  Response *res = new Response;
  res = Response::redirect(path);
  return res;
}

Response *LoginHandler::callback(Request *req) {
  Response *res = new Response;
  int id;
  string username = req->getBodyParam("username");
  string password = req->getBodyParam("password");
  if (username == "root")
    throw Server::Exception("Remote root access has been disabled."); 
  try{
    id = database->find_user_id(username,password);
    user_type type = database->user_id_map[id]->get_type();
    if(type == chef)
      res = Response::redirect("/ChefPage");
    else if(type == common_user)
      res = Response::redirect("/CommonPage");
    else
      res = Response::redirect("/BadRequest");
    res->setSessionId(to_string(id));
  } 
  catch(Not_found_err& ne){
    res = Response::redirect("/NotSignedUp");
  }
  return res;
}

Response *SignupHandler::callback(Request *req) {
  
  Response *res = new Response;
  int id = 0;
  string username = req->getBodyParam("username");
  string password = req->getBodyParam("password");
  string type = req->getBodyParam("userType");
  if (username == "root")
    throw Server::Exception("Remote root access has been disabled.");
  try{
    id = database->add_user(type,username,password);
    if(type == "chef")
    res = Response::redirect("/ChefPage");
    else
      res = Response::redirect("/CommonPage");
  } 
  catch(Bad_request_err& be){
    res = Response::redirect("/AlreadySignedUp");
  }  
  res->setSessionId(to_string(id));
  return res;
}

Response *UploadHandler::callback(Request *req) {
  string name = req->getBodyParam("file_name");
  string file = req->getBodyParam("file");
  cout << name << " (" << file.size() << "B):\n" << file << endl;
  Response *res = Response::redirect("/");
  return res;
}

ColorHandler::ColorHandler(string filePath) : TemplateHandler(filePath) {}

map<string, string> ColorHandler::handle(Request *req) {
  map<string, string> context;
  string newName = "I am " + req->getQueryParam("name");
  context["name"] = newName;
  context["color"] = req->getQueryParam("color");
  return context;
}
