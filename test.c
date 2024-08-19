#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <float.h>
#include <math.h>

#define test(fn) \
    printf("Testing: \x1b[33m" # fn "()\x1b[0m\n"); \
    test_##fn(); // call the test function

#define ElementType long long
typedef ElementType* ElementTypePtr;

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

#define __printElement
void _printElement(ElementType *_E){
    printf("%lld", *_E);
}

#define __traverseFunction
int _traverseFunction(ElementType *_E){
    _printElement(_E);
    return 0;
}

#include "src/doubly_linked_list.c"

// test functions
static void test__comp(void){
    ElementType eq1, eq2, big, small;
    eq1 = eq2 = 10000;
    big = 10000;
    small = -10000;

    assert(!_comp(&eq1, &eq2, equal, greater));
    assert(_comp(&big, &small, equal, greater) > 0);
    assert(_comp(&small, &big, equal, greater) < 0);

}
static void test__makeEqualWithVal(void){
    __Val = 1;
    ElementType z;
    _makeEqualWithVal(&z);
    
    assert(z == __Val);
}
static void test__makeNode(void){
    ElementType x = 1;
    Node *p = _makeNode(&x);
    assert(p);

    assert(*p -> _val == x);
    assert(p -> _next == NULL);
    assert(p -> _prev == NULL);

    _freeNode(p);
}
static void test__insert(void){
    ElementType x = 1;
    Node *p = _makeNode(&x), *q = _makeNode(&x);
    assert(p && q);
    p -> _next = q;
    q -> _prev = p;
    // p <-> q
    Node *r = _insert(p, &x);
    assert(r);

    // p <-> r <-> q
    assert(p -> _next == r);
    assert(r -> _prev == p);
    assert(r -> _next == q);
    assert(q -> _prev == r);

    _freeNode(p); _freeNode(q); _freeNode(r);
}
static void test__swap(void){
    ElementType x = 0, y = 1;
    ElementType *px = &x, *py = &y;
    _swap(&px, &py);

    assert(*px == 1);
    assert(*py == 0);
}

static void test_create(void){
    List lst;
    create(&lst);

    assert(lst._head == NULL);
    assert(lst._tail == NULL);
    assert(!lst._size);
}
static void test_addHead(void){
    List lst;
    create(&lst);
    Node* p = addHead(&lst, 1);
    assert(p);
    assert(lst._head == p);
    assert(lst._size == 1);

    Node* q = addHead(&lst, 2);
    assert(q);
    assert(lst._head == q);
    assert(lst._size == 2);

    Node* r = addHead(&lst, 3);
    assert(r);

    assert(lst._head == r);
    assert(lst._size == 3);

    assert(p -> _next == NULL);
    assert(q -> _next == p);
    assert(r -> _next == q);
    assert(r -> _prev == NULL);
    assert(q -> _prev == r);
    assert(p -> _prev == q);
    assert(lst._head == r);
    assert(lst._tail == p);
    assert(lst._head -> _next == q);
    assert(lst._tail -> _prev == q);

    clear(&lst);
}
static void test_eraseHead(void){
    List lst;
    create(&lst);
    Node* p = addHead(&lst, 1);
    Node* q = addHead(&lst, 2);
    Node* r = addHead(&lst, 3);
    assert(p&&q&&r);

    eraseHead(&lst);
    assert(lst._size == 2);
    assert(lst._head == q);
    assert(lst._head -> _prev == NULL);

    eraseHead(&lst);
    assert(lst._size == 1);
    assert(lst._head == p);
    assert(lst._head -> _prev == NULL);

    eraseHead(&lst);
    assert(lst._size == 0);
    assert(lst._head == NULL);
    assert(lst._tail == NULL);

    clear(&lst);
}
static void test_clear(void){
    List lst;
    create(&lst);
    Node* p = addHead(&lst, 1);
    Node* q = addHead(&lst, 2);
    Node* r = addHead(&lst, 3); 
    assert(p&&q&&r);

    clear(&lst);
    
    assert(lst._size == 0);
    assert(lst._head == NULL);
    assert(lst._tail == NULL);
    
}

static void test_addTail(void){
    List lst;
    create(&lst);
    Node* p = addTail(&lst, 1);
    assert(p);

    assert(lst._tail == p);
    assert(lst._size == 1);

    Node* q = addTail(&lst, 2);
    assert(q);

    assert(lst._tail == q);
    assert(lst._size == 2);

    Node* r = addTail(&lst, 3);
    assert(r);

    assert(lst._tail == r);
    assert(lst._size == 3);

    assert(r -> _next == NULL);
    assert(q -> _next == r);
    assert(p -> _next == q);
    assert(r -> _prev == q);
    assert(q -> _prev == p);
    assert(p -> _prev == NULL);
    assert(lst._head == p);
    assert(lst._tail == r);
    assert(lst._head -> _next == q);
    assert(lst._tail -> _prev == q);

    clear(&lst);

}
static void test_eraseTail(void){
    List lst;
    create(&lst);
    Node* p = addTail(&lst, 1);
    Node* q = addTail(&lst, 2);
    Node* r = addTail(&lst, 3);
    assert(p&&q&&r);

    eraseTail(&lst);
    assert(lst._size == 2);
    assert(lst._tail == q);
    assert(lst._tail->_next == NULL);

    eraseTail(&lst);
    assert(lst._size == 1);
    assert(lst._tail == p);
    assert(lst._tail->_next == NULL);

    eraseTail(&lst);
    assert(lst._size == 0);
    assert(lst._tail == NULL);
    assert(lst._tail == NULL);

    clear(&lst);
}

static void test_insertAt(void){
    List lst;
    create(&lst);
    Node *p = insertAt(&lst, 1, 0);

    assert(p);
    assert(lst._size == 1);
    assert(lst._head == lst._tail && lst._head == p);
    assert(*lst._head -> _val == 1);

    clear(&lst);

    p = insertAt(&lst, 1, -1);
    assert(p);
    assert(lst._size == 1);
    assert(lst._head == lst._tail && lst._head == p);
    assert(*lst._head -> _val == 1);

    assert(addHead(&lst, 2) && addHead(&lst, 3) && addHead(&lst, 4));

    p = insertAt(&lst, 9, 1);
    assert(p);
    assert(lst._size == 5);
    assert(lst._head -> _next == p);
    assert(lst._head -> _next -> _next ->_prev == p);

    p = insertAt(&lst, 9, -1);
    assert(p);
    assert(lst._tail == p);
    assert(lst._tail -> _prev -> _next == p);

    p = insertAt(&lst, 9, 0);
    assert(p);
    assert(lst._head == p);
    assert(lst._head -> _next -> _prev == p);

    p = insertAt(&lst, 9, -(signed)lst._size);
    assert(p);
    assert(lst._head == p);
    assert(lst._head -> _next -> _prev == p);

    clear(&lst);
}
static void test_insertAfter(void){
    List lst;
    create(&lst);

    assert(addTail(&lst, 1) && addTail(&lst, 3) && addTail(&lst, 4));
    Node *q = insertAfter(&lst, 2, lst._head);
    assert(q);
    assert(*q->_val == 2);
    assert(q->_prev->_next == q);
    assert(q->_next->_prev == q);
    
    q = insertAfter(&lst, 5, lst._tail);
    assert(q);
    assert(lst._tail == q);
    assert(q->_next == NULL);
    assert(q->_prev->_next == q);

    clear(&lst);
}

static void test_append(void){
    List lst1, lst2;
    create(&lst1);
    create(&lst2);
    assert(addTail(&lst1, 1) && addTail(&lst1, 2) && addTail(&lst1, 3));
    assert(addTail(&lst2, 4) && addTail(&lst2, 5) && addTail(&lst2, 6));

    append(&lst2, &lst1);
    Node *p = lst1._head;
    assert(p);
    for (int i = 1; p && i<6; i++){
        assert(*p->_val == i);
        p = p->_next;
    }
    assert(p == lst1._tail);
    assert(*p->_val == 6);

    clear(&lst1);
    clear(&lst2);
}
static void test_prepend(void){
    List lst1, lst2;
    create(&lst1);
    create(&lst2);
    assert(addTail(&lst1, 4) && addTail(&lst1, 5) && addTail(&lst1, 6));
    assert(addTail(&lst2, 1) && addTail(&lst2, 2) && addTail(&lst2, 3));

    prepend(&lst2, &lst1);
    Node *p = lst1._head;
    assert(p);
    for (int i = 1; p && i<6; i++){
        assert(*p->_val == i);
        p = p->_next;
    }
    assert(p == lst1._tail);
    assert(*p->_val == 6);

    clear(&lst1);
    clear(&lst2);
}

static void test_val(void){
    ElementType x = 1;
    Node *p = _makeNode(&x);
    assert(p);
    assert(val(p) == p->_val);

    _freeNode(p);
}
static void test_size(void){
    List lst;
    create(&lst);

    assert(addTail(&lst, 1) && addTail(&lst, 2) && addTail(&lst, 3));
    assert(size(&lst) == lst._size);

    clear(&lst);
}
static void test_empty(void){
    List lst;
    create(&lst);

    assert(empty(&lst));
    assert(addTail(&lst, 1) && addTail(&lst, 2) && addTail(&lst, 3));
    assert(!empty(&lst));

    clear(&lst);
}

static void test__eraseNode(void){
    List lst;
    create(&lst);
    assert(addTail(&lst, 1));
    Node *p = _eraseNode(&lst, lst._head);

    assert(p == NULL);
    assert(lst._head == NULL);
    assert(lst._tail == NULL);
    assert(lst._size == 0);

    assert(addTail(&lst, 1) && addTail(&lst, 2) && addTail(&lst, 3));
    p = _eraseNode(&lst, lst._head->_next);

    assert(p == lst._tail);
    assert(lst._head->_next == p);

    clear(&lst);
}
static void test_erase(void){
    List lst;
    create(&lst);
    assert(addTail(&lst, 1));
    erase(&lst, lst._head);

    assert(lst._head == NULL);
    assert(lst._tail == NULL);
    assert(lst._size == 0);

    assert(addTail(&lst, 1) && addTail(&lst, 2) && addTail(&lst, 3));
    Node *p = erase(&lst, lst._head);

    assert(lst._head == p);
    assert(*p->_val == 2);

    p = erase(&lst, lst._tail);

    assert(lst._head == lst._tail);
    assert(*lst._tail->_val == 2);
    assert(p == NULL);

    clear(&lst);
}

static void test_jump_headward(void){
    List lst;
    create(&lst);
    assert(addTail(&lst, 1) && addTail(&lst, 2) && addTail(&lst, 3));
    Node *t = lst._tail;
    Node *q = jump_headward(t, 0), *r = jump_headward(t, 1), *s = jump_headward(t, 2);

    assert(q == t);
    assert(r == lst._head->_next);
    assert(s == lst._head);

    clear(&lst);
}
static void test_jump_tailward(void){
    List lst;
    create(&lst);
    assert(addTail(&lst, 1) && addTail(&lst, 2) && addTail(&lst, 3));
    Node *t = lst._head;
    Node *q = jump_tailward(t, 0), *r = jump_tailward(t, 1), *s = jump_tailward(t, 2);

    assert(q == t);
    assert(r == lst._head->_next);
    assert(s == lst._tail);

    t = jump_tailward(t, 4);

    assert(t == NULL);

    clear(&lst);
}
static void test_at(void){
    List lst;
    create(&lst);
    assert(addTail(&lst, 1));

    assert(at(&lst, 0) == lst._head);
    assert(at(&lst, -(int)lst._size) == lst._head);
    assert(at(&lst, -1) == lst._head);

    assert(addTail(&lst, 2) && addTail(&lst, 3));

    assert(*at(&lst, -3)->_val == 1);
    assert(*at(&lst, -2)->_val == 2);
    assert(*at(&lst, -1)->_val == 3);
    assert(*at(&lst, 0)->_val ==  1);
    assert(*at(&lst, 1)->_val ==  2);
    assert(*at(&lst, 2)->_val ==  3);

    clear(&lst);
}
static void test_eraseAt(void){
    List lst;
    create(&lst);
    assert(addTail(&lst, 1));
    Node *p = eraseAt(&lst, 0);

    assert(lst._head == lst._tail && lst._head == NULL);
    assert(!lst._size);
    assert(p == NULL);

    assert(addTail(&lst, 1));
    assert(addTail(&lst, 2));
    assert(addTail(&lst, 3));
    p = eraseAt(&lst, 1);

    assert(p == lst._tail);
    assert(p == lst._head->_next);

    p = eraseAt(&lst, -2);

    assert(lst._head == lst._tail);
    assert(lst._head == p);

    p = eraseAt(&lst, 3);

    assert(p == NULL);

    clear(&lst);
}
static void test_eraseVal(void){
    List lst;
    create(&lst);
    assert(addTail(&lst, 1) && addTail(&lst, 2) && addTail(&lst, 3));
    ListSize x = eraseVal(&lst, 1, equal);

    assert(*lst._head->_val == 2);
    assert(lst._size == 2);
    assert(x == 1);

    x = eraseVal(&lst, 10, equal);

    assert(x == 0);
    assert(lst._size == 2);

    clear(&lst);
}
static void test_next(void){
    List lst;
    create(&lst);
    assert(addTail(&lst, 1) && addTail(&lst, 2) && addTail(&lst, 3));
    
    assert(next(lst._head) == lst._head->_next);

    clear(&lst);
}
static void test_prev(void){
    List lst;
    create(&lst);
    assert(addTail(&lst, 1) && addTail(&lst, 2) && addTail(&lst, 3));

    assert(prev(lst._head) == lst._head->_prev);

    clear(&lst);
}
static void test_head(void){
    List lst;
    create(&lst);
    assert(addTail(&lst, 1));

    assert(head(&lst) == lst._head);

    clear(&lst);
}
static void test_tail(void){
    List lst;
    create(&lst);
    assert(addTail(&lst, 1));

    assert(tail(&lst) == lst._tail);

    clear(&lst);
}

static void test_count(void){
    List lst;
    create(&lst);
    assert(addTail(&lst, 1) && addTail(&lst, 1) && addTail(&lst, 2));

    assert(count(&lst, 1, equal) == 2);
    assert(count(&lst, 2, equal) == 1);
    assert(count(&lst, 3, equal) == 0);

    clear(&lst);
}
static void test_find(void){
    List lst;
    create(&lst);
    assert(addTail(&lst, 1) && addTail(&lst, 1) && addTail(&lst, 2));
    Node *p = find(&lst, 1, equal), *q = find(&lst, 3, equal);

    assert(p == lst._head);
    assert(q == NULL);

    clear(&lst);
}

static void test_compare(void){
    List lst1, lst2;
    create(&lst1);
    create(&lst2);
    assert(addTail(&lst1, 1) && addTail(&lst1, 2) && addTail(&lst1, 3));
    assert(addTail(&lst2, 1) && addTail(&lst2, 2) && addTail(&lst2, 3));
    
    assert(compare(&lst1, &lst2, equal) == 1);

    *lst1._head->_val = 10;

    assert(!compare(&lst1, &lst2, equal));

    clear(&lst1);
    clear(&lst2);
}
static void test_copy(void){
    List lst1, lst2;
    create(&lst1);
    create(&lst2);
    assert(addTail(&lst1, 1) && addTail(&lst1, 2) && addTail(&lst1, 3));
    copy(&lst1, &lst2);

    assert(compare(&lst1, &lst2, equal));

    assert(addTail(&lst2, 1) && addTail(&lst2, 2) && addTail(&lst2, 3));
    copy(&lst1, &lst2);

    assert(compare(&lst1, &lst2, equal));

    clear(&lst1);
    clear(&lst2);
}
static void test_reverse(void){
    List lst1, lst2;
    create(&lst1);
    create(&lst2);
    assert(addTail(&lst1, 1));
    reverse(&lst1);
    
    assert(lst1._head == lst1._tail);
    assert(lst1._size == 1);
    assert(*lst1._head->_val == 1);

    assert(addTail(&lst1, 2) && addTail(&lst1, 3) && addTail(&lst1, 4));
    assert(addHead(&lst2, 1) && addHead(&lst2, 2) && addHead(&lst2, 3) && addHead(&lst2, 4));
    reverse(&lst1);

    assert(compare(&lst1, &lst2, equal));

    copy(&lst1, &lst2);
    reverse(&lst1);
    reverse(&lst1);

    assert(compare(&lst1, &lst2, equal));

    clear(&lst1);
    clear(&lst2);
}
static void test_fill(void){
    List lst;
    create(&lst);
    assert(addTail(&lst, 1) && addTail(&lst, 2) && addTail(&lst, 3));

    fill(&lst, 9);

    assert(lst._size == 3);
    for (Node *h = lst._head; h; h = h->_next){
        assert(*h->_val == 9);
    }

    clear(&lst);
}
static void test_swap(void){
    List lst;
    create(&lst);
    assert(addTail(&lst, 1) && addTail(&lst, 2) && addTail(&lst, 3));
    swap(lst._head, lst._tail);

    assert(*lst._tail->_val == 1);
    assert(*lst._head->_val == 3);

    clear(&lst);
}

int main(){
    test(_comp);
    test(_makeEqualWithVal);
    test(_makeNode);
    test(_insert);
    test(_swap);
    puts("");
    test(create);
    test(addHead);
    test(eraseHead);
    test(clear);
    puts("");
    test(addTail);
    test(eraseTail);
    puts("");
    test(insertAt);
    test(insertAfter);
    puts("");
    test(append);
    test(prepend);
    puts("");
    test(val);
    test(size);
    test(empty);
    puts("");
    test(_eraseNode);
    test(erase);
    puts("");
    test(jump_headward);
    test(jump_tailward);
    test(at);
    test(eraseAt);
    test(eraseVal);
    test(next);
    test(prev);
    test(head);
    test(tail);
    puts("");
    test(count);
    test(find);
    puts("");
    test(compare);
    test(copy);
    test(reverse);
    test(fill);
    test(swap);
    printf("\n\t\x1b[32mAll tests passed\n");
    return 0;
}