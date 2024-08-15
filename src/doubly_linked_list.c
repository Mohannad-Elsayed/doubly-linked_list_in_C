#ifndef DOUBLY_LINKED_LIST_c
#define DOUBLY_LINKED_LIST_c 1

#include "doubly_linked_list.h"

/// a helper variable to hold filling value 
ElementType __Val;
/// @brief helper function compares two elements of type `ElementType`
/// @return `1` if element 1 greater than element 2, `0` if both are equal, `-1` if element 1 is smaller than element 2
int _comp(ElementType *_E1, ElementType *_E2){
    if (equal(_E1, _E2))
        return 0;
    else if (greater(_E1, _E2))
        return 1;
    else 
        return -1;
}
/// @brief helper function to make a list element's value equal to a given value
/// @param _E the list element's value
int _makeEqualWithVal(ElementType *_E){
    *_E = __Val;
    return 0;
}
/// @brief helper function for function `find()` to compare two elements
/// @return `1` if two elements are equal, `0` otherwise
int _find(ElementType *_E){
    return !_comp(&__Val, _E);
}
/// @brief helper function for function `find()` to compare two elements
/// @return `1` if two elements are equal, `0` otherwise
int _count(ElementType *_E){
    return !_comp(&__Val, _E);
}
/// @brief helper function to allocate, insert a node after a specified node
/// @param _pNode a pointer to the current node
/// @param _E the element to be inserted
/// @return an iterator to the inserted node in case of successful insertion, `NULL` otherwise
ListIterator _insert(Node *_pNode, ElementType *_E){
    Node *__pNode = (Node *)malloc(sizeof(Node));
    if (__pNode){
        __pNode -> _val = *_E;
        __pNode -> _prev = _pNode;
        __pNode -> _next = _pNode -> _next;
        _pNode -> _next -> _prev = __pNode;
        _pNode -> _next = __pNode;
        return __pNode;
    }
    return NULL;
}
/// @brief a helper function swaps two elements
/// @param _E1 pointer to the first element
/// @param _E2 pointer to the second element
void _swap(ElementType *_E1, ElementType *_E2){
    ElementType _T = *_E1;
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
/// @return an iterator to the element if it's a valid element in the list, `NULL` otherwise
ListIterator jump_tailward(ListIterator _it, unsigned _step){
    while(_it && _step--)
        _it = _it -> _prev;
    return _it;
}
/// @brief advances the iterator to the tail by 1 step
/// @param _it an iterator to the current element
/// @return an iterator to the element if it's a valid element in the list, `NULL` otherwise
ListIterator next(ListIterator _it){
    if (_it)
        return _it -> _next;
    return _it;
}
/// @brief advances the iterator to the head by 1 step
/// @param _it an iterator to the current element
/// @return an iterator to the element if it's a valid element in the list, `NULL` otherwise
ListIterator prev(ListIterator _it){
    if (_it)
        return _it -> _prev;
    return _it;
}
/// @brief get an iterator pointing at the element in the specified index, including negative indexing
/// @attention `0` is the first element at the head, `-1` is the last element at the tail, `-2` is second to last, ...
/// @param _list a pointer to the list 
/// @param _index index of the element `[-size, size-1]` inclusive
/// @return an iterator points at the element at the index, `NULL` if it's out-of-boundary
ListIterator at(List *_list, signed _index){
    if (_index < 0)
        _index += _list -> _size;
    if ((ListSize)_index >= _list -> _size || _index < 0)
        return NULL;
    return jump_headward(head(_list), _index);
}
/// @param _list a pointer to the list
/// @return an iterator to the Head element in the list
ListIterator head(List *_list){
    return _list -> _head;
}
/// @param _list a pointer to the list
/// @return an iterator to the Tail element in the list
ListIterator tail(List *_list){
    return _list -> _tail;
}
/// @param _it an iterator to the current element
/// @return the value pointed to by the iterator
/// @attention the function doesn't check the iterator's validity
ElementType val(ListIterator _it){
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
/// @return an iterator to the element in success addition, `NULL` in failure
// TODO make ElementType reference type
ListIterator addHead(List *_list, ElementType val){
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
/// @return an iterator to the element in success addition, `NULL` in failure
// TODO make ElementType reference type
ListIterator addTail(List *_list, ElementType val){
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
/// @return an iterator to the inserted node in case of successful insertion, `NULL` otherwise
ListIterator insert(List *_list, ElementType _element, ListSize _index){
    if (_index >= _list -> _size)
        return 0;
    if (_index == 0)
        return addHead(_list, _element);
    Node *_pNode = _list -> _head;
    while(--_index)
        _pNode = _pNode -> _next;
    _pNode = _insert(_pNode, &_element);
    if (_pNode){
        _list -> _size++;
        return _pNode;
    }
    return NULL;
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
/// @returns an iterator to the new HEAD in success removal, `NULL` if the list is empty before or after the removal
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
/// @returns an iterator to the new TAIL in success removal, `NULL` if the list is empty before or after the removal
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
ListSize eraseVal(List *_list, ElementType val){
    Node *_pNode = _list -> _head;
    int _flag = 0;
    while (_pNode){
        ElementType *_pNodeType = &(_pNode -> _val);
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
ListSize find(List *_list, ElementType _element){
    __Val = _element;
    return !(!traverse_headward(_list, _find));
}
/// @brief count the number of element occurrences in the list
/// @param _list a pointer to the list
/// @param _element element to be counted
/// @return number of elements matched 
ListSize count(List *_list, ElementType _element){
    __Val = _element;
    return traverse_headward(_list, _count);
}
/// @brief traverse the elements of the list with a special function (from Head to Tail)
/// @param _list a pointer to the list
/// @param _pfun function pointer that do work on the elements inside list nodes
/// @returns accumulation of the traversal function return
ListSize traverse_headward(List *_list, int _pfun(ElementType *_E)){
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
ListSize traverse_tailward(List *_list, int _pfun(ElementType *_E)){
    Node *_pNode = _list -> _tail;
    ListSize result = 0;
    while (_pNode){
        result += (*_pfun)(&_pNode -> _val);
        _pNode = _pNode -> _prev;
    }
    return result;
}
/// @brief reverse the list in-place
/// @param _list a pointer to the list
void reverse(List *_list){
    Node *_H = _list -> _head, *_T = _list -> _tail;
    ListSize _i = 0, _limit = _list -> _size / 2;
    for (;_H && _T && _i < _limit; _i++){
        _swap(&_H -> _val, &_T -> _val);
        _H = _H -> _next;
        _T = _T -> _prev;
    }
}
/// @brief make all list elements equal to a value
/// @param _list a pointer to the list
/// @param val value to make all elements equal to
void fill(List *_list, ElementType val){
    __Val = val;
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
#endif /* DOUBLY_LINKED_LIST_c */