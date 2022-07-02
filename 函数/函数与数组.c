#include<stdio.h>
#include<stdlib.h>
void change_ad(int arr[],int size)//传入的为指针 == (int *p ,int size)
{
    int i,j,tmp;
    //int size = sizeof(arr) / sizeof(*arr);所以size 为2 = 8/4
    for (i = 0;i < size; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");
    int n = (size - 1) / 2;
    for (i = 0; i < n; i++)
    {
        j = size - 1 - i;
        tmp = arr[i];
        arr[i] = arr[j];
        arr[j] = tmp;
    }
    for (i = 0; i < size; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");    
}

//二维数组
void arr_2(int *p,int size)//把二维数组当作一维数组使用
{
    int i;
    for ( i = 0; i < size; i++)
    {
        printf("%d ", *(p+i));
    }
    
}
void arr_1(int (*p)[2], int a, int b)//int p[][2]
{
    int i,j;
    for (i = 0; i < a; i++)
    {
        for (j = 0; j < b; j++)
        {
            printf("%4d ", *(*(p + i) + j));
        }
        printf("\n");
    }

}
char* cpy(char* p, const char* q)
{
    char* ret = p;
    if (p != NULL && q != NULL)
        while ((*p++ = *q++) != '\0');
            
    return ret;
}
int main()
{

    int arr[5] = { 1,2,3,4,5 };
    int size = sizeof(arr) / sizeof(*arr);
    change_ad(arr,size);
    int arr2[2][3] = { 1,2,3,4,5,6 };
    size = sizeof(arr2) / sizeof(arr2[0][0]);
    printf("size is %d \n", size);
    arr_2(*arr2, size);//把二维数组当作一维数组对待 *a a[0] *(a+0) &a[][]
    int col = sizeof(arr2[0]) / sizeof(arr2[0][0]);//求二维数组的列数
    int line = size / col;//求二维数组的行数
    arr_1(arr2, line, col);
    char str1[10] = {"123"};
    char str2[5] = {"asd"};
    cpy(&str1, &str2);
    puts(str2);

    exit(0);
}