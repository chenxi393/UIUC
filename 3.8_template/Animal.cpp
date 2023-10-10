#include <iostream>
using namespace std;
//oop 
class Animal{//继承 ！！！派生类会自动拥有基类的全部东西  
private://可访问的范围不同 
    string name;
public://基类 子类  派生类
     //private
    Animal(string s){
        name=s;
    }
    virtual void speak()=0; //纯虚函数 pure virtual  //多态
    void setname(string s){
        name=s;
    }
    string getname(){
        return name;
    }
       
};//abstact class //没办法生成 object 

class Dog: public Animal{//派生类
    public://automatic default constructor （if no Dog constructor）
    Dog():Animal("dog"){//initialize list before Dog constructor
        cout<<"111"<<endl;
    }
    //构造函数
    virtual void speak();//声明 
};

void Dog::speak(){//函数体
    setname("dog");
    cout<<"My name is "<<getname()<<endl;
}

class cat:public Animal{
    public:
    void speak();
};
void cat::speak(){
    printf("Cat\n");
}
///  
int main(){
    Dog b;//stack 
    b.speak();
    // cat c;
    // //&c   // get c's address 
    // //Animal * //  //=address
    // //Animal &//      引用类型 /=object 
    // Animal &a=c; //基类指针（同理引用） 指向了派生类对象 调用的就是派生类的成员
    // //基类的指针 指向派生类对象
    return 0;
}
