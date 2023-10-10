#include <iostream>
using namespace std;
//构造函数的执行顺序
//先基类构造函数 在执行派生类的构造函数
//在派生类的构造函数的初始化列表 是在派生类构造函数之前执行的
class Animal{
private:
    string name;
public:
    Animal(string s){
        name=s;
        cout<<"there is animal constructor\n";
    }
    string getname(){
        return name;
    }
    
};//abstact class //没办法生成 object 

class Dog: public Animal{//派生类
    int number;
    int sex;
    public://automatic default constructor 
    Dog(int num):Animal("dog"),number(num){//initialize list before Dog constructor
        cout<<getname()<<endl;
        cout<<"there is Dog constructor\n";
    }
};

int main(){
    Dog d;
    cout<<d.getname()<<endl;
}