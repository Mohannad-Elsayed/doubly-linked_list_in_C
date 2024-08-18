# Doubly Linked List Library Documentation

## Introduction

This documentation provides details on how to use the Doubly Linked List library implemented in C. The library supports various operations on doubly linked lists, including insertion, deletion, traversal, and more.

## How to Use the Library
Types breakdown:
  - `ElementType`: A data type used to represent the data inside the list. It can be any data type that supports equality and ordering.
    ```c
    #define ElementType int
  - `ElementTypePtr`: Defined as a pointer of type `ElementType*`.
    ```c
    typedef ElementType* ElementTypePtr;
  - `ListSize`: Defined as `unsigned long long` to represent the size of the list.
    ```c
    typedef unsigned long long ListSize;
  - `Node`: In the implementation, a `Node` holds a pointer of type `ElementType*`, as well as `next` and `prev` pointers of type `Node*`.
    ```c
    typedef struct node {
    ElementTypePtr _val;
    struct node *_next, *_prev;
    } Node;
  - `ListIterator`: A pointer of type `Node*`.
    ```c
    typedef Node* ListIterator;
  - `List`: It stores 2 pointers of type `Node*` to the head and the tail, also it stores the list current size.
    ```c
    typedef struct list {
    Node *_head;
    Node *_tail;
    ListSize _size;
    } List;
  
To use this library, follow these steps:
1. **Define Your Element Type:** Define the `ElementType` according to your needs, and define the macro `ElementType`. The type should be compatible with operations such as comparison and assignment.
   - Default type is `int`.
    ```c
    #define ElementType int
2.  **Implement Comparison Functions:** Implement functions to compare elements for equality and ordering, you can set more than compare function for the same purpose based on the context. Define the macro `__compare_functions`.
   - Default comparison functions are basic integer comparisons.
     ```c
      #define __compare_functions
      int equal_fun(ElementTypePtr e1, ElementTypePtr e2) {
       return (*e1 == *e2);
      }
      int greater_fun(ElementTypePtr e1, ElementTypePtr e2) {
          return (*e1 > *e2);
      }
      int smaller_fun(ElementTypePtr e1, ElementTypePtr e2) {
          return (*e1 < *e2);
      }
3.  **Implement a printing and traversing function** Implement a function using the prototype below and only prints that element, and one for traversing. Define macros `__printElement`, `__traverseFunction` respectively.
     ```c
     #define __printElement
     void _printElement(ElementType *_E){
     printf("%d", *_E);
     }
   - Default printing function prints one integer, default traversing function is printing.
     ```c
     #define __traverseFunction
     int _traverseFunction(ElementType *_E){
     printf("%d ", *_E);
     return 0;
     }
Now you can use `List` type to declare new lists.
