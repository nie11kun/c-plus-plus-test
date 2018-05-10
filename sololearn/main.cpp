#include <iostream>
#include <cstdlib>//add random numbers
#include <ctime>


using namespace std;


void printSometing(int x);
void printSometing(float x);//overoad the same function
int timesTwo(int x);
int addNumbers(int x, int y);
int factorial(int n);
void printArray(int arrp[], int size);
void passRef(int *x);

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
