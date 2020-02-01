#include<iostream>
#include<stdio.h>
using namespace std;

template<class T, int N>                                //first template for the class myContainer
class myContainer                                       //class defn. begins
{
    T container[N];
public:
    myContainer(int x, T value){container[x]=value;}    //constructor for myContainer
    void setValue(int x,T value){container[x]=value;}   //one function defined inline
    T getValue(int x);                                  //other func declared only
};
template<class T,int N>                                 //defined outside
T myContainer<T,N>::getValue(int x)
{
    return container[x];
}

template<class T,int M>                                 //second template for class myBox
class myBox                                             //class defn.....it has similar members
{
    T box[M];
public:
    myBox(int x, T value){box[x]=value;}
    void setValue(int x,T value){box[x]=value;}
    T getValue(int x);
};
template<class T,int M>
T myBox<T,M>::getValue(int x)
{
    return box[x];
}

int main() {
    const int count_int=3,count_float=2;
    myBox<int,count_int> myint(0,23);
    myContainer<float,count_float> myfloat(0,234.332);
    myint.setValue(4,2523);
    myfloat.setValue(9,23.32);
    printf("%d \n %f",myint.getValue(4),myfloat.getValue(9));
    return 0;
}
