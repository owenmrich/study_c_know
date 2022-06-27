#include<stdio.h>
#include<stdlib.h>
static void sort1(int a[],int size)
{
    int i, j;
    int tmp;
    for (i = 0; i < size; i++)
        printf("%d ", a[i]);
    printf("\n");
    for (i = 0; i < size; i++)
    {
        for (j = 0; j < size - 1 - i; j++)
        {
            if (a[j] > a[j + 1])
            {
                tmp = a[j];
                a[j] = a[j+1];
                a[j+1] = tmp;
            }
        }
    }
    for (i = 0; i < size; i++)
        printf("%d ", a[i]);
    printf("\n");
}
int main(int argc, char** argv)
{
    int size; 
    int a[10] = { 9,5,8,7,3,6,2,4,1,2 };
    size = sizeof(a) / sizeof(a[0]);
    printf("size = %d\n", size);
    sort1(a,size);
    return 0;
}