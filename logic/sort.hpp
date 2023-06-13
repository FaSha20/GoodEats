#ifndef _SORT_H
#define _SORT_H

#include <vector>
#include <string>
using namespace std;

template<typename T>
void lexicographicalize(vector<T>& list,int i = 0)
{
    string username1,username2;
    for(int i = 0;i< list.size()-1;i++){
        username1 =  list[i]->get_name();
        username2 = list[i+1]->get_name();
        if(username1[0] > username2[0]){
            T temp = list[i];
            list[i] = list[i+1];
            list[i+1] = temp;
            lexicographicalize(list,i+1);
        }
    }
}


#endif // _SORT_H