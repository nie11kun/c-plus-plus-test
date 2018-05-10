#include <iostream>

using namespace std;

int main()
{
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
    cout << input1 + "\n";

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
    delete [] p;//delete array, pointed by p1.

    cout << "char: " << sizeof(char) << endl;
    int num[10];
    cout << sizeof(num) << endl;










    return 0;
}
//this is comment

/*
multi lines
*/


