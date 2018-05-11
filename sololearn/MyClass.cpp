#include "MyClass.h"
#include <iostream>

using namespace std;

MyClass::MyClass(int a, int b, int c)
:segVar(a), segvar2(b), constVar(c)
{
    cout << segVar << endl;
    cout << constVar << endl;
}
MyClass::~MyClass()
{
    cout << "distructor" << endl;
}
void MyClass::myPrint() const
{
    cout << segVar << "," << constVar << endl;
}
MyClass MyClass::operator+(MyClass &obj)
{
    MyClass res(1, 2, 3);
    res.segVar = this->segVar + obj.segVar;
    res.segvar2 = this->segvar2 + obj.segvar2;
    return res;
}
