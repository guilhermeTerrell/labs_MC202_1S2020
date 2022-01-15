#include <stdio.h>


int main(){
    int *ptr;
    ptr=malloc(5*sizeof(int));
    printf("%d", ptr);
    return 0;
}
