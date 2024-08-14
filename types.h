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

int _comp(NodeType *_E1, NodeType *_E2);
void _traverseFunction(NodeType *_E);
void _printElement(NodeType *_E);
NodeType* _Val(NodeType *val);
int _makeEqualWithVal(NodeType *_E);
int _find(NodeType *_E);
int _count(NodeType *_E);
ListIterator _insert(Node *_pNode, NodeType *_E);
void _swap(NodeType *_E1, NodeType *_E2);
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
NodeType val(ListIterator _it);
ListSize size(List *_list);
int empty(List *_list);
ListIterator addHead(List *_list, NodeType val);
ListIterator addTail(List *_list, NodeType val);
ListIterator insert(List *_list, NodeType _element, ListSize _index);
void append(List *source, List *destination);
void prepend(List *source, List *destination);
ListIterator eraseHead(List *_list);
ListIterator eraseTail(List *_list);
ListIterator erase(List *_list, ListIterator _it);
ListIterator eraseAt(List *_list, signed _index);
ListSize eraseVal(List *_list, NodeType val);
ListSize find(List *_list, NodeType _element);
ListSize count(List *_list, NodeType _element);
ListSize traverse_headward(List *_list, int _pfun(NodeType *_E));
ListSize traverse_tailward(List *_list, int _pfun(NodeType *_E));
void reverse(List *_list);
void fill(List *_list, NodeType val);
void copy(List *_list1, List *_list2);
void printAllElements(List *_list, char *separator);
void swap(ListIterator _it1, ListIterator _it2);
