# Doubly Linked List Implementation In C: Documentation

## Introduction

This documentation provides details on how to use this implementation of Doubly Linked List in C.

## How to Use the Library
Types breakdown:
  - `ElementType`: A data type used to represent the data inside the list. It can be any data type that supports equality and ordering.
    ```c
    #define ElementType int
    ```
  - `ElementTypePtr`: Defined as a pointer of type `ElementType*`.
    ```c
    typedef ElementType* ElementTypePtr;
    ```
  - `ListSize`: Defined as `unsigned long long` to represent the size of the list.
    ```c
    typedef unsigned long long ListSize;
    ```
  - `Node`: In this implementation, a `Node` holds a pointer of type `ElementType*`, as well as `next` and `prev` pointers of type `Node*`.
    ```c
    typedef struct node {
    ElementTypePtr _val;
    struct node *_next, *_prev;
    } Node;
    ```
  - `ListIterator`: A pointer of type `Node*`.
    ```c
    typedef Node* ListIterator;
    ```
  - `List`: It stores 2 pointers of type `Node*` to the head and the tail, also it stores the list's current size.
    ```c
    typedef struct list {
    Node *_head;
    Node *_tail;
    ListSize _size;
    } List;
    ```
To use this library, follow these steps:
1. **Define Your Element Type:** Define the `ElementType` according to your needs. You must define the macro `ElementType`. The type should be compatible with operations such as comparison and assignment.
  - Default type is `int`.
    ```c
    #define ElementType int
    ```
2.  **Implement Comparison Functions:** Implement functions to compare elements for equality and ordering, you can set more than compare function for the same purpose based on the context. You must define the macro `__compare_functions`.
  - Default comparison functions are basic integer comparisons.
  - Prototype of a comparison function should be:
    ```c
      int fun(ElementType*, ElementType*);
    ```
  - Default comparison functions:
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
    ```
3.  **Implement a printing and traversing function** Implement a function that only prints an element. Implement another function for traversing. Define macros `__printElement`, `__traverseFunction` respectively.
  - Prototype of a printing function should be:
    ```c
      void fun(ElementType*);
    ```
  - Prototype of a traversing function should be:
    ```c
      int fun(ElementType*);
    ```
  - Default printing function prints one integer, default traversing function is printing.
    ```c
      #define __printElement
      void _printElement(ElementType *_E){
        printf("%d", *_E);
      }
    ```
    ```c
      #define __traverseFunction
      int _traverseFunction(ElementType *_E){
        printf("%d ", *_E);
        return 0;
      }
    ```
Now you can use `List` type to declare new lists.
## Interface:
**Passing the list to the functions is always by reference**
  - Declaring a new list or list iterators using `List`, `ListIterator`:
    ```c
      List myList;
      ListIterator it;
    ```

  - **`create():`**
    - It's used to initialize the list members with null values. Use it after declaring a new list.
      ```c
        List myList;
        create(&myList);
      ```

  - **`clear():`**
    - Erases and frees memory of all elements in the list.
    - User must call it before the program ends to avoid memory leaks.
      ```c
        clear(&myList);
      ```

  - **`jump_headward():`**
    - Skips elements in the list in the HEAD direction.
    - Returns an iterator to the element if it's a valid element in the list, `NULL` otherwise
      ```c
        ListIterator it = jump_headward(currentIterator, 3);
      ```

  - **`jump_tailward():`**
    - Skips elements in the list in the TAIL direction.
    - Returns an iterator to the element if it's a valid element in the list, `NULL` otherwise
      ```c
        ListIterator it = jump_tailward(currentIterator, 3);
      ```

  - **`next():`**
    - Advances the iterator to the tail direction by 1 step.
    - Returns an iterator to the element if it's a valid element in the list, `NULL` otherwise
      ```c
        ListIterator it = next(currentIterator);
      ```

  - **`prev():`**
    - Advances the iterator to the head by 1 step.
    - Returns an iterator to the element if it's a valid element in the list, `NULL` otherwise
      ```c
        ListIterator it = prev(currentIterator);
      ```

  - **`at():`**
    - Get an iterator pointing at the element in the specified index (zero-based), including negative indexing.
    - `0` is the first element at the head, `-1` is the last element at the tail, `-2` is second to last, ...
    - The index of the element should be between `[-size, size-1]` inclusive.
    - Returns an iterator points at the element at the index, `NULL` if it's out-of-boundary
      ```c
        ListIterator it = at(&myList, 2);
      ```

  - **`head():`**
    - Returns an iterator to the Head element in the list.
      ```c
        ListIterator it = head(&myList);
      ```

  - **`tail():`**
    - Returns an iterator to the Tail element in the list.
      ```c
        ListIterator it = tail(&myList);
      ```

  - **`val():`**
    - Returns a pointer to the value in the node pointed to by the iterator.
      ```c
        ElementType *value = val(currentIterator);
      ```

  - **`size():`**
    - Returns the number of elements in the list.
      ```c
        ListSize size = size(&myList);
      ```

  - **`empty():`**
    - Returns `1` if the list has no elements, `0` otherwise.
      ```c
        int isEmpty = empty(&myList);
      ```

  - **`addHead():`**
    - Used to allocate memory and add a new element of type `ElementType` in the head side of the list.
    - Returns a `ListIterator` to the added head or `NULL`  in case of failure.
      ```c
        ListIterator it = addHead(&myList, 12);
      ```

  - **`addTail():`**
    - Used to allocate memory and add a new element of type `ElementType` in the tail side of the list.
    - Returns a `ListIterator` to the added tail or `NULL`  in case of failure.
      ```c
        ListIterator it = addTail(&myList, 12);
      ```

  - **`insertAt():`**
    - Allocate memory and insert an element in the specified index (zero-based) allowing negative indexing.
    - An iterator to the inserted node in case of successful insertion, `NULL` otherwise
      ```c
        ListIterator it = insertAt(&myList, 12, 2);
      ```

  - **`insertAfter():`**
    - Allocate memory and insert an element after a specified node in the list.
    - Returns an iterator to the inserted element in case of successful insertion, `NULL` otherwise
      ```c
        ListIterator it = insertAfter(&myList, 12, currentIterator);
      ```

  - **`append():`**
    - Allocate memory and append all elements in `source` list to the Tail of `destination` list.
      ```c
        append(&sourceList, &destinationList);
      ```

  - **`prepend():`**
    - Allocate memory and prepend all elements in `source` list to the Tail of `destination` list.
      ```c
        prepend(&sourceList, &destinationList);
      ```

  - **`eraseHead():`**
    - Erases and frees the memory allocated by the Head element in the list (the left most element).
    - Returns an iterator to the new head in success removal, `NULL` if the list is empty before or after the removal
      ```c
        ListIterator it = eraseHead(&myList);
      ```

  - **`eraseTail():`**
    - Erases and frees the memory allocated by the Tail element in the list (the right most element).
    - Returns an iterator to the new tail in success removal, `NULL` if the list is empty before or after the removal
      ```c
        ListIterator it = eraseTail(&myList);
      ```

  - **`erase():`**
    - Erases and frees the memory allocated by the element pointed to by an iterator.
    - Returns an iterator points at the next element in the list, `NULL` if it's the last element or list is empty
      ```c
        ListIterator it = erase(&myList, currentIterator);
      ```

  - **`eraseAt():`**
    - Erases an element at a specific index in the list (zero-based), including negative indexes.
    - Returns an iterator points at the next element in the list, `NULL` if it's the last element or index is out-of-bound
      ```c
        ListIterator it = eraseAt(&myList, 2);
      ```

  - **`eraseVal():`**
    - Erases all occurrences of a particular value from the list.
    - User must pass the equal function that the list elements will be compared against.
    - Returns number of elements erased.
      ```c
        ListSize count = eraseVal(&myList, 12, equalFunction);
      ```

  - **`find():`**
    - Finds an element inside a list.
    - User must pass the equal function that the list elements will be compared against.
    - Returns iterator pointing at the first occurrence of the element in the list if it's present, `NULL` otherwise.
      ```c
        ListIterator it = find(&myList, 12, equalFunction);
      ```

  - **`count():`**
    - Count the number of element occurrences in the list.
    - User must pass the equal function that the list elements will be compared against.
    - Returns number of elements matched.
      ```c
        ListSize count = count(&myList, 12, equalFunction);
      ```

  - **`traverse_tailward():`**
    - Traverse the elements of the list with a special function (from Head to Tail).
    - User must provide the traversal function (default is printing).
      ```c
        ListSize result = traverse_tailward(&myList, traversalFunction);
      ```

  - **`traverse_headward():`**
    - Traverse the elements of the list with a special function (from Tail to Head).
    - User must provide the traversal function (default is printing).
      ```c
        ListSize result = traverse_headward(&myList, traversalFunction);
      ```

  - **`reverse():`**
    - Reverse the list in-place.
      ```c
        reverse(&myList);
      ```

  - **`fill():`**
    - Make all list elements equal to a specific value.
      ```c
        fill(&myList, 12);
      ```

  - **`copy():`**
    - Allocate memory and copy all elements in source to destination, excess elements in destination are freed.
      ```c
        copy(&sourceList, &destinationList);
      ```

  - **`printAllElements():`**
    - Print all elements in the list in order from Head to Tail.
    - User must provide a separator of type string literal that will be printed between each two nodes.
      ```c
        printAllElements(&myList, ", ");
      ```

  - **`swap():`**
    - Swaps two elements using their iterators.
      ```c
        swap(iterator1, iterator2);
      ```

  - **`compare():`**
    - Compares two lists regarding number of elements and elements.
    - User must pass the equal function that the list elements will be compared against.
      ```c
        int result = compare(&list1, &list2, equalFunction);
      ```  
## Example
Below is an example of using the list to store some data about some people.
  ```c
  #include <stdio.h>
	#include <stdbool.h>
	#include <stdlib.h>
	#include <string.h>
	typedef struct person {
    char *name;
    int age;
    bool gender; // 1 for male, 0 for female;
	} Person;

	#define ElementType Person
	typedef ElementType* ElementTypePtr;
	#define __compare_functions
	int equalnames(ElementTypePtr _E1, ElementTypePtr _E2){
			return strcmp(_E1->name, _E2->name);
	}
	int greater(ElementTypePtr _E1, ElementTypePtr _E2){
			return _E1->age > _E2->age;
	}
	int smaller(ElementTypePtr _E1, ElementTypePtr _E2){
			return _E1->age < _E2->age;
	}
	#define __printElement
	void _printElement(ElementType *_E){
    printf("Name: %s\n\tAge: %d\n\tGender: %s\n", 
    _E->name,
    _E->age,
    _E->gender ? "Male" : "Female");
	}
	#define __traverseFunction
	int _traverseFunction(ElementType *_E){
			_printElement(_E);
			return 0;
	}
	#include "src/doubly_linked_list.c"
	int main(){
			List Employees;
			create(&Employees);
			addHead(&Employees, (ElementType){"Ahmed", 15, 1});
			addTail(&Employees, (ElementType){"Salma", 22, 0});
			printAllElements(&Employees, "\n");
			clear(&Employees);
			return 0;
	}
```
Output: 
```
Name: Ahmed
      Age: 15
      Gender: Male

Name: Salma
        Age: 22
        Gender: Female
```
## Testing
```bash
make test
```
## Challenges
	- Only one type allowed in the program. 
	- Not circular
	- Lacking sort function
	- Not fully generic, can't use multiple lists of different data types in one program
  	- ...
