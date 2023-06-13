CC := g++ -std=c++11

goodeats.out: main.o users.o recipes.o supplier.o orders.o ingredients.o command_checking.o managers.o procces.o data_base.o
	$(CC) main.o users.o recipes.o managers.o supplier.o orders.o ingredients.o procces.o command_checking.o data_base.o -o goodeats.out

main.o: procces.hpp main.cpp
	$(CC) -c main.cpp -o main.o

users.o: users.hpp recipes.hpp my_errors.hpp sort.hpp finder.hpp users.cpp
	$(CC) -c users.cpp -o users.o

recipes.o: recipes.hpp users.hpp ingredients.hpp my_errors.hpp sort.hpp finder.hpp recipes.cpp
	$(CC) -c recipes.cpp -o recipes.o

command_checking.o: command_checking.hpp users.hpp recipes.hpp ingredients.hpp orders.hpp command_checking.cpp
	$(CC) -c command_checking.cpp -o command_checking.o

supplier.o: supplier.hpp users.hpp ingredients.hpp supplier.cpp
	$(CC) -c supplier.cpp -o supplier.o

ingredients.o: ingredients.hpp users.hpp supplier.hpp ingredients.cpp 
	$(CC) -c ingredients.cpp -o ingredients.o

orders.o: orders.hpp ingredients.hpp supplier.hpp orders.cpp 
	$(CC) -c orders.cpp -o orders.o

data_base.o: data_base.cpp  data_base.hpp managers.hpp 
	$(CC) -c data_base.cpp -o data_base.o

managers.o: managers.hpp users.hpp recipes.hpp command_checking.hpp finder.hpp my_errors.hpp ingredients.hpp managers.cpp
	$(CC) -c managers.cpp -o managers.o

procces.o: procces.hpp managers.hpp procces.cpp
	$(CC) -c procces.cpp -o procces.o


clean:
	rm -r *.o *.out