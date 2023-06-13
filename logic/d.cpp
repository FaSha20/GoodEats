#include <iostream>
#include <vector>
#include <sstream>
#include <algorithm>
#include <memory>
#include <exception>
#include <limits>
#include <iomanip>
using namespace std;

template<typename T>
class my{
public:
    
    void add(T new_){nums.push_back(new_);};
protected:
    int x;
    vector<T> nums;
};

class U{
public:
    string name;
};

class hi : public my<int>{
public:
    int get_num(int index){return nums[index];};
};
    
int* fun(){
    return NULL;
}
int main()
{   
    string str = "hi\n";
    cout << str ;
    if(!str.empty())
        str.pop_back();
    cout << str ;
    
    // my m;
    // m.add_num(&a);
    // m.add_num(&b);
    // m.printnums();
    // cout << endl;
    // m.add_num(&c);
    // m.printnums();
    // cout << endl;
    // cout <<"here"<< *m.nums[0] << endl;
    // cout <<"here"<< *m.nums[1] << endl;
    // cout <<"here"<< *m.nums[2] << endl;

    // m.delete_num(&c);
    // m.printnums();
    // cout << endl;
    // cout <<"here"<< *m.nums[0] << endl;
    // cout <<"here"<< *m.nums[1] << endl;
    // cout <<"here"<< *m.nums[2] << endl;
    // cout << m.nums.size() << endl;


    
}