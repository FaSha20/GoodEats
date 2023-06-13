#include "handlers.hpp"
#include "my_server.hpp"
#include <cstdlib> // for rand and srand
#include <ctime>   // for time
#include <iostream>
#define BAD_REQUEST_PAGE "static/303.html"
#define NO_PERMITION_PAGE "static/505.html"
#define NOT_FOUND_PAGE "static/404.html"
#define NOT_SIGNEDUP_PAGE "static/4004.html"
#define ALREADY_SIGNEDUP_PAGE "static/5005.html"
#define UNCOMPELETE_PAGE "static/3003.html"
#define LOGIN_PAGE "static/logincss.html"
#define SIGNUP_PAGE "static/signupcss.html"
#define CHEF_PAGE "static/chefcss.html"
#define EDIT_PAGE "static/editcss.html"
#define EDIT_SHELF_PAGE "static/editshelfcss.html"
#define CHANGE_MADE_PAGE "static/change.html"
#define CHANGE_MADESH_PAGE "static/changesh.html"

#define COMMON_TEMP_PAGE "template/commontemp.html"
#define COMMON_PAGE "static/commoncss.html"


using namespace std;

int main(int argc, char **argv) {
  DataBase *dataBase = new DataBase();
  MyServer server(argc > 1 ? atoi(argv[1]) : 5000);
  try {
    server.setNotFoundErrPage(NOT_FOUND_PAGE);
    server.get("/NotFound",new ShowPage(NOT_FOUND_PAGE));
    server.post("/NotFound",new MyHandler("/"));
    server.get("/PermisionDenied",new ShowPage(NO_PERMITION_PAGE));
    server.post("/PermisionDenied",new MyHandler("/"));
    server.get("/BadRequest",new ShowPage(BAD_REQUEST_PAGE));
    server.post("/BadRequest",new MyHandler("/"));
    server.get("/NotSignedUp",new ShowPage(NOT_SIGNEDUP_PAGE));
    server.post("/NotSignedUp",new MyHandler("/"));
    server.get("/AlreadySignedUp",new ShowPage(ALREADY_SIGNEDUP_PAGE));
    server.post("/AlreadySignedUp",new MyHandler("/"));
    server.get("/UnCompeleteData",new ShowPage(UNCOMPELETE_PAGE));
    server.post("/UnCompeleteData",new MyHandler("/"));
    server.get("/ChangePage", new ShowPage(CHANGE_MADE_PAGE));
    server.post("/ChangePage", new RedirectHandler("/ChefPage"));
    server.get("/ChangeshPage", new ShowPage(CHANGE_MADESH_PAGE));
    server.post("/ChangeshPage", new RedirectHandler("/CommonPage"));

    server.get("/login", new ShowPage(LOGIN_PAGE));
    server.post("/login", new LoginHandler(dataBase));
    server.get("/signup", new ShowPage(SIGNUP_PAGE));
    server.post("/signup", new SignupHandler(dataBase));

    server.get("/ChefPage", new ShowPage(CHEF_PAGE));
    server.post("/ChefPage", new ChefHandler(dataBase));
    server.get("/EditPage", new ShowPage(EDIT_PAGE));
    server.post("/EditPage", new EditHandler(dataBase));
    server.get("/EditShelfPage", new ShowPage(EDIT_SHELF_PAGE));
    server.post("/EditShelfPage", new EditShelfHandler(dataBase));

    server.get("/CommonPage",new ShowPage(COMMON_PAGE));
    server.get("/RecipeListPage", new ListHandler(COMMON_TEMP_PAGE,dataBase));
    server.get("/RecipePage",new RecipeHandler(dataBase));
    server.get("/ShelfPage",new ShelfPageHandler(dataBase));
    server.get("/ShelfManPage",new ShelfHandler(dataBase));

    server.get("/up", new ShowPage("static/upload_form.html"));
    server.post("/up", new UploadHandler());
    server.get("/rand", new RandomNumberHandler());
    server.get("/food.jpeg", new ShowImage("static/foodwall.jpeg"));
    server.get("/food.gif", new ShowImage("static/food.gif"));
    server.get("/home.png", new ShowImage("static/home.png"));
    server.get("/cheff.png", new ShowImage("static/cheff.png"));
    server.get("/user.jpeg",new ShowImage("static/user.jpeg"));
    server.get("/", new ShowPage("static/home.html"));
    server.post("/", new MyHandler("/"));
    server.get("/colors", new ColorHandler("template/colors.html"));
    server.run();
  }
  catch (Server::Exception& e) {
    cerr << e.getMessage() << endl;
  }
  catch (...) {
    server.get("/BadRequest",new ShowPage(BAD_REQUEST_PAGE));
  }

}
