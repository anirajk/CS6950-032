#include<stdio.h>
#include<stdbool.h>
#include<math.h>
bool predicate(void * bval) {
    int value = malloc(sizeof(int));
    int i, s;
    value = (int) bval;
    if (value <2)
        return false;
    if (value == 2)
        return true;
    s = (int)ceil(sqrt(value));
    printf("\nvalue:%d, squareroot:%d",value,s);
    for(i=2;i<=s;i++) {
        if (value % i == 0)
            return false;
   }
   return true;
}


