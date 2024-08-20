#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

typedef struct date {
    int d, m, y;
} Date;
typedef struct person {
    int id;
    char *name;
    double salary;
    Date birthDate;
    bool gender; // 1 for male, 0 for female;
} Person;

#define ElementType Person
typedef ElementType* ElementTypePtr;
#define __compare_functions
int equalids(ElementTypePtr _E1, ElementTypePtr _E2){
    return _E1->id == _E2->id;
}
int greater(ElementTypePtr _E1, ElementTypePtr _E2){
    return _E1->salary > _E2->salary;
}
int smaller(ElementTypePtr _E1, ElementTypePtr _E2){
    return _E1->salary < _E2->salary;
}
#define __printElement
void _printElement(ElementType *_E){
    printf("Id: %d\n\tName: %s\n\tSalary: %f\n\tBirthdate: %d/%d/%d\n\tGender: %s\n", 
    _E->id, 
    _E->name,
    _E->salary,
    _E->birthDate.d,
    _E->birthDate.m,
    _E->birthDate.y,
    _E->gender ? "Male" : "Female");
}
#define __traverseFunction
int _traverseFunction(ElementType *_E){
    _printElement(_E);
    return 0;
}

int id = 1;

#define printy(x) printf("\n-=-=-=-=--=-=-=-=--=-=-=-=-\n" \
                        #x"\n-=-=-=-=--=-=-=-=--=-=-=-=-\n");

ElementType makeEmployee(
    char* name, 
    double salary,
    int dd, 
    int mm, 
    int yy,
    bool gender
){
    return (ElementType){++id, name, salary, (Date){dd, mm, yy}, gender};
}
ElementType randEmp(char* name, bool gender){
    return (ElementType){++id, name, rand()%8888+1000, 
    (Date){rand()%30+1, rand()%12+1, rand()%20+1980}, 
    gender};
}
int equal_names(ElementTypePtr _E1, ElementTypePtr _E2){
    return !strcmp(_E1->name, _E2->name);
}
#include "src/doubly_linked_list.c"
int main(){
    List Employees;
    create(&Employees);
    addHead(&Employees, (ElementType){1, "Ahmed", 5600, (Date){12, 10, 2000}, 1});
    addHead(&Employees, makeEmployee("Salma", 1200, 3, 1, 1998, 0));
    addTail(&Employees, makeEmployee("Mohamed", 3600, 6, 12, 2001, 1));
    addHead(&Employees, makeEmployee("Essam", 2900, 7, 6, 1988, 1));
    addTail(&Employees, makeEmployee("Abdulrahman", 9000, 9, 10, 2003, 1));
    addHead(&Employees, makeEmployee("Mohab Salama", 12000, 14, 8, 2000, 1));
    addTail(&Employees, makeEmployee("Yara Mahgoub", 5400, 19, 4, 1999, 0));
    printf("Added 7 employees\n");
    printAllElements(&Employees, "\n");


    eraseHead(&Employees);
    printy(Erased Head);
    printAllElements(&Employees, "\n");


    eraseTail(&Employees);
    printy(Erased Tail);
    printAllElements(&Employees, "\n");


    insertAt(&Employees, makeEmployee("Haneen", 4900, 23, 4, 1997, 0), 3);
    printy(Haneen inserted at index 3);
    printAllElements(&Employees, "\n");


    ListIterator h = head(&Employees), t = tail(&Employees), thindex = at(&Employees, 3);
    insertAfter(&Employees, makeEmployee("Ramdan", 3000, 23, 4, 1997, 0), thindex);
    printy(Ramdan inserted after the third index);
    printAllElements(&Employees, "\n");


    printy(Size of the List); printf("%lld\n", size(&Employees));
    printy(Value at index 5); _printElement(val(at(&Employees, 5)));
    printy(Value at index 0); _printElement(val(at(&Employees, 0)));
    printy(Value at index -1); _printElement(val(at(&Employees, -1)));
    printy(Value at index -4); _printElement(val(at(&Employees, -4)));
    printy(Value at index -7); _printElement(val(at(&Employees, -7)));

    clear(&Employees);
    printy(List is cleared and the new size is);
    printf("%lld\n", size(&Employees));


    addHead(&Employees, randEmp("Ahmed", 1));
    addHead(&Employees, randEmp("Osama", 1));
    addHead(&Employees, randEmp("Mohamed", 1));
    addHead(&Employees, randEmp("Sameh", 1));
    addHead(&Employees, randEmp("Ehab", 1));
    addHead(&Employees, randEmp("Mohamed", 1));
    addHead(&Employees, randEmp("Eshraq", 0));
    addHead(&Employees, randEmp("Mohamed", 1));
    addHead(&Employees, randEmp("Rana", 0));
    addHead(&Employees, randEmp("Sohair", 0));
    printy(Added 10 random employees);
    printAllElements(&Employees, "\n");


    thindex = at(&Employees, 3);
    erase(&Employees, thindex);
    printy(Erased the Employee at index 3);
    printAllElements(&Employees, "\n");
    
    
    eraseVal(&Employees, (ElementType){15}, equalids);
    printy(Erased employee with id 15);
    printAllElements(&Employees, "\n");


    eraseVal(&Employees, (ElementType){15, "Mohamed"}, equal_names);
    printy(Erased employee with name Mohamed);
    printAllElements(&Employees, "\n");


    addHead(&Employees, randEmp("Ahmed", 1));
    addHead(&Employees, randEmp("Osama", 1));
    addHead(&Employees, randEmp("Mohamed", 1));
    addHead(&Employees, randEmp("Sameh", 1));
    addHead(&Employees, randEmp("Ehab", 1));
    addHead(&Employees, randEmp("Mohamed", 1));
    addHead(&Employees, randEmp("Eshraq", 0));
    addHead(&Employees, randEmp("Mohamed", 1));
    addHead(&Employees, randEmp("Rana", 0));
    addHead(&Employees, randEmp("Mohamed", 1));
    printy(Added 10 random employees);
    printAllElements(&Employees, "\n");


    ListSize counter = count(&Employees, makeEmployee("Mohamed", 0, 0, 0, 0, 0), equal_names);
    printy(Count number of Employees with name Mohamed);
    printf("%lld\n", counter);


    printy(Print employee with id number 13);
    _printElement(find(&Employees, (ElementType){13}, equalids)->_val);


    swap(find(&Employees, (ElementType){10}, equalids), find(&Employees, (ElementType){19}, equalids));
    printy(Swaped Id 10 with Id 19);
    printAllElements(&Employees, "\n");


    reverse(&Employees);
    printy(Reversed the List);
    printAllElements(&Employees, "\n");

    fill(&Employees, (ElementType){12, "Saleh"});
    printy(Filled the list with id 12 and name Saleh);
    printAllElements(&Employees, "\n");

    
    clear(&Employees);
    return 0;
}