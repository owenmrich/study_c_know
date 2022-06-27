#include<stdio.h>
#include<stdlib.h>
static void sort1(int a[],int size)
{
    int i, j, k;
    int tmp;
    for (i = 0; i < size; i++)
        printf("%d ", a[i]);
    printf("\n");
    for (i = 0; i < size-1; i++)
    {
        k = i;
        for (j = i+1; j < size; j++)
        {
            if (a[j] < a[k])
                k = j;
        }
        if(i!=k)
        {
            tmp = a[i];
            a[i] = a[k];
            a[k] = tmp; 
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