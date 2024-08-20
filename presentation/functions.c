/// @brief initializes the list pointers to `NULL` and the list size to 0
/// @param _list a pointer to the list
void create(List *_list){
    _list -> _head = NULL;
    _list -> _tail  = NULL;
    _list -> _size  = 0;
}


/// @brief helper function to make a node and assign its value
/// @param _E data inside the node
/// @return a pointer to the node created in case of successful creation, `NULL` otherwise
static ListIterator _makeNode(const ElementTypePtr _E){
    Node *_pNode = (Node*)malloc(sizeof(Node));
    if (_pNode == NULL)
        return NULL;
    ElementTypePtr __val = (ElementTypePtr)malloc(sizeof(ElementType));
    if (__val == NULL){
        free(_pNode); 
        return NULL;
    }
    *__val = *_E;
    _pNode -> _val = __val;
    _pNode -> _next = _pNode -> _prev = NULL;
    return _pNode;
}


/// @brief appends an element to the start (Head side) of the list
/// @param _list a pointer to the list
/// @param val the value to be added
/// @return an iterator to the element in success addition, `NULL` in failure
// TODO make ElementType reference type
ListIterator addHead(List *_list, ElementType val){
    Node *_newHead = _makeNode(&val);
    if (_newHead){
        Node *_oldHead = _list -> _head;
        _list -> _head = _newHead;
        _newHead -> _prev = NULL;
        _newHead -> _next = _oldHead;
        if (_oldHead)
            _oldHead -> _prev = _newHead;
        else
            _list -> _tail = _newHead;
        _list -> _size++;
        return _newHead;
    }
    return NULL;
}


/// @brief get an iterator pointing at the element in the specified index, including negative indexing
/// @attention `0` is the first element at the head, `-1` is the last element at the tail, `-2` is second to last, ...
/// @param _list a pointer to the list 
/// @param _index index of the element `[-size, size-1]` inclusive
/// @return an iterator points at the element at the index, `NULL` if it's out-of-boundary
ListIterator at(List *_list, signed _index){
    if (_index < 0)
        _index += _list -> _size;
    return ((ListSize)_index >= _list -> _size || _index < 0) ? 
        NULL : 
        ((ListSize)_index < _list -> _size/2 ? 
            jump_tailward(_list -> _head, _index) : 
            jump_headward(_list -> _tail, _list -> _size - _index-1));
}


/// @brief helper function to allocate, insert a node after a specified node
/// @attention the function doesn't handle head and tail properly, use `addHead` and `addTail` for them
/// @attention the function doesn't increment the size of the list, consider manual increment
/// @param _fixedNode a pointer to the current node
/// @param _E the element to be inserted
/// @return an iterator to the inserted node in case of successful insertion, `NULL` otherwise
static ListIterator _insert(Node *_fixedNode, ElementTypePtr _E){
    if (!_fixedNode)
        return NULL;
    Node *_insertedNode = _makeNode(_E);
    if (_insertedNode){
        _insertedNode -> _prev = _fixedNode;
        _insertedNode -> _next = _fixedNode -> _next;
        _fixedNode -> _next -> _prev = _insertedNode;
        _fixedNode -> _next = _insertedNode;
        return _insertedNode;
    }
    return NULL;
}


/// @brief insert an element in the specified index (zero-based)
/// @param _list a pointer to the list
/// @param _element element to be inserted
/// @param _index the index, must be in the range [-size, size-1] inclusive
/// @return an iterator to the inserted node in case of successful insertion, `NULL` otherwise
ListIterator insertAt(List *_list, ElementType _element, signed _index){
    if (!_index || !(_index + _list -> _size))
        return addHead(_list, _element);
    if (!~_index)
        return addTail(_list, _element);
    Node *_pNode = at(_list, _index);
    if (_pNode){
        _pNode = _insert(_pNode -> _prev, &_element);
        if (_pNode)
            return _list -> _size++, _pNode;
        return NULL;
    }
    return NULL;
}


/// @brief a function to insert a node after a specified node in a list
/// @param _list a pointer to the list
/// @param _element the element to be inserted
/// @param _it an iterator points to the current node
/// @return an iterator to the inserted element in case of successful insertion, `NULL` otherwise
ListIterator insertAfter(List *_list, ElementType _element, ListIterator _it){
    if (_it == _list -> _tail){
        return addTail(_list, _element);
    }
    return _list -> _size++, _insert(_it, &_element);
}


/// @brief append all elements in `source` to the Tail of `destination`
/// @param source
/// @param destination
void append(List *source, List *destination){
    Node *_pSrcNode = source -> _head;
    while(_pSrcNode){
        addTail(destination, *(_pSrcNode -> _val));
        _pSrcNode = _pSrcNode -> _next;
    }
}



/// @brief prepend all elements in `source` to the Head of `destination`
/// @param source
/// @param destination
void prepend(List *source, List *destination){
    Node *_pSrcNode = source -> _tail;
    while(_pSrcNode){
        addHead(destination, *(_pSrcNode -> _val));
        _pSrcNode = _pSrcNode -> _prev;
    }
}


/// @brief a helper function to free a node completely
/// @param _pNode a pointer to the node
static void _freeNode(ListIterator _pNode){
    if (_pNode){
        if (_pNode->_val)
            free(_pNode->_val);
        free(_pNode);
    }
}


/// @brief erases the Head element in the list (the left most element)
/// @param _list a pointer the the list
/// @returns an iterator to the new HEAD in success removal, `NULL` if the list is empty before or after the removal
ListIterator eraseHead(List *_list){
    if (!_list -> _size){
        return _list -> _head = _list -> _tail = NULL;
    }
    Node *_oldHead = _list -> _head;
    _list -> _head = _list -> _head -> _next;
    _freeNode(_oldHead);
    _list -> _size--;
    if (!_list -> _size)
        return _list -> _head = _list -> _tail = NULL;
    _list -> _head -> _prev = NULL;
    return _list -> _head;
}


/// @brief helper function to erase an element in the list, decrement the size
/// @param _list pointer to the list
/// @param _node pointer to the element to be erased
/// @return a pointer the next element in the list to the left, if no such elements, returns `Null`
// TODO refactor
static ListIterator _eraseNode(List *_list, Node *_node){
    if (_node){
        Node *retNode = _node -> _next;
        if (_node -> _prev)
            _node -> _prev -> _next = _node -> _next;
        else
            _list -> _head = _node -> _next;
        if (_node -> _next)
            _node -> _next -> _prev = _node -> _prev;
        else
            _list -> _tail = _node -> _prev;
        _freeNode(_node);
        _node = NULL;
        _list -> _size--;
        return retNode;
    }
    return NULL;
}


/// @brief erases all occurrences of a particular value from te list
/// @param _list a pointer to the list
/// @param val the value to be erased 
/// @param equal_fun the equality function to compare against
/// @return number of elements erased
ListSize eraseVal(List *_list, 
                  ElementType val, 
                  int equal_fun(ElementTypePtr _E1, ElementTypePtr _E2)){
    Node *_pNode = _list -> _head;
    int _flag = 0;
    while (_pNode){
        if (equal_fun(_pNode->_val, &val)){
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
/// @param equal_fun the equality function to compare against
/// @return iterator pointing at the first occurrence of the element in the list if it's present, `NULL` otherwise
ListIterator find(List *_list, 
                  ElementType _element, 
                  int equal_fun(ElementTypePtr _E1, ElementTypePtr _E2)){
    Node *_H = _list -> _head, *_T = _list -> _tail;
    ListSize _i = 0, _limit = _list -> _size / 2;
    for (;_H && _T && _i <= _limit; _i++){
        if (equal_fun(_H->_val, &_element))
            return _H;
        if (equal_fun(_T->_val, &_element))
            return _T;
        _H = _H -> _next;
        _T = _T -> _prev;
    }
    return NULL;
}



/// @brief count the number of element occurrences in the list
/// @param _list a pointer to the list
/// @param _element element to be counted
/// @param equal_fun the equality function to compare against
/// @return number of elements matched 
ListSize count(List *_list, 
               ElementType _element, 
               int equal_fun(ElementTypePtr _E1, ElementTypePtr _E2)){
    ListSize _counter = 0;
    Node *_H = _list -> _head, *_T = _list -> _tail;
    ListSize _i = 0, _limit = _list -> _size / 2;
    for (;_H && _T && _i < _limit; _i++){
        if (equal_fun(_H->_val, &_element))
            _counter++;
        if (equal_fun(_T->_val, &_element))
            _counter++;
        _H = _H -> _next;
        _T = _T -> _prev;
    }
    if (_i&1)
        _counter += equal_fun(_T->_prev->_val, &_element);
    return _counter;
}


/// @brief traverse the elements of the list with a special function (from Head to Tail)
/// @param _list a pointer to the list
/// @param _pfun function pointer that do work on the elements inside list nodes
/// @returns accumulation of the traversal function return
ListSize traverse_tailward(List *_list, int _pfun(ElementTypePtr _E)){
    Node *_pNode = _list -> _head;
    ListSize result = 0;
    while (_pNode){
        result += (*_pfun)(_pNode -> _val);
        _pNode = _pNode -> _next;
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


