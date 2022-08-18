#include<iostream>
class testA
{
private:
    int a1 = 999;
    void ret_t()
    {
        printf("aaaa\n");
    }
public:
    int a;
    void ret()
    {
        printf("testA.a1 is %d",a1);
        return ret_t();
    }
};
class testC
{
    public:
        int c=555;
};
//jicheng
class testB: public testA,public testC
{
    public:
        testB();
        ~testB();
        testB(const testB & obj);
        static void testpr()
        {
            printf("1111\n");
        }
        int c = 666;
        void print_s(int i)
        {
            printf("i is %d\n",i);
        }
        void print_s(double i)
        {
            printf("i is %f\n",i);
        }
        void setB(int i)
        {
            b = i;
        }
        void printB()
        {
            printf("testB_b is %d\n",b);
        }
        testB operator+(const testB& b)//+ - * /
        {
            testB box;
            printf("%d %d\n",this->b,b.b);
            box.b = this->b + b.b;
            return box;
        }
        testB operator-()//+ -
        {
            testB box;
            box.b = -this->b;
            return box;
        }
        bool operator <(const testB& d)// > < == >= <=
        {
            //d is hou date
            if(b < d.b)
            {
                return true;
            }
            return false;
        }
        testB operator--()//++ ---
        {
            testB box;
            box.b= --b;
            return box;
        }
        testB operator--(int)//++ ---
        {
            testB box;
            box.b= b--;
            return box;
        }
        void operator=(const testB& d)//=
        {
            this->b = d.b;
        }
    private:
        int b;
};
testB::~testB()
{
    //析构函数有助于在跳出程序（比如关闭文件、释放内存等）前释放资源
    printf("test_destory\n");

}
testB::testB(void)
{
    //构函数
    printf("test_create\n");
}
testB::testB(const testB & obj)
{
    printf("test_create\n");
}
int main()
{
    testB test,test1,test2;
    test.a = 1;
    printf("a is %d\n",test.a);
    testB *point;
    point = &test;
    //point->~testB();
    testB::testpr();
    test.ret();
    printf("ovw\n");
    printf("c is %d\n",test.c);
    test.print_s(1);
    test.print_s(1.1111);
    test.setB(9);
    test1.setB(2222);
    test1=-test1;
    test1.printB();
    test.printB();
    test2 = test1 + test;
    test2.printB();
    if(test1 < test)
    {
        printf("test1 < test\n");
    }
    printf("***********************\n");
    --test1;
    test1.printB();
    test1--;
    test1.printB();
    test2=test1;
    test2.printB();
}