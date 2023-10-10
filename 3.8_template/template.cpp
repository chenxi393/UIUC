#include <iostream>
using namespace std;

//模板类
template<class T>
class Array{
    public:
    T* a;
    int num;
    Array(T m){
        num=10;
        a=new T[num];
        for(int i=0;i<10;i++){
            a[i]=m;
        }
    }
    void print(){
        for(int i=0;i<10;i++){
            cout<<a[i]<<' ';
        }
    }
    ~Array(){
        delete []a;
    }
};

// 模板函数
template <class T>
T max_(T a, T b)
{
    if (a > b)
    {
        return a;
    }
    return b;
}

// int max_(int a, int b)
// {
//     if (a > b)
//     {
//         return a;
//     }
//     return b;
// }



// double max_(double a, double b)
// {
//     if (a > b)
//     {
//         return a;
//     }
//     return b;
// }



int main(){
    int a=5;
    int b=10;
    double c=1.9,d=4.5;
    cout<< max_<int>(a,b)<<endl;
    cout<< max_<double>(c,d)<<endl;


    Array<int> p1(10);
    p1.print();
    cout<<endl<<endl;
    Array<double> p2(44.4);
    p2.print();
    cout<<endl<<endl;
    Array<string> p3("cs");
    p3.print();
    cout<<endl<<endl;
    Array<char> p4('c');
    p4.print();
}
