/*
TODO

    swap
    reverse list
    find
    count
    insert
    traverse-forward, backward
    iterators, front, back, next, prev, jump
    indexing, negative indexing
    //inbetween pointer to speed up insertion
    head, tail naming
    circular
    prototypes in a .h file
    generic using void pointers
    a proper API
    licence

*/

#include <stdio.h>
#include <malloc.h>
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
/// @brief function to traverse list elements
/// @param _E 
void _traverseFunction(NodeType *_E){
    printf("%d ", *_E);
}
/// @brief prints an element of type `NodeType`
/// @param _E pointer to the element
void _printElement(NodeType *_E){
    printf("%d", *_E);
}
/// @brief holds the filling value in a static place in memory 
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
/// @brief make a list element's value equal to a given value
/// @param _E the list element's value
int makeEqualWithVal(NodeType *_E){
    *_E = *_Val((NodeType*)0);
    return 0;
}
int _find(NodeType *_E){
    return !_comp(_Val((NodeType*)0), _E);
}
int _count(NodeType *_E){
    return !_comp(_Val((NodeType*)0), _E);
}

/// @brief initializes the list pointers to NULL and the list size to 0
/// @param _list a pointer to the list
void initList(List *_list){
    _list -> _head = NULL;
    _list -> _tail  = NULL;
    _list -> _size  = 0;
}
/// @brief appends an element to the start (Head side) of the list
/// @param _list a pointer to the list
/// @param val the value to be added
/// @return `1` in success addition, `0` in failure
// TODO make NodeType reference type
int addHead(List *_list, NodeType val){
    Node *_pNode = (Node*)malloc(sizeof(Node));
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
        return 1;
    }
    return 0;
}
/// @brief appends an element to the end (Tail side) of the list
/// @param _list a pointer to the list
/// @param val the value to be added
/// @return `1` in success addition, `0` in failure
// TODO make NodeType reference type
int addTail(List *_list, NodeType val){
    Node *_pNode = (Node*)malloc(sizeof(Node));
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
        return 1;
    }
    return 0;
}
/// @brief removes the Head element in the list (the left most element)
/// @param _list a pointer the the list
/// @returns `1` in success removal, `0` in failure
int removeHead(List *_list){
    if (!_list -> _size){
        _list -> _head = _list -> _tail = NULL;
        return 0;
    }
    Node *_pNode = _list -> _head;
    _list -> _head = _list -> _head -> _next;
    free(_pNode);
    _list -> _size--;
    if (!_list -> _size){
        _list -> _head = _list -> _tail = NULL;
    }
    return 1;
}
/// @brief removes the Tail element in the list (the right most element)
/// @param _list a pointer the the list
/// @returns `1` in success removal, `0` in failure
int removeTail(List *_list){
    if (!_list -> _size){
        _list -> _head = _list -> _tail = NULL;
        return 0;
    }
    Node *_pNode = _list -> _tail;
    _list -> _tail = _list -> _tail -> _prev;
    free(_pNode);
    _list -> _size--;
    if (!_list -> _size){
        _list -> _head = _list -> _tail = NULL;
    }
    return 1;
}
/// @brief traverse the elements of the list with a special function (from Head to Tail)
/// @param _list a pointer to the list
/// @param _pfun function pointer that do work on the elements inside list nodes
/// @returns the result of the function
ListSize traverse_forward(List *_list, int _pfun(NodeType *_E)){
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
/// @returns the result of the function
ListSize traverse_backward(List *_list, int _pfun(NodeType *_E)){
    Node *_pNode = _list -> _tail;
    ListSize result = 0;
    while (_pNode){
        result += (*_pfun)(&_pNode -> _val);
        _pNode = _pNode -> _prev;
    }
    return result;
}
/// @brief removes an element in the list
/// @param _list pointer to the list
/// @param _node pointer to the element to be removed
/// @return a pointer the next element in the list to the left, if no such elements, returns `Null`
// TODO refactor
Node* _removeNode(List *_list, Node *_node){
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
    return retNode;
}
/// @brief removes all occurrences of a particular value from te list
/// @param _list a pointer to the list
/// @param val the value to be removed 
/// @return `1` in success removal, `0` in failure
int removeVal(List *_list, NodeType val){
    Node *_pNode = _list -> _head;
    int _flag = 0;
    while (_pNode){
        NodeType *_pNodeType = &(_pNode -> _val);
        if (!_comp(_pNodeType, &val)){
            _pNode = _removeNode(_list, _pNode);
            _flag = 1;
            _list -> _size--;
        }
        else
            _pNode = _pNode -> _next;
    }
    return _flag;
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
/// @brief make all list elements equal to one element
/// @param _list a pointer to the list
/// @param val value to make all elements equal to
void fill(List *_list, NodeType val){
    _Val(&val);
    traverse_forward(_list, makeEqualWithVal);
}
/// @brief removes all elements in the list
/// @param _list a pointer to the list
void clear(List *_list){
    while(_list -> _size)
        removeHead(_list);
}
/// @return returns the number of elements in the list
ListSize size(List *_list){
    return _list -> _size;
}
/// @return `1` if the list has no elements, `0` otherwise
int empty(List *_list){
    return !(_list -> _size);
}
/// @brief copy all elements in source to destination, all elements in destination are removed
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
/// @brief append all elements in source to the Tail of destination
/// @param _list1 source
/// @param _list2 destination
void append(List *_list1, List *_list2){
    Node *_pSrcNode = _list1 -> _head;
    while(_pSrcNode){
        addTail(_list2, _pSrcNode -> _val);
        _pSrcNode = _pSrcNode -> _next;
    }
}
/// @brief prepend all elements in source to the Head of destination
/// @param _list1 source
/// @param _list2 destination
void prepend(List *_list1, List *_list2){
    Node *_pSrcNode = _list1 -> _head;
    while(_pSrcNode){
        addTail(_list2, _pSrcNode -> _val);
        _pSrcNode = _pSrcNode -> _next;
    }
}
/// @brief swaps two elements in the list
/// @param _E1 pointer to the first element
/// @param _E2 pointer to the second element
void swap(NodeType *_E1, NodeType *_E2){
    NodeType _T = *_E1;
    *_E1 = *_E2;
    *_E2 = _T;
}
/// @brief reverse the list in-place
/// @param _list 
void reverse(List *_list){
    Node *_F = _list -> _head, *_B = _list -> _tail;
    ListSize _i = 0, _limit = _list -> _size / 2;
    for (;_F && _B && _i < _limit; _i++){
        swap(&_F -> _val, &_B -> _val);
        _F = _F -> _next;
        _B = _B -> _prev;
    }
}
/// @brief finds an element inside a list 
/// @param _list a pointer to the list
/// @param _element element to be found
/// @return `1` if the element is present in the list, `0` otherwise
ListSize find(List *_list, NodeType _element){
    _Val(&_element);
    return !(!traverse_forward(_list, _find));
}
/// @brief count the number of element occurrences in the list
/// @param _list a pointer to the list
/// @param _element element to be counted
/// @return number of elements matched 
ListSize count(List *_list, NodeType _element){
    _Val(&_element);
    return traverse_forward(_list, _count);
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
/// @brief skips elements in the list to the tail
/// @param _it an iterator to the current element
/// @param _step number of elements to be skipeed
/// @return `1` if the final element is a valid element in the list, `0` otherwise
int jump_forward(ListIterator *_it, unsigned _step){
    while((*_it) && _step--)
        (*_it) = (*_it) -> _next;
    return *_it != NULL;
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
/// @param _it an iterator to the current element
/// @return the value pointed to by the iterator
/// @attention the function doesn't check the iterator's validity
NodeType val(ListIterator _it){
    return _it -> _val;
}
/// @brief get an iterator pointing at the element in the specified index, including negative indexing
/// @attention `0` is the first element at the head, `-1` is the last element at the tail, `-2` is second to last, ...
/// @param _list a pointer to the list 
/// @param _index index of the element `[-size, size-1]` inclusive
/// @return 
ListIterator at(List *_list, signed _index){
    if (_index < 0)
        _index += _list -> _size;
    if (_index >= _list -> _size || _index < 0)
        return NULL;
    ListIterator _it = _list -> _head;
    jump_forward(&_it, _index);
    return _it;
}

//// !for test
int printe(NodeType *_){
    printf("%d ", *_);
}


int main(){
    List list1, list2;
    initList(&list1);
    initList(&list2);

    for (int i = 1; i<0; i++){
        addTail(&list1, i);
    }
    printAllElements(&list1, "\n");
    insert(&list1, 999999, 3);
    addTail(&list1, 1222);
    addTail(&list1, 1212);
    printf("---------------------------- %lld\n", size(&list1));
    printAllElements(&list1, "\n");

    // traverse_tailward(&list1, printe);
    printf("%d", val(at(&list1, -3)));
    return 0;
}