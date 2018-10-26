#include <iostream>
#include <cstdlib>//add random numbers
#include <ctime>
#include "MyClass.h"
#include "Brithday.h"
#include "Person.h"
#include "fstream"
#include <string>
#include <boost/filesystem.hpp>


using namespace std;
namespace fs = boost::filesystem;


void printSometing(int x);
void printSometing(float x);//overoad the same function
int timesTwo(int x);
int addNumbers(int x, int y);
int factorial(int n);
void printArray(int arrp[], int size);
void passRef(int *x);
void nameValue(Person &obj);

string strTest(string x, char y)
{
    string line;
    int i = x.find_first_of(y);
    line = x.substr(0, i);
    return line;
}

template <class T>
class TestSpeac
{
public:
    TestSpeac(T x)
    {
        cout << x << " - not a char" << endl;
    }
};
template <>//Template Specialization
class TestSpeac<char>
{
public:
    TestSpeac(char x)
    {
        cout << x << " - is a char" << endl;
    }
};


template <class T>
class PairValue
{
private:
    T frist, second;
public:
    PairValue(T a, T b)
    :frist(a), second(b)
    {
    }
    T bigger();//define the function out of the class.
};
template <class T>
T PairValue<T>::bigger()//define the template function out of the class in this way. may be in different files.
{
    return (frist > second ? frist: second);
}


template <class T, class U>
T smaller(T a, U b)
{
    return (a<b ? a : b);
}

template <class T>//or can be like: template <typename  T>.
T sumT(T a, T b)
{
    return a + b;
}

class Enemy
{
public:
    void setAttackPower(int a)
    {
        attackPower = a;
    }
    virtual void attack()//virtual function used to make it possible direct control derived class. pointer.
    //virtual void attack() ==0 // pure virtual function. this is abstract class. only been use as base class.
    {
    }
protected:
    int attackPower;
};

class Ninja: public Enemy
{
public:
    void attack()
    {
        cout << "Ninja! - " << attackPower << endl;
    }
};

class Monster: public Enemy
{
public:
    void attack()
    {
        cout << "Monster! - " << attackPower << endl;
    }
};


class Mother
{
public:
    Mother()
    {
        cout << "mother ctor" << endl;
    }
    ~Mother()
    {
        cout << "mother dtor" << endl;
    }
    void sayHi()
    {
        cout << "Hi" << endl;
    }
};
class Daughter: public Mother//public members been inherited as public, if is protected: public and protected members as protected member in new class, private: both is as private in new class. private is default mode.
{
public:
    Daughter()
    {
        cout << "daughter ctor" << endl;
    }
    ~Daughter()
    {
        cout << "daughter dtor" << endl;
    }
};



class BankAccount {
public:
    BankAccount(string x) {   //constructors, suto executed when class be instanted.used to set default values.
        name = x;
    }
    void setName(string x)
    {
        name = x;
    }
    string getName()
    {
        return name;
    }
private://default is private
    string name;
};

class Test1 {
public:
    Test1(int x): var1(x) {//init const value must in this way.

    }
private:
    const int var1;
};

int main()
{
    srand(time(0));//time(0) is current time seconds, srand is used to use and seed value to generate random numbers use rand()

    cout << "Hello world!" << "this is marco!" << endl;
    cout << "this is my first c++ project.\n\n";
    cout << "new line" << endl;
    int myVarible = 10;
    cout << myVarible << endl;

    int var1 = 2;
    int var2 = 3;
    int sum1 = var1 + var2;
    cout << sum1 << endl;

    int input1;
    cin >> input1;
    cout << input1 << "\n";

    if (2 > 3) {
        cout << "true\n";
    }
    else {
        cout << "false\n";
    }

    int age = 8;
    if (age > 14) {
        if (age >= 18) {
            cout << "adult\n";
        }
        else {
            cout << "teenage\n";
        }
    }
    else {
        if (age > 0) {
            cout << "child\n";
        }
        else {
            cout << "error\n";
        }
    }

    if (2 > 3)
        cout << "if only one statment, no need braces\n";
    else
        cout << "if only one statment, no need braces\n";

    int var3 = 0;
    while (var3 < 3) {
        cout << var3 << endl;
        var3++;
    }

    int var5 = 1;
    int var6;
    int var7 = 0;
    while (var5 <= 2) {
        cin >> var6;
        var7 += var6;
        var5++;
    }
    cout << var7 << endl;


    for (int i = 0; i < 5; i++) {
        cout << i << endl;
    }

    int var9 = 0;
    do {
        cout << var9 << endl;
        var9++;
    } while(var9 < 3);


    int var10 = 16;
    switch (var10) {
    case 16:
        cout << "is 16.\n";
        break;
    case 20:
        cout << "adult.\n";
        break;
    default:
        cout << "is default.\n";
    }

    //&& || !
    if (20 > 10 && 2 < 3) {
        cout << "right\n";
    }


    //singed unsigned long short
    unsigned long int var11 = 4;
    //float double long double, always is signed.
    double temp = 2.4;

    string str1 = "this is strings";
    char ca1 = 'A';
    bool b1 = true;

    int a[5] = {1, 2, 3, 4, 5};
    cout << a[0] << endl;

    int b[2][3] = {{1, 2, 3}, {4, 5, 6}};
    cout << b[0][2] << endl;
    cout << &b[0][1] << endl;

    int *ip;
    int var13 = 5;
    ip = &var13;
    *ip += 3;
    cout << ip << endl;
    cout << *ip << endl;

    int *p = new int;//request memory.
    *p = 5;
    cout << *p << endl;
    delete p;//free up memory.

    int *p1 = NULL;
    p1 = new int[5];
    delete p1;//delete array, pointed by p1.

    cout << "char: " << sizeof(char) << endl;
    int num[10];
    cout << sizeof(num) << endl;

    float var15 = 45.678;
    printSometing(23);
    printSometing(var15);

    cout << timesTwo(45) << endl;

    cout << addNumbers(3, 5) << endl;

    for (int x = 0; x < 5; x++) {
        cout << 1 +(rand() % 6) << endl;
    }


    cout << factorial(5) << endl;

    int myArr[3] = {33, 44, 55};
    printArray(myArr, 3);

    int var17 = 20;
    passRef(&var17);//referenced in the function
    cout << "var17: " << var17 <<endl;

    BankAccount test1("jim");
    //test1.setName("marco");
    cout << test1.getName() << endl;

    const MyClass obj1(1, 3, 4);
    obj1.myPrint();//only constant behavir can be use in const instance.

    const MyClass *ptr = &obj1;
    ptr->myPrint();


    Brithday br1(11, 25, 1989);
    Person ps1("marco", br1);
    ps1.printInfo();

    nameValue(ps1);//access private value, using friend function.
    ps1.printInfo();


    MyClass cls1(1, 2, 3);
    MyClass cls2(2, 3, 4);
    MyClass cls3 = cls1 + cls2;
    cls3.myPrint();

    Daughter d;
    d.sayHi();

    Ninja n;
    Monster m;
    Enemy *p11 = &n;
    Enemy *p22 = &m;
    p11->setAttackPower(15);
    p22->setAttackPower(20);
    p11->attack();
    p22->attack();


    double var20 = 7.5, var21 = 8.9;
    cout << sumT(var20, var21) << endl;

    PairValue <int> obj3(2, 6);//template class must define the type when use.
    cout << obj3.bigger() << endl;
    PairValue <double> obj4(3.5, 5.7);
    cout << obj4.bigger() << endl;


    TestSpeac<int> obj5(5);//Template Specialization
    TestSpeac<char> obj6(';');


    try {
        int sonAge = 10;
        int dadAge = 5;
        if (sonAge > dadAge) {
            throw 99;
        }
    }
    catch(int x) {// ... catch every condition.
        cout << "Wrong age values - Error " << x << endl;
    }


    fstream Myfile1;
    Myfile1.open("test1.txt", ios::app);//ios::trunc-delete content if have content.
    if (Myfile1.is_open()) {
        Myfile1 << "this is a test.\n";
    }
    else {
        cout << "something was wrong.";
    }
    Myfile1.close();


    fstream Myfile2("test1.txt");
    string line;
    string newline;
    while(getline(Myfile2, line)) {
        newline += strTest(line, 'a') + "\n";
    }
    Myfile2.close();

    ofstream Myfile3;
    Myfile3.open("B_DRESS.SPF", ios::trunc);
    Myfile3 << newline;
    Myfile3.close();



    return 0;
}
//this is comment

/*
multi lines
*/

void printSometing(int x)
{
    cout << x << endl;
}

void printSometing(float x)
{
    cout << x << endl;
}

int timesTwo(int x)
{
    return x*2;
}

int addNumbers(int x, int y)
{
    int result = x + y;
    return result;
}

int factorial(int n)//reursion function.
{
    if (n == 1) {
        return 1;
    }
    else {
        return n * factorial(n-1);
    }
}

void printArray(int arrp[], int size)
{
    for (int x = 0; x < size; x++) {
        cout << arrp[x] << endl;
    }
}

void passRef(int *x)//pass by reference.
{
    *x = 100;
}

void nameValue(Person &obj)//friend function defined in person.h
{
    obj.name = "marco nie";
}

typedef struct   //same as below defined look in c++
{
    int a, b;
}
point;

struct point1
{
    int a, b;
}

point1 add(point1 a, point1 b)
{
    point1 c;
    c.a = a.a + b.a;
    c.b = a.b + b.b;
    return c;
}

int abc;

abc def;

