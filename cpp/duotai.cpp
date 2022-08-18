#include<iostream>
#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fstream>
#include<fcntl.h>
#define X 'x'
typedef int f(int a,int b);
 using namespace std;
class A
{
    public:
        A(int a=1,int b=2)
        {
            width = a;
            longth = b;
        }
        A(int a)
        {
            width = 9;
            longth = 9;
        }
        virtual int area()
        {
            printf("this is A\n");
            return 1;
        }
        virtual int test(int a) = 0;
    protected:
        int width;
        int longth;
    public:
        int x = 1;
};

class B:public A
{
    public:
        B(int a=1,int b=1):A(a,b) {}
        virtual int area()
        {
            printf("this is B ,area is %d \n",width*longth);
            return 1;
        }
        int test(int a)
        {
            printf("test a is %d\n",a);
            return 0;
        }
        void openfile(int a);
        f(func);
};
int B::func(int a,int b)
{
    printf("a is %d ,b is %d",a,b);
}
void B::openfile(int a)
{
    width = 2;
    this->longth = 222;
}
int main()
{
    A *tess = NULL;
    //A a;
    B b(1,2);
    //tess = &b;
    //tess = &a;

    tess->area();
    //tess->test();
    printf("%d\n",b.x);

    //write read 
    //ofstream outfile;
    //outfile.open("afile.dat");

    int fd;
    fd = open("1.txt",O_RDWR);
    int ret = lseek(fd,0,SEEK_END);
    char buf[ret]={0};
    lseek(fd,0,SEEK_SET);
    printf("%d\n",ret);
    read(fd,buf,sizeof(buf));
    printf("%s\n",buf);

    delete tess;
    //数组申明
    B *test= new B();
    test[1].test(1);
    
    test[2].test(3);
    delete [] test;
    printf("%d   %c\n",__LINE__,X);
    cout << "Value of __LINE__ : " << __LINE__ << endl;
    cout << "Value of __FILE__ : " << __FILE__ << endl;
    cout << "Value of __DATE__ : " << __DATE__ << endl;
    cout << "Value of __TIME__ : " << __TIME__ << endl;
    
    B *point = new B(1,2);
    point->area();
    point->openfile(1);
    point->area();
    delete point;
}