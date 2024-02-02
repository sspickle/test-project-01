# cython: language_level=3, boundscheck=False

#
# Cython is a "glue" technology meant for creating wrapper
# libraries between python and C/C++
#

from libc.stdlib cimport malloc, free

cdef extern from "impl.h":
    cpdef enum sort_e:
        SORT_BY_DATE,
        SORT_BY_GPA,
        SORT_BY_NAME

    ctypedef sort_e SortOption

    struct date_t:
        int month
        int day
        int year

    ctypedef date_t Date

    struct person_t:
        char *name
        Date *birthDate
        float gpa

    ctypedef person_t Person

    struct personList_t:
        Person **people
        unsigned int size

    ctypedef personList_t PersonList

    Date *createDate(int month, int day, int year)
    void freeDate(Date *d)

    Person *createPerson(char *name, float gpa, Date *birthDay)
    void freePersonMemory(char *name, Date *date, Person *p)
    void freePerson(Person *person)

    PersonList *createPersonList()
    void freePersonList(PersonList *pList)

    int addPerson(PersonList *list, Person *person)
    int removePersonAtIndex(PersonList *list, unsigned int ix)
    int findPersonByName(PersonList *list, char *name)
    int sortPersonList(PersonList *list, SortOption sort)


cdef class PyPersonList:

    cdef PersonList *_person_list_ptr
    cdef dict __dict__

    def __cinit__(self):
       self._person_list_ptr = createPersonList()

    def __dealloc__(self):
        if (self._person_list_ptr):
            freePersonList(self._person_list_ptr)
            self._person_list_ptr = NULL

    def add(self, char *name, int month, int day, int year, float gpa):
        cdef Date *newDate = createDate(month, day, year)
        cdef Person *newPerson = createPerson( name, gpa, newDate)

        addPerson(self._person_list_ptr, newPerson)

    @property
    def size(self):
        return self._person_list_ptr[0].size
    
    def remove(self, int ix):
        removePersonAtIndex(self._person_list_ptr, ix)
        
    def find(self, char *name):
        return findPersonByName(self._person_list_ptr, name)
        
    def sort(self, SortOption sort):
        return sortPersonList(self._person_list_ptr, sort)
        
    def getObjs(self):
        cdef Date bd
        cdef Person pObj
        result = []
        for i in range(self.size):
            pObj = self._person_list_ptr[0].people[i][0]
            bd = pObj.birthDate[0]
            result.append({
                'name': pObj.name,
                'month': bd.month,
                'day': bd.day,
                'year': bd.year,
                'gpa': pObj.gpa,
                })
        return result
