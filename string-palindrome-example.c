#include <stdio.h>
#define ElementType char
typedef ElementType* ElementTypePtr;
#define __printElement
void _printElement(ElementTypePtr p){
    printf("%c", *p);
}
#include "src/doubly_linked_list.c"
int main(){
    List str;
    create(&str);
    addTail(&str, 'a');
    addTail(&str, 'a');
    addTail(&str, 'a');
    addTail(&str, 'b');
    addTail(&str, 'b');
    addTail(&str, 'a');
    addTail(&str, 'a');
    addTail(&str, 'a');
    addTail(&str, 'a');
    printAllElements(&str, "");
    List revstr;
    create(&revstr);
    copy(&str, &revstr);
    reverse(&revstr);
    printf("\n%s\n", (compare(&str, &revstr, equal) ? "Palindrome" : "Not Palindrome"));
    clear(&str);
}