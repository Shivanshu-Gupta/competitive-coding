#include <iostream>
#include <stdio.h>

class Cvector
{
    public:
    int x;
    int y;
    //constructors:
    Cvector() {}
    Cvector(int a,int b): x(a),y(b) {}
    /*Cvector(const Cvector& param){                  //copy constructor...declared even though unnecessary as it is implicitly defined for all classes
        x=param.x;
        y=param.y;
        }*/
    //overloaded + for class Cvector
    Cvector operator+(const Cvector&);
};

Cvector Cvector::operator+ (const Cvector& param)   //overloaded + that returns the sum of two Cvectors
{
    Cvector temp;
    temp.x=x+param.x;
    temp.y=y+param.y;
    return temp;
}
int main() {
    Cvector a(1,4), b(a),c,d;
    c=a+b;
    d=c;
    printf("x=%d y=%d",d.x,d.y);
    return 0;
}
