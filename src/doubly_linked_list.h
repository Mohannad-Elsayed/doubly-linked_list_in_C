#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <assert.h>
#ifndef DOUBLY_LINKED_LIST_HEADER
#define DOUBLY_LINKED_LIST_HEADER 1


/*      SHOULD BE DEFINED BY THE USER      */
#ifndef ElementType
#define ElementType int
#endif /* ElementTypePtr */

/// @brief helper function to print an element of type `ElementType`
/// @param _E pointer to the element
void _printElement(ElementType *_E);
/// @brief helper function to traverse list elements
/// @param _E List element
int _traverseFunction(ElementType *_E);

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
int _traverseFunction(ElementTypePtr _E){
    printf("%d ", *_E);
    return 0;
}
#endif /* __traverseFunction */
#ifndef __printElement
#define __printElement
void _printElement(ElementTypePtr _E){
    printf("%d", *_E);
}
#endif /* __printElement */
/*  END SHOULD BE DEFINED BY THE USER      */

typedef unsigned long long ListSize;
typedef ElementType* ElementTypePtr;
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

static int _comp(ElementTypePtr _E1, ElementTypePtr _E2);
static int _makeEqualWithVal(ElementTypePtr _E);
static int _find(ElementTypePtr _E);
static int _count(ElementTypePtr _E);
static ListIterator _insert(Node *_pNode, ElementTypePtr _E);
static void _swap(ElementTypePtr *_E1, ElementTypePtr *_E2);
static ListIterator _makeNode(const ElementTypePtr const _E);
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
ListIterator insertAt(List *_list, ElementType _element, ListSize _index);
ListIterator insertAfter(List *_list, ElementType _element, ListIterator _it);
void append(List *source, List *destination);
void prepend(List *source, List *destination);

ListIterator eraseHead(List *_list);
ListIterator eraseTail(List *_list);
ListIterator erase(List *_list, ListIterator _it);
ListIterator eraseAt(List *_list, signed _index);
ListSize eraseVal(List *_list, ElementType val);

ListIterator find(List *_list, ElementType _element);
ListSize count(List *_list, ElementType _element);

ListSize traverse_headward(List *_list, int _pfun(ElementTypePtr _E));
ListSize traverse_tailward(List *_list, int _pfun(ElementTypePtr _E));

void reverse(List *_list);
void fill(List *_list, ElementType val);

void copy(List *_list1, List *_list2);
void printAllElements(List *_list, char *separator);

void swap(ListIterator _it1, ListIterator _it2);

#endif /* DOUBLY_LINKED_LIST_HEADER */
