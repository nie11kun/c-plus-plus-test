#ifndef MYCLASS_H
#define MYCLASS_H


class MyClass
{
    public:
        MyClass(int a,int b, int c);
        ~MyClass();
        void myPrint() const;
        MyClass operator+(MyClass &obj);
    protected:

    private:
        int segVar;
        int segvar2;
        const int constVar;
};

#endif // MYCLASS_H
