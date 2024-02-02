#include "impl.h"
#include <stdlib.h>
#include <string.h>

/*
** Implementation of array based data structures in C.
*/

Date* createDate(int month, int day, int year) {
    /*
    ** Create a new Date object on the heap and
    ** return a pointer.
    */

    return NULL;
}

void freeDate(Date* d) {}

void freePersonMemory(char* name, Date* date, Person* p) {
    /*
    ** free the memory used by elements of the Person object,
    ** then free the Person object itself.
    */
}

void freePerson(Person* person) {
    /*
    ** Free the person object.
    */
}

Person* createPerson(char* name, float gpa, Date* birthDate) {
    /*
    ** Create a person object and return.
    **
    ** name is *owned* by caller so use strdup to make a copy.
    ** birthDate is owned by the person, just use it.
    */

    return NULL;
}

PersonList* createPersonList() {
    /*
    ** create a pointer to a new empty PersonList structure.
    */

    return NULL;
}

void freePersonList(PersonList* pList) {
    /*
    ** free all the people, free the array,
    ** free the PersonList structure itself.
    */
}

int addPerson(PersonList* list, Person* person) {
    /*
    ** add a new person to the end of the list.
    ** If successful, return 0.
    */

    return -1;
}

int removePersonAtIndex(PersonList* list, unsigned int ix) {
    /*
    ** remove person at index given. If ix >= list->size then
    ** return non-zero. If realloc fails (why would it?), then
    ** return non-zero.
    */

    return -1;
}

int findPersonByName(PersonList* list, char* name) {
    /*
    ** Iterate through the list. Return the index of the
    ** first match. If not found, return -1.
    */

    return -1;
}

int cmpPeople_byName(const void* pa, const void* pb) {
    /*
    ** compare two people objects by name.
    ** pa and pb are really Person** pointers.
    **
    ** return is like strcmp (>0, 0, <0).
    ** http://man7.org/linux/man-pages/man3/strcmp.3.html
    */

    return 0;
}

int cmpPeople_byBirth(const void* pa, const void* pb) {
    /*
    ** compare two people objects by birthDate.
    ** pa and pb are really Person** pointers.
    **
    ** return is like strcmp (>0, 0, <0).
    ** http://man7.org/linux/man-pages/man3/strcmp.3.html
    */

    return 0;
}

int cmpPeople_byGPA(const void* pa, const void* pb) {
    /*
    ** compare two people objects by gpa.
    ** pa and pb are really Person** pointers.
    **
    ** return is like strcmp (>0, 0, <0).
    ** Note: return type is explicitly `int`
    ** http://man7.org/linux/man-pages/man3/strcmp.3.html
    */

    return 0;
}

int sortPersonList(PersonList* list, SortOption sort) {
    /*
    ** Sort the pointers in the PersonList `people` member
    ** in the order specified by `sort`.
    **
    ** Hint: use the companion `cmpPeople_byXxx` function in
    ** a call to qsort. Return non-zero for error.
    */

    return -1;
}