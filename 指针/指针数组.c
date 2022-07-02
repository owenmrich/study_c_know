#include<stdio.h>
#include<stdlib.h>
#include<string.h>
int main()
{
    int j = 0, k;
    int i[3] = { 1,2,3 };
    int arr[2][3] = { 1,2,3,4,5,6 };
    int* p = i;
    int* p1 = &arr[0][0];
    for (j = 0; j < 6; j++)
    {
        printf("i is %d, its ard is %p\n", p1[j], &(p1[j]));
    }
    int* p2 = *arr;//相对于二级指针取地址
    for (j = 0; j < 3; j++)
    {
        printf("i is %d, its ard is %p\n", i[j], p + j);
        printf("i is %d, its ard is %p\n", *(p + j), &i[j]);

    }
    printf("+++++++\n");
    for (j = 0; j < 2; j++)
    {
        for (k = 0; k < 3; k++)
        {
            printf("i is %d, its ard is %p\n", *(*(arr + j) + k), *(arr + j) + k);
        }
    }

    //数组指针
#if 0
    213213213
#endif
        int(*q)[3] = arr;
    for (j = 0; j < 2; j++)
    {
        for (k = 0; k < 3; k++)
        {
            printf("i is %d, its ard is %p\n", *(*(q + j) + k), *(q + j) + k);
        }
    }
    //指针数组
        int *arr1[3] = {"abc","wee","ooo"};
        int i, j, k;
        char* tmp;
    for (i = 0; i < 5; i++)
        printf("%d ", arr[i]);
    printf("\n");
    for (i = 0; i < 5-1; i++)
    {
        k = i;
        for (j = i+1; j < 5; j++)
        {
            if (strcmp(arr[k],arr[j]) > 0)
                k = j;
        }
        if(i!=k)
        {
            tmp = arr[i];
            arr[i] = arr[k];
            arr[k] = tmp; 
        }
    }

    //字符指针
    char str[10] = "love";
    char* qc = str + 1;
    puts(qc);
    puts(str);
    strcpy(str,"owen");
    puts(str);

    return 0;
}