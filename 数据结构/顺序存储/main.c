#include <stdio.h>
#include <stdlib.h>

#include "sqlist.h"

int sqlist_init(sqlist ** ls, datatype *arr, int size, int createtype)
{
    //  printf("init %p %p %p %p\n",&ls, ls ,*ls, &(*ls));
    
    if (createtype == 1)
        *ls = sqlist_create();
    if (createtype == 2)
        sqlist_create2(&(*ls));

    if(*ls == NULL)
        return -1;

    int err;
    for(int i = 0; i < size; i++)
    {
        if((err = sqlist_insert(*ls, 0, arr + i)) != 0)
        {
            if(err == -1)
                fprintf(stderr, "The arr is full.\n");
            else if(err == -2)
                fprintf(stderr, "The insert position is wrong.\n");
            else
                fprintf(stderr, "error.\n");
            return -1;   
        }
    }

    // printf("init %p last = %d\n",*ls, (*ls)->last);
    return 0;
}

int main()
{
    
    sqlist *list = NULL;
    sqlist *list2 = NULL;
    datatype arr[] ={12, 23, 34, 45, 56};
    datatype arr2[] ={89, 90, 78, 67, 56, 45};

    // printf("main %p %p\n",&list, list);

    if(sqlist_init(&list, arr, sizeof(arr)/sizeof(*arr), 1)== -1)
    {
        fprintf(stderr, "list init() failed!\n");
        exit(1);
    }

    // printf("main %p last = %d\n",list, list->last);

    // printf("\n\nmain %p %p\n",&list2, list2);

    if(sqlist_init(&list2, arr2, sizeof(arr2)/sizeof(*arr2), 2)== -1)
    {
        fprintf(stderr, "list2 init() failed!\n");
        exit(1);
    }

    // printf("main %p last = %d\n",list2, list2->last);

    sqlist_display(list);

    sqlist_display(list2);


    int x = 34;

    printf("find 34 = %d\n", sqlist_find(list, &x));

    sqlist_union(list, list2);

    sqlist_display(list);

    
    sqlist_destroy(list);

    sqlist_destroy(list2);
   
    exit(0);
}
