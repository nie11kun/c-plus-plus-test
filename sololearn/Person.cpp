#include "Person.h"
#include "Brithday.h"
#include <iostream>

using namespace std;

Person::Person(string a, Brithday b)
:name(a), bd(b)
{
}
void Person::printInfo()
{
    cout << name << endl;
    bd.printDate();
}
