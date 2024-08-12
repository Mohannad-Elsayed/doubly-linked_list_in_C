#include <stdio.h>
#include <malloc.h>
typedef int NodeType;
typedef unsigned long long listSize;
typedef struct node {
    NodeType _val;
    struct node *_next, *_prev;
} Node;
typedef struct list {
    Node *_front;
    Node *_back;
    listSize _size;
} List;

/// @brief compares two elements of type `NodeType`
/// @return `1` if element 1 equals element 2, `0` otherwise
int equal(NodeType *_E1, NodeType *_E2){
    if (*_E1 == *_E2)
        return 1;
    else
        return 0;
}
/// @brief function to traverse list elements
/// @param _E 
void traverseFunction(NodeType *_E){
    printf("%d ", *_E);
}
/// @brief prints an element of type `NodeType`
/// @param _E pointer to the element
void printElement(NodeType *_E){
    printf("%d", *_E);
}
/// @brief holds the filling value in a static place in memory 
/// @param val a pointer to the value to be filled
/// @return a pointer to the place in memory in which the filling value is stored
NodeType* Val(NodeType *val){
    static NodeType *_val = NULL;
    if (_val) 
        return _val;
    _val = val;
    return _val;
}
/// @brief make a list element's value equal to a given value
/// @param _E the list element's value
void makeEqualWithVal(NodeType *_E){
    *_E = *Val((NodeType*)0);
}

/// @brief initializes the list pointers to NULL and the list size to 0
/// @param _list a pointer to the list
void initList(List *_list){
    _list -> _front = NULL;
    _list -> _back  = NULL;
    _list -> _size  = 0;
}
/// @brief appends an element to the start (front) of the list
/// @param _list a pointer to the list
/// @param val the value to be added (must be of type ```NodeType```)
/// @return `1` in success addition, `0` in failure
// TODO make NodeType reference type
int addFront(List *_list, NodeType val){
    Node *_pNode = (Node*)malloc(sizeof(Node));
    if (_pNode){
        Node *__pNode = _list -> _front;
        _list -> _front = _pNode;
        _pNode -> _prev = NULL;
        _pNode -> _next = __pNode;
        if (__pNode)
            __pNode -> _prev = _pNode;
        else
            _list -> _back = _pNode;
        _pNode -> _val = val;
        _list -> _size++;
        return 1;
    }
    return 0;
}
/// @brief appends an element to the end (back) of the list
/// @param _list a pointer to the list
/// @param val the value to be added (must be of type ```NodeType```)
/// @return `1` in success addition, `0` in failure
// TODO make NodeType reference type
int addBack(List *_list, NodeType val){
    Node *_pNode = (Node*)malloc(sizeof(Node));
    if (_pNode){
        Node *__pNode = _list -> _back;
        _list -> _back = _pNode;
        _pNode -> _prev = __pNode;
        _pNode -> _next = NULL;
        if (__pNode)
            __pNode -> _next = _pNode;
        else
            _list -> _front = _pNode;
        _pNode -> _val = val;
        _list -> _size++;
        return 1;
    }
    return 0;
}
/// @brief removes the front element in the list (the left most element)
/// @param _list a pointer the the list
/// @returns `1` in success removal, `0` in failure
int removeFront(List *_list){
    if (!_list -> _size){
        _list -> _front = _list -> _back = NULL;
        return 0;
    }
    Node *_pNode = _list -> _front;
    _list -> _front = _list -> _front -> _next;
    free(_pNode);
    _list -> _size--;
    if (!_list -> _size){
        _list -> _front = _list -> _back = NULL;
    }
    return 1;
}
/// @brief removes the back element in the list (the right most element)
/// @param _list a pointer the the list
/// @returns `1` in success removal, `0` in failure
int removeBack(List *_list){
    if (!_list -> _size){
        _list -> _front = _list -> _back = NULL;
        return 0;
    }
    Node *_pNode = _list -> _back;
    _list -> _back = _list -> _back -> _prev;
    free(_pNode);
    _list -> _size--;
    if (!_list -> _size){
        _list -> _front = _list -> _back = NULL;
    }
    return 1;
}
/// @brief traverse the elements of the list with a special function
/// @param _list a pointer to the list
/// @param _pfun function pointer that do work on the elements inside list nodes
void traverse(List *_list, void _pfun(NodeType *_E)){
    Node *_pNode = _list -> _front;
    while (_pNode){
        (*_pfun)(&_pNode -> _val);
        _pNode = _pNode -> _next;
    }
}
/// @brief removes an element in the list
/// @param _list pointer to the list
/// @param _node pointer to the element to be removed
/// @return a pointer the next element in the list to the left, if no such elements, returns `Null`
// TODO refactor
Node* removeElement(List *_list, Node *_node){
    Node *retNode = _node -> _next;
    if (_node -> _prev)
        _node -> _prev -> _next = _node -> _next;
    else
        _list -> _front = _node -> _next;
    if (_node -> _next)
        _node -> _next -> _prev = _node -> _prev;
    else
        _list -> _back = _node -> _prev;
    free(_node);
    return retNode;
}
/// @brief removes all occurrences of a particular value from te list
/// @param _list a pointer to the list
/// @param val the value to be removed (must be a pointer of type ```NodeType```)
/// @return `1` in success removal, `0` in failure
int removeVal(List *_list, NodeType *val){
    Node *_pNode = _list -> _front;
    int _flag = 0;
    while (_pNode){
        NodeType *_pNodeType = &(_pNode -> _val);
        if (equal(_pNodeType, val)){
            _pNode = removeElement(_list, _pNode);
            _flag = 1;
            _list -> _size--;
        }
        else
            _pNode = _pNode -> _next;
    }
    return _flag;
}
/// @brief print all elements int the list in order form front (left) to back (right)
/// @param _list a pointer to the list
/// @param separator a separator of type string literal
void printAllElements(List *_list, char *separator){
    Node *_pNode = _list -> _front;
    while (_pNode){
        printElement(&(_pNode -> _val));
        printf("%s", separator);
        _pNode = _pNode -> _next;
    }
}
/// @brief make all list elements equal to one element
/// @param _list a pointer to the list
/// @param val value to make all elements equal to
void fill(List *_list, NodeType val){
    Val(&val);
    traverse(_list, makeEqualWithVal);
}
/// @brief removes all elements in the list
/// @param _list a pointer to the list
void clear(List *_list){
    while(_list -> _size)
        removeFront(_list);
}
/// @return returns the number of elements in the list
listSize size(List *_list){
    return _list -> _size;
}
/// @brief copy all elements in source to destination, all elements in destination are removed
/// @param _list1 source
/// @param _list2 destination
void copy(List *_list1, List *_list2){
    clear(_list2);
    Node *_pSrcNode = _list1 -> _front;
    while(_pSrcNode){
        addBack(_list2, _pSrcNode -> _val);
        _pSrcNode = _pSrcNode -> _next;
    }
}
/// @brief append all elements in source to the end (back) of destination
/// @param _list1 source
/// @param _list2 destination
void append(List *_list1, List *_list2){
    Node *_pSrcNode = _list1 -> _front;
    while(_pSrcNode){
        addBack(_list2, _pSrcNode -> _val);
        _pSrcNode = _pSrcNode -> _next;
    }
}


int main(){
    List list1, list2;
    initList(&list1);
    initList(&list2);

    for (int i = 1; i<100; i++){
        if (i&1)
            addBack(&list1,i);
    }
    printAllElements(&list1, "   ");
    printf("\nsize: %llu\n", size(&list1));
    return 0;
}