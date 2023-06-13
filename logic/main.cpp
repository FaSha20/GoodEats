// IN THE NAME OF GOD
//Fatemeh Shahhosseini - 1400/3/8
//AP7-1 poject : goodeats (general programming)
#include <iostream>
#include "procces.hpp"
#include <fstream>
using namespace std;

void print(string out_put)
{
    cout << out_put << endl;
}

void procces()
{  
    string line;
    Procces procces;
    while (true)
    {      
        try{            
            if(!getline(cin,line))
                break;
    
            stringstream line_data_buf(line);
            procces.check_commands(line_data_buf);
            print(procces.get_out_puts());
        }
        catch(runtime_error& err){
            print(err.what()) ;
        }
    }
}


int main()
{
    procces();
}