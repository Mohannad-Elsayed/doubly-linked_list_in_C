#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <float.h>
#include <math.h>

#define test(fn) \
    printf("Testing: " # fn "\n"); \
    test_##fn(); //Call the test function

#define ElementType long long
#define equal(a,b) (a)==(b)
#define greater(a, b) (a)>(b)
#define smaller(a, b) (a)<(b)

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
static void test__comp(void){}
static void test__makeEqualWithVal(void){}
static void test__find(void){}
static void test__count(void){}
static void test__insert(void){}
static void test__swap(void){}
static void test__makeNode(void){}
static void test__eraseNode(void){}


static void test_create(void){}
static void test_clear(void){}

static void test_jump_headward(void){}
static void test_jump_tailward(void){}
static void test_next(void){}
static void test_prev(void){}
static void test_at(void){}
static void test_head(void){}
static void test_tail(void){}

static void test_val(void){}
static void test_size(void){}
static void test_empty(void){}

static void test_addHead(void){}
static void test_addTail(void){}
static void test_insertAt(void){}
static void test_insertAfter(void){}
static void test_append(void){}
static void test_prepend(void){}

static void test_eraseHead(void){}
static void test_eraseTail(void){}
static void test_erase(void){}
static void test_eraseAt(void){}
static void test_eraseVal(void){}

static void test_find(void){}
static void test_count(void){}

static void test_traverse_headward(void){}
static void test_traverse_tailward(void){}

static void test_reverse(void){}
static void test_fill(void){}

static void test_copy(void){}
static void test_printAllElements(void){}

static void test_swap(void){}

int main(){
    test(_comp);
    test(_makeEqualWithVal);
    test(_count);
    test(_insert);
    test(_swap);
    test(_makeNode);
    test(_eraseNode);
    puts("");
    test(create);
    test(clear);
    puts("");
    test(jump_headward);
    test(jump_tailward);
    test(next);
    test(prev);
    test(at);
    test(head);
    test(tail);
    puts("");
    test(val);
    test(size);
    test(empty);
    puts("");
    test(addHead);
    test(addTail);
    test(insertAt);
    test(insertAfter);
    test(append);
    test(prepend);
    puts("");
    test(eraseHead);
    test(eraseTail);
    test(erase);
    test(eraseAt);
    test(eraseVal);
    puts("");
    test(find);
    test(count);
    puts("");
    test(traverse_headward);
    test(traverse_tailward);
    puts("");
    test(reverse);
    test(fill);
    puts("");
    test(copy);
    test(printAllElements);
    puts("");
    test(swap);
    puts("");
    printf("\n\tAll tests passed\n");
    return 0;
}