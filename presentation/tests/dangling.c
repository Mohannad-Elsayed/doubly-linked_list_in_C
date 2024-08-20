#include <malloc.h>
int main(){
    int *p = malloc(4);
    *p = 4;
    free(p);
    free(p);
    return 0;
}