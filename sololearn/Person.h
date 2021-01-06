#ifndef PERSON_H
#define PERSON_H
#include "Brithday.h"
#include <iostream>

using namespace std;

class Person
{
    public:
        Person(string a, Brithday b);
        void printInfo();
        friend void nameValue(Person &obj);
    protected:

    private:
        string name;
        Brithday bd;
};

#endif // PERSON_H
