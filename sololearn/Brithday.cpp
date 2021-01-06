#include "Brithday.h"
#include <iostream>

using namespace std;

Brithday::Brithday(int a, int b, int c)
:month(a), day(b), year(c)
{
}
void Brithday::printDate()
{
    cout << month << "/" << this->day << "/" << (*this).year << endl;//this is a pointer point self.
}
