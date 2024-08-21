#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <assert.h>
#ifndef DOUBLY_LINKED_LIST_H
#define DOUBLY_LINKED_LIST_H 1


/*      SHOULD BE DEFINED BY THE USER      */
#ifndef ElementType
#define ElementType int
typedef ElementType* ElementTypePtr;
#endif /* ElementType */
#ifndef __compare_functions
#define __compare_functions
int equal(ElementTypePtr _E1, ElementTypePtr _E2){
    return *_E1 == *_E2;
}
int greater(ElementTypePtr _E1, ElementTypePtr _E2){
    return *_E1 > *_E2;
}
int smaller(ElementTypePtr _E1, ElementTypePtr _E2){
    return *_E1 < *_E2;
}
typedef struct compare_struct {
    void *equal, *greater, *smaller;
} CompareStruct;
CompareStruct compareInt = {equal, greater, smaller};
#endif /* __compare_functions */
#ifndef __printElement
#define __printElement
void _printElement(ElementType *_E){
    printf("%d", *_E);
}
#endif /* __printElement */
#ifndef __traverseFunction
#define __traverseFunction
int _traverseFunction(ElementType *_E){
    _printElement(_E);
    return 0;
}
#endif /* __traverseFunction */
/*  END SHOULD BE DEFINED BY THE USER      */

typedef unsigned long long ListSize;
typedef struct node {
    ElementTypePtr _val;
    struct node *_next, *_prev;
} Node;
typedef Node* ListIterator;
typedef struct list {
    Node *_head;
    Node *_tail;
    ListSize _size;
} List;

static int _comp(ElementTypePtr _E1,
                 ElementTypePtr _E2,
                 int equal_fun(ElementTypePtr _E1, ElementTypePtr _E2),
                 int greater_fun(ElementTypePtr _E1, ElementTypePtr _E2));
static int _makeEqualWithVal(ElementTypePtr _E);
static ListIterator _insert(Node *_pNode, ElementTypePtr _E);
static void _swap(ElementTypePtr *_E1, ElementTypePtr *_E2);
static ListIterator _makeNode(const ElementTypePtr _E);
static void _freeNode(ListIterator _pNode);
static ListIterator _eraseNode(List *_list, Node *_node);
void create(List *_list);
void clear(List *_list);

ListIterator jump_headward(ListIterator _it, unsigned _step);
ListIterator jump_tailward(ListIterator _it, unsigned _step);
ListIterator next(ListIterator _it);
ListIterator prev(ListIterator _it);
ListIterator at(List *_list, signed _index);
ListIterator head(List *_list);
ListIterator tail(List *_list);

ElementTypePtr val(ListIterator _it);
ListSize size(List *_list);
int empty(List *_list);

ListIterator addHead(List *_list, ElementType val);
ListIterator addTail(List *_list, ElementType val);
ListIterator insertAt(List *_list, ElementType _element, signed _index);
ListIterator insertAfter(List *_list, ElementType _element, ListIterator _it);
void append(List *source, List *destination);
void prepend(List *source, List *destination);

ListIterator eraseHead(List *_list);
ListIterator eraseTail(List *_list);
ListIterator erase(List *_list, ListIterator _it);
ListIterator eraseAt(List *_list, signed _index);
ListSize eraseVal(List *_list, ElementType val, int equal_fun(ElementTypePtr _E1, ElementTypePtr _E2));

ListIterator find(List *_list, ElementType _element, int equal_fun(ElementTypePtr _E1, ElementTypePtr _E2));
ListSize count(List *_list, ElementType _element, int equal_fun(ElementTypePtr _E1, ElementTypePtr _E2));

ListSize traverse_headward(List *_list, int _pfun(ElementTypePtr _E));
ListSize traverse_tailward(List *_list, int _pfun(ElementTypePtr _E));

void reverse(List *_list);
void fill(List *_list, ElementType val);

void copy(List *_list1, List *_list2);
void printAllElements(List *_list, char *separator);

void swap(ListIterator _it1, ListIterator _it2);
int compare(List *_list1, List *_list2, int equal_fun(ElementTypePtr _E1, ElementTypePtr _E2));

#endif /* DOUBLY_LINKED_LIST_H */