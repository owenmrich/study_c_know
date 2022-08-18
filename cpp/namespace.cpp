#include<iostream>
#include<fstream>
class A
{
    public:
        void func()
        {
            printf("class");
        }
};
namespace test
{
    void func()
    {
        printf("test\n");
    }
}
namespace test1
{
    void func()
    {
        printf("test1\n");
    }
    namespace test2
    {
        void func2()
        {
            printf("test2\n");
        }
    }
}
int main()
{
    test::func();
    test1::func();
    test1::test2::func2();

}