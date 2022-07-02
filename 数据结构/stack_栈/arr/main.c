#include <stdio.h>
#include <stdlib.h>

#include "sqstack.h"

int main()
{
    
    sqstack *st;

    datatype arr[] ={19,23,0,45,67};

    st = st_create();

    for(int i=0;i<sizeof(arr)/sizeof(*arr); i++)
        st_push(st, &arr[i]);
    
    st_travel(st);

    datatype tmp;
    // st_top(st, &tmp);
    // printf("top = %d\n",tmp);

    st_pop(st, &tmp);
    st_travel(st);
    
    st_destroy(st);
    
    exit(0);
}
