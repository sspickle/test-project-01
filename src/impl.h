
typedef enum sort_e { SORT_BY_DATE, SORT_BY_GPA, SORT_BY_NAME } SortOption;

typedef struct date_t {
    int month;
    int day;
    int year;
} Date;

typedef struct person_t {
    char* name;
    float gpa;
    Date* birthDate;
} Person;

typedef struct personList_t {
    Person** people;
    unsigned int size;
} PersonList;

// Date Functions. Dates are allocated on the heap only.

Date* createDate(int month, int day, int year);
void freeDate(Date* d);

// Person functions. Person objects are allocated on the heap.
// The Date object is owned by the Person object.
// The name, in contrast, is owned by the caller.

Person* createPerson(char* name, float gpa, Date* birthDay);
void freePersonMemory(char* name, Date* date, Person* p);
void freePerson(Person* person);

// Person lists are allocated on the heap.

PersonList* createPersonList(void);
void freePersonList(PersonList* pList);

// Once added, Person objects are owned by the list.
// Removed person objects are freed.
// Sorting is done in-place.

int addPerson(PersonList* list, Person* person);
int removePersonAtIndex(PersonList* list, unsigned int ix);
int findPersonByName(PersonList* list, char* name);
int sortPersonList(PersonList* list, SortOption sort);

// cmpPeople_byXxx functions are helpers used by qsort in sortPersonList

int cmpPeople_byName(const void* pa, const void* pb);
int cmpPeople_byBirth(const void* pa, const void* pb);
int cmpPeople_byGPA(const void* pa, const void* pb);
