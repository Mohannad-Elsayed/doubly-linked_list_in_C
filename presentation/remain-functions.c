#ifndef DOUBLY_LINKED_LIST_IMPL
#define DOUBLY_LINKED_LIST_IMPL 1

#include "doubly_linked_list.h"

/// a helper variable to hold filling value 
ElementType __Val;
/// @brief a helper function to compare two values
/// @param _E1 a pointer to the first element
/// @param _E2 a pointer to the second element
/// @param equal_fun the equality function to compare against
/// @param greater_fun the greater than function to compare against
/// @return `0` if both equal, `> 0` if the first element greater than the second, `< 0` otherwise
static int _comp(ElementTypePtr _E1,
                 ElementTypePtr _E2,
                 int equal_fun(ElementTypePtr _E1, ElementTypePtr _E2),
                 int greater_fun(ElementTypePtr _E1, ElementTypePtr _E2)){
    if (equal_fun(_E1, _E2))
        return 0;
    else if (greater_fun(_E1, _E2))
        return 1;
    else 
        return -1;
}
/// @brief helper function to make a list element's value equal to a given value
/// @param _E the list element's value
static int _makeEqualWithVal(ElementTypePtr _E){
    *_E = __Val;
    return 0;
}
/// @brief erases all elements in the list
/// @param _list a pointer to the list
void clear(List *_list){
    while(_list -> _size)
        eraseHead(_list);
}
/// @brief skips elements in the list in the HEAD direction
/// @param _it an iterator to the current element
/// @param _step number of elements to be skipped
/// @return an iterator to the element if it's a valid element in the list, `NULL` otherwise
ListIterator jump_headward(ListIterator _it, unsigned _step){
    while(_it && _step--)
        _it = _it -> _prev;
    return _it;
}
/// @brief skips elements in the list in the TAIL direction
/// @param _it an iterator to the current element
/// @param _step number of elements to be skiped
/// @return an iterator to the element if it's a valid element in the list, `NULL` otherwise
ListIterator jump_tailward(ListIterator _it, unsigned _step){
    while(_it && _step--)
        _it = _it -> _next;
    return _it;
}
/// @brief advances the iterator to the tail by 1 step
/// @param _it an iterator to the current element
/// @return an iterator to the element if it's a valid element in the list, `NULL` otherwise
ListIterator next(ListIterator _it){
    return (_it ? _it -> _next : _it);
}
/// @brief advances the iterator to the head by 1 step
/// @param _it an iterator to the current element
/// @return an iterator to the element if it's a valid element in the list, `NULL` otherwise
ListIterator prev(ListIterator _it){
    return (_it ? _it -> _prev : _it);
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
/// @return pointer to the value pointed to by the iterator
/// @attention the function doesn't check the iterator's validity
ElementTypePtr val(ListIterator _it){
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
/// @brief traverse the elements of the list with a special function (from Tail to Head)
/// @param _list a pointer to the list
/// @param _pfun function pointer that do work on the elements inside list nodes
/// @returns accumulation of the traversal function return
ListSize traverse_headward(List *_list, int _pfun(ElementTypePtr _E)){
    Node *_pNode = _list -> _tail;
    ListSize result = 0;
    while (_pNode){
        result += (*_pfun)(_pNode -> _val);
        _pNode = _pNode -> _prev;
    }
    return result;
}
/// @brief make all list elements equal to a value
/// @param _list a pointer to the list
/// @param val value to make all elements equal to
void fill(List *_list, ElementType val){
    __Val = val;
    traverse_tailward(_list, _makeEqualWithVal);
}
/// @brief copy all elements in source to destination, all elements in destination are erased
/// @param _list1 source
/// @param _list2 destination
// TODO refactor
void copy(List *_list1, List *_list2){
    clear(_list2);
    Node *_pSrcNode = _list1 -> _head;
    while(_pSrcNode){
        addTail(_list2, *(_pSrcNode -> _val));
        _pSrcNode = _pSrcNode -> _next;
    }
}
/// @brief print all elements int the list in order form Head to Tail
/// @param _list a pointer to the list
/// @param separator a separator of type string literal
void printAllElements(List *_list, char *separator){
    Node *_pNode = _list -> _head;
    while (_pNode){
        _printElement(_pNode -> _val);
        if (_pNode->_next) 
            printf("%s", separator);
        _pNode = _pNode -> _next;
    }
}
/// @brief swaps two elements using their iterators
void swap(ListIterator _it1, ListIterator _it2){
    _swap(&_it1 -> _val, &_it2 -> _val);
}
/// @brief compares two lists regarding number of elements and elements
/// @param _list1 a pointer to the first list
/// @param _list2 a pointer to the second list
/// @param equal_fun the equality function to compare against
/// @return `1` if both are identical, `0` otherwise
int compare(List *_list1, 
            List *_list2, 
            int equal_fun(ElementTypePtr _E1, ElementTypePtr _E2)){
    if (_list1->_size != _list2->_size)
        return 0;
    Node *pl1 = _list1->_head, *pl2 = _list2->_head;
    while(pl1){
        if (!equal_fun(pl1->_val, pl2->_val))
            return 0;
        pl1 = pl1->_next,
        pl2 = pl2->_next;
    }
    return 1;
}
#endif /* DOUBLY_LINKED_LIST_IMPL */