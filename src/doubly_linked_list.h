#include <stdio.h>
#include <malloc.h>
#ifndef DOUBLY_LINKED_LIST_h
#define DOUBLY_LINKED_LIST_h 1

/*      SHOULD BE DEFINED BY THE USER      */
#ifndef ElementType
#define ElementType int
#endif /* ElementType */
#ifndef equal
#define equal(a,b) (a) == (b)
#endif /* equal(a, b) */
#ifndef greater
#define greater(a, b) (a) > (b)
#endif /* greater(a, b) */
#ifndef smaller
#define smaller(a, b) (a) < (b)
#endif /* smaller(a, b) */
#ifndef __traverseFunction
#define __traverseFunction
/// @brief helper function to traverse list elements
/// @param _E 
int _traverseFunction(ElementType *_E){
    printf("%d ", *_E);
}
#endif /* __traverseFunction */
#ifndef __printElement
#define __printElement
/// @brief helper function to print an element of type `ElementType`
/// @param _E pointer to the element
void _printElement(ElementType *_E){
    printf("%d", *_E);
}
#endif /* __printElement */
/*  END SHOULD BE DEFINED BY THE USER      */

typedef unsigned long long ListSize;
typedef struct node {
    ElementType _val;
    struct node *_next, *_prev;
} Node;
typedef Node* ListIterator;
typedef struct list {
    Node *_head;
    Node *_tail;
    ListSize _size;
} List;

int _comp(ElementType *_E1, ElementType *_E2);
ElementType* _Val(ElementType *val);
int _makeEqualWithVal(ElementType *_E);
int _find(ElementType *_E);
int _count(ElementType *_E);
ListIterator _insert(Node *_pNode, ElementType *_E);
void _swap(ElementType *_E1, ElementType *_E2);
ListIterator _eraseNode(List *_list, Node *_node);

void create(List *_list);
void clear(List *_list);

ListIterator jump_headward(ListIterator _it, unsigned _step);
ListIterator jump_tailward(ListIterator _it, unsigned _step);
ListIterator next(ListIterator _it);
ListIterator prev(ListIterator _it);
ListIterator at(List *_list, signed _index);
ListIterator head(List *_list);
ListIterator tail(List *_list);

ElementType val(ListIterator _it);
ListSize size(List *_list);
int empty(List *_list);

ListIterator addHead(List *_list, ElementType val);
ListIterator addTail(List *_list, ElementType val);
ListIterator insertAt(List *_list, ElementType _element, ListSize _index);
void append(List *source, List *destination);
void prepend(List *source, List *destination);

ListIterator eraseHead(List *_list);
ListIterator eraseTail(List *_list);
ListIterator erase(List *_list, ListIterator _it);
ListIterator eraseAt(List *_list, signed _index);
ListSize eraseVal(List *_list, ElementType val);

ListSize find(List *_list, ElementType _element);
ListSize count(List *_list, ElementType _element);

ListSize traverse_headward(List *_list, int _pfun(ElementType *_E));
ListSize traverse_tailward(List *_list, int _pfun(ElementType *_E));

void reverse(List *_list);
void fill(List *_list, ElementType val);

void copy(List *_list1, List *_list2);
void printAllElements(List *_list, char *separator);

void swap(ListIterator _it1, ListIterator _it2);

#endif /* DOUBLY_LINKED_LIST */
