/*
TODO

    ?swap
    ?reverse list
    ?find
    ?count
    ?insert
    ?traverse-headward, tailward
    ?iterators, front, back, next, prev, jump
    ?indexing, negative indexing
    //inbetween pointer to speed up insertion
    ?head, tail naming

    //circular

    prototypes in a .h file
    generic using void pointers
    a proper API
    licence

NodeType
ListSize
node
list

_comp
_traversfunction
_printElement
_Val
__
_find
_count
_insert
_swap
_removeNode

makeList
clear
jump_headward
jump_tailward
next
prev
at
head
tail
val
size
empty

addHead
addTail
insert
append
prepend

removeHead
removeTail
erase
eraseAt
removeVal

find
count

traverse_headward
traverse_tailward
reverse
fill
copy
swap
printAllElements
*/

#include <stdio.h>
#include <malloc.h>
#include "types.h"
/*
typedef int NodeType;
typedef unsigned long long ListSize;
typedef struct node {
    NodeType _val;
    struct node *_next, *_prev;
} Node;
typedef Node* ListIterator;
typedef struct list {
    Node *_head;
    Node *_tail;
    ListSize _size;
} List;

#define equal(a,b) (a) == (b)
#define greater(a, b) a > b
#define smaller(a, b) a < b
*/

/// @brief helper function compares two elements of type `NodeType`
/// @return `1` if element 1 greater than element 2, `0` if both are equal, `-1` if element 1 is smaller than element 2
int _comp(NodeType *_E1, NodeType *_E2){
    if (equal(*_E1, *_E2))
        return 0;
    else if (greater(*_E1, *_E2))
        return 1;
    else 
        return -1;
}
/// @brief helper function to traverse list elements
/// @param _E 
void _traverseFunction(NodeType *_E){
    printf("%d ", *_E);
}
/// @brief helper function to print an element of type `NodeType`
/// @param _E pointer to the element
void _printElement(NodeType *_E){
    printf("%d", *_E);
}
/// @brief helper function to hold the filling value in a static place in memory 
/// @param val a pointer to the value to be filled
/// @return a pointer to the place in memory in which the filling value is stored
// TODO refactor
NodeType* _Val(NodeType *val){
    static NodeType *_val = NULL;
    if (_val) 
        return _val;
    _val = val;
    return _val;
}
/// @brief helper function to make a list element's value equal to a given value
/// @param _E the list element's value
int _makeEqualWithVal(NodeType *_E){
    *_E = *_Val((NodeType*)0);
    return 0;
}
/// @brief helper function for function `find()` to compare two elements
/// @return `1` if two elements are equal, `0` otherwise
int _find(NodeType *_E){
    return !_comp(_Val((NodeType*)0), _E);
}
/// @brief helper function for function `find()` to compare two elements
/// @return `1` if two elements are equal, `0` otherwise
int _count(NodeType *_E){
    return !_comp(_Val((NodeType*)0), _E);
}
/// @brief helper function to allocate, insert a node after a specified node
/// @param _pNode a pointer to the current node
/// @param _E the element to be inserted
/// @return `1` in case of successful insertion, `0` otherwise
int _insert(Node *_pNode, NodeType *_E){
    Node *__pNode = (Node *)malloc(sizeof(Node));
    if (__pNode){
        __pNode -> _val = *_E;
        __pNode -> _prev = _pNode;
        __pNode -> _next = _pNode -> _next;
        _pNode -> _next -> _prev = __pNode;
        _pNode -> _next = __pNode;
        return 1;
    }
    return 0;
}
/// @brief a helper function swaps two elements
/// @param _E1 pointer to the first element
/// @param _E2 pointer to the second element
void _swap(NodeType *_E1, NodeType *_E2){
    NodeType _T = *_E1;
    *_E1 = *_E2;
    *_E2 = _T;
}
/// @brief helper function to erase an element in the list
/// @param _list pointer to the list
/// @param _node pointer to the element to be erased
/// @return a pointer the next element in the list to the left, if no such elements, returns `Null`
// TODO refactor
ListIterator _eraseNode(List *_list, Node *_node){
    Node *retNode = _node -> _next;
    if (_node -> _prev)
        _node -> _prev -> _next = _node -> _next;
    else
        _list -> _head = _node -> _next;
    if (_node -> _next)
        _node -> _next -> _prev = _node -> _prev;
    else
        _list -> _tail = _node -> _prev;
    free(_node);
    _list -> _size--;
    return retNode;
}

/// @brief initializes the list pointers to `NULL` and the list size to 0
/// @param _list a pointer to the list
void create(List *_list){
    _list -> _head = NULL;
    _list -> _tail  = NULL;
    _list -> _size  = 0;
}
/// @brief erases all elements in the list
/// @param _list a pointer to the list
void clear(List *_list){
    while(_list -> _size)
        eraseHead(_list);
}
/// @brief skips elements in the list in the TAIL direction
/// @param _it an iterator to the current element
/// @param _step number of elements to be skiped
/// @return an iterator to the element in case it's a valid element in the list, `NULL` otherwise
ListIterator jump_headward(ListIterator _it, unsigned _step){
    while(_it && _step--)
        _it = _it -> _next;
    return _it;
}
/// @brief skips elements in the list to the head
/// @param _it an iterator to the current element
/// @param _step number of elements to be skipeed
/// @return `1` if the final element is a valid element in the list, `0` otherwise
int jump_tailward(ListIterator *_it, unsigned _step){
    while((*_it) && _step--)
        (*_it) = (*_it) -> _prev;
    return *_it != NULL;
}
/// @brief advances the iterator to the tail by 1 step
/// @param _it an iterator to the current element
/// @return `1` on success, `0` on failure
int next(ListIterator *_it){
    if (*_it)
        return (*_it) = (*_it) -> _next, 1;
    return 0;
}
/// @brief advances the iterator to the head by 1 step
/// @param _it an iterator to the current element
/// @return `1` on success, `0` on failure
int prev(ListIterator *_it){
    if (*_it)
        return (*_it) = (*_it) -> _prev, 1;
    return 0;
}
/// @brief get an iterator pointing at the element in the specified index, including negative indexing
/// @attention `0` is the first element at the head, `-1` is the last element at the tail, `-2` is second to last, ...
/// @param _list a pointer to the list 
/// @param _index index of the element `[-size, size-1]` inclusive
/// @return an iterator points at the element at the index
ListIterator at(List *_list, signed _index){
    if (_index < 0)
        _index += _list -> _size;
    if (_index >= _list -> _size || _index < 0)
        return NULL;
    return jump_headward(head(_list), _index);
}
/// @param _list a pointer to the list
/// @return returns an iterator to the Head element in the list
ListIterator head(List *_list){
    return _list -> _head;
}
/// @param _list a pointer to the list
/// @return returns an iterator to the Tail element in the list
ListIterator tail(List *_list){
    return _list -> _tail;
}
/// @param _it an iterator to the current element
/// @return the value pointed to by the iterator
/// @attention the function doesn't check the iterator's validity
NodeType val(ListIterator _it){
    return _it -> _val;
}
/// @return returns the number of elements in the list
ListSize size(List *_list){
    return _list -> _size;
}
/// @return `1` if the list has no elements, `0` otherwise
int empty(List *_list){
    return !(_list -> _size);
}
/// @brief appends an element to the start (Head side) of the list
/// @param _list a pointer to the list
/// @param val the value to be added
/// @return iterator to the element in success addition, `NULL` in failure
// TODO make NodeType reference type
ListIterator addHead(List *_list, NodeType val){
    Node *_pNode = (ListIterator)malloc(sizeof(Node));
    if (_pNode){
        Node *__pNode = _list -> _head;
        _list -> _head = _pNode;
        _pNode -> _prev = NULL;
        _pNode -> _next = __pNode;
        if (__pNode)
            __pNode -> _prev = _pNode;
        else
            _list -> _tail = _pNode;
        _pNode -> _val = val;
        _list -> _size++;
        return __pNode;
    }
    return NULL;
}
/// @brief appends an element to the end (Tail side) of the list
/// @param _list a pointer to the list
/// @param val the value to be added
/// @return iterator to the element in success addition, `NULL` in failure
// TODO make NodeType reference type
ListIterator addTail(List *_list, NodeType val){
    Node *_pNode = (ListIterator)malloc(sizeof(Node));
    if (_pNode){
        Node *__pNode = _list -> _tail;
        _list -> _tail = _pNode;
        _pNode -> _prev = __pNode;
        _pNode -> _next = NULL;
        if (__pNode)
            __pNode -> _next = _pNode;
        else
            _list -> _head = _pNode;
        _pNode -> _val = val;
        _list -> _size++;
        return __pNode;
    }
    return NULL;
}
/// @brief insert an element in the specified index
/// @param _list a pointer to the list
/// @param _element element to be inserted
/// @param _index the index, must be [0, size -1] inclusive
/// @return `1` in case of successful insertion, `0` otherwise
int insert(List *_list, NodeType _element, ListSize _index){
    if (_index >= _list -> _size)
        return 0;
    if (_index == 0)
        return addHead(_list, _element);
    Node *_pNode = _list -> _head;
    while(--_index)
        _pNode = _pNode -> _next;
    if (_insert(_pNode, &_element)){
        _list -> _size++;
        return 1;
    }
    return 0;
}
/// @brief append all elements in `source` to the Tail of `destination`
/// @param source
/// @param destination
void append(List *source, List *destination){
    Node *_pSrcNode = source -> _head;
    while(_pSrcNode){
        addTail(destination, _pSrcNode -> _val);
        _pSrcNode = _pSrcNode -> _next;
    }
}
/// @brief prepend all elements in `source` to the Head of `destination`
/// @param source
/// @param destination
void prepend(List *source, List *destination){
    Node *_pSrcNode = source -> _tail;
    while(_pSrcNode){
        addHead(destination, _pSrcNode -> _val);
        _pSrcNode = _pSrcNode -> _prev;
    }
}
/// @brief erases the Head element in the list (the left most element)
/// @param _list a pointer the the list
/// @returns iterator to the new HEAD in success removal, `NULL` if the list is empty before or after the removal
ListIterator eraseHead(List *_list){
    if (!_list -> _size){
        _list -> _head = _list -> _tail = NULL;
        return NULL;
    }
    Node *_pNode = _list -> _head;
    _list -> _head = _list -> _head -> _next;
    free(_pNode);
    _list -> _size--;
    if (!_list -> _size){
        _list -> _head = _list -> _tail = NULL;
    }
    return _list -> _head;
}
/// @brief erases the Tail element in the list (the right most element)
/// @param _list a pointer the the list
/// @returns iterator to the new TAIL in success removal, `NULL` if the list is empty before or after the removal
ListIterator eraseTail(List *_list){
    if (!_list -> _size){
        _list -> _head = _list -> _tail = NULL;
        return NULL;
    }
    Node *_pNode = _list -> _tail;
    _list -> _tail = _list -> _tail -> _prev;
    free(_pNode);
    _list -> _size--;
    if (!_list -> _size){
        _list -> _head = _list -> _tail = NULL;
    }
    return _list -> _tail;
}
/// @brief erases the element pointed to by an iterator
/// @param _list a pointer to the list
/// @param _it an iterator points at the element to be deleted
/// @return an iterator points at the next element in the list, `NULL` if it's the last element
ListIterator erase(List *_list, ListIterator _it){
    return _eraseNode(_list, _it);
}
/// @brief erases an element at a specific index in the list, including negative indexes
/// @attention `0` is the first element at the head, `-1` is the last element at the tail, `-2` is second to last, ...
/// @param _list a pointer to the list
/// @param _index index of the element to be deleted
/// @return an iterator points at the next element in the list, `NULL` if it's the last element
ListIterator eraseAt(List *_list, signed _index){
    return erase(_list, at(_list, _index));
}
/// @brief erases all occurrences of a particular value from te list
/// @param _list a pointer to the list
/// @param val the value to be erased 
/// @return number of elements erased
int eraseVal(List *_list, NodeType val){
    Node *_pNode = _list -> _head;
    int _flag = 0;
    while (_pNode){
        NodeType *_pNodeType = &(_pNode -> _val);
        if (!_comp(_pNodeType, &val)){
            _pNode = _eraseNode(_list, _pNode);
            _flag++;
        }
        else
            _pNode = _pNode -> _next;
    }
    return _flag;
}
/// @brief finds an element inside a list 
/// @param _list a pointer to the list
/// @param _element element to be found
/// @return `1` if the element is present in the list, `0` otherwise
ListSize find(List *_list, NodeType _element){
    _Val(&_element);
    return !(!traverse_headward(_list, _find));
}
/// @brief count the number of element occurrences in the list
/// @param _list a pointer to the list
/// @param _element element to be counted
/// @return number of elements matched 
ListSize count(List *_list, NodeType _element){
    _Val(&_element);
    return traverse_headward(_list, _count);
}
/// @brief traverse the elements of the list with a special function (from Head to Tail)
/// @param _list a pointer to the list
/// @param _pfun function pointer that do work on the elements inside list nodes
/// @returns accumulation of the traversal function return
ListSize traverse_headward(List *_list, int _pfun(NodeType *_E)){
    Node *_pNode = _list -> _head;
    ListSize result = 0;
    while (_pNode){
        result += (*_pfun)(&_pNode -> _val);
        _pNode = _pNode -> _next;
    }
    return result;
}
/// @brief traverse the elements of the list with a special function (from Tail to Head)
/// @param _list a pointer to the list
/// @param _pfun function pointer that do work on the elements inside list nodes
/// @returns accumulation of the traversal function return
ListSize traverse_tailward(List *_list, int _pfun(NodeType *_E)){
    Node *_pNode = _list -> _tail;
    ListSize result = 0;
    while (_pNode){
        result += (*_pfun)(&_pNode -> _val);
        _pNode = _pNode -> _prev;
    }
    return result;
}
/// @brief reverse the list in-place
/// @param _list 
void reverse(List *_list){
    Node *_F = _list -> _head, *_B = _list -> _tail;
    ListSize _i = 0, _limit = _list -> _size / 2;
    for (;_F && _B && _i < _limit; _i++){
        _swap(&_F -> _val, &_B -> _val);
        _F = _F -> _next;
        _B = _B -> _prev;
    }
}
/// @brief make all list elements equal to one element
/// @param _list a pointer to the list
/// @param val value to make all elements equal to
void fill(List *_list, NodeType val){
    _Val(&val);
    traverse_headward(_list, _makeEqualWithVal);
}
/// @brief copy all elements in source to destination, all elements in destination are erased
/// @param _list1 source
/// @param _list2 destination
// TODO refactor
void copy(List *_list1, List *_list2){
    clear(_list2);
    Node *_pSrcNode = _list1 -> _head;
    while(_pSrcNode){
        addTail(_list2, _pSrcNode -> _val);
        _pSrcNode = _pSrcNode -> _next;
    }
}
/// @brief print all elements int the list in order form Head to Tail
/// @param _list a pointer to the list
/// @param separator a separator of type string literal
void printAllElements(List *_list, char *separator){
    Node *_pNode = _list -> _head;
    while (_pNode){
        _printElement(&(_pNode -> _val));
        printf("%s", separator);
        _pNode = _pNode -> _next;
    }
}
/// @brief swaps two elements using their iterators
void swap(ListIterator _it1, ListIterator _it2){
    _swap(&_it1 -> _val, &_it2 -> _val);
}


//// !for test
int printe(NodeType *_){
    printf("%d ", *_);
}


int main(){
    List list1, list2;
    makeList(&list1);
    makeList(&list2);

    for (int i = 1; i<10; i++){
        addTail(&list1, i);
    }
    // printAllElements(&list1, "\n");
    insert(&list1, 999999, 3);
    addTail(&list1, 1222);
    addTail(&list1, 1212);

    printf("---------------------------- %lld\n", size(&list1));
    printAllElements(&list1, "\n");
    ListIterator h = head(&list1);
    

    
    // traverse_tailward(&list1, printe);

    return 0;
}