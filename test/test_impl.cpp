#include "gtest/gtest.h"
#include <string.h>
extern "C" {
#include "impl.h"
}

TEST(create, anEmptyList) {
    PersonList *pl = createPersonList();
    ASSERT_TRUE(pl != (PersonList *)NULL);
    ASSERT_EQ(pl->people, (Person **)NULL);
    ASSERT_EQ(pl->size, 0);
    freePersonList(pl);
}

TEST(create, date) {
    Date *d = createDate(3, 10, 2019);
    ASSERT_TRUE(d != (Date *)NULL);
    ASSERT_EQ(d->month, 3);
    ASSERT_EQ(d->day, 10);
    ASSERT_EQ(d->year, 2019);
    freeDate(d);
}

TEST(create, aperson) {
    const char *name = "Joe Blow";
    float gpa = 2.14;
    Date *bd = createDate(10, 12, 2011);
    Person *p = createPerson((char *)name, gpa, bd);  // person owns date now
    ASSERT_TRUE(p != (Person *)NULL);
    ASSERT_EQ(strcmp(p->name, name), 0);
    ASSERT_EQ(p->birthDate->month, bd->month);
    ASSERT_EQ(p->birthDate->day, bd->day);
    ASSERT_EQ(p->birthDate->year, bd->year);
    freePerson(p);
}

TEST(addAperson, toAlist) {
    PersonList *pl = createPersonList();
    Date *d = createDate(5, 12, 2019);
    Person *p = createPerson((char *)"James", 3.14, d);
    addPerson(pl, p);
    ASSERT_EQ(pl->size, 1);
    ASSERT_EQ(strcmp(pl->people[0]->name, "James"), 0);
    freePersonList(pl);
}

TEST(addAperson, thenRemove) {
    PersonList *pl = createPersonList();
    Date *d1 = createDate(5, 12, 2019);
    Person *p = createPerson((char *)"James", 3.14, d1);
    addPerson(pl, p);
    Date *d2 = createDate(3, 9, 1923);
    p = createPerson((char *)"Henry", 2.41, d2);
    addPerson(pl, p);
    ASSERT_EQ(pl->size, 2);
    removePersonAtIndex(pl, 0);
    ASSERT_EQ(pl->size, 1);
    ASSERT_EQ(strcmp(pl->people[0]->name, "Henry"), 0);
    removePersonAtIndex(pl, 0);
    ASSERT_EQ(pl->size, 0);
    freePersonList(pl);
}

TEST(findPerson, inAList) {
    PersonList *pl = createPersonList();
    Date *d1 = createDate(5, 12, 2019);
    Person *p = createPerson((char *)"James", 3.14, d1);
    addPerson(pl, p);
    Date *d2 = createDate(3, 9, 1923);
    p = createPerson((char *)"Henry", 2.41, d2);
    addPerson(pl, p);
    int ix1 = findPersonByName(pl, (char *)"James");
    ASSERT_EQ(ix1, 0);
    int ix2 = findPersonByName(pl, (char *)"Henry");
    ASSERT_EQ(ix2, 1);
    int ix3 = findPersonByName(pl, (char *)"Mary");
    ASSERT_EQ(ix3, -1);
    freePersonList(pl);
}

TEST(sortList, byName) {
    PersonList *pl = createPersonList();
    Date *d1 = createDate(5, 12, 2019);
    Person *p = createPerson((char *)"Wilson", 3.14, d1);
    addPerson(pl, p);
    Date *d2 = createDate(3, 9, 1923);
    p = createPerson((char *)"Henry", 2.41, d2);
    addPerson(pl, p);
    sortPersonList(pl, SORT_BY_NAME);
    ASSERT_EQ(findPersonByName(pl, (char *)"Wilson"), 1);
    ASSERT_EQ(findPersonByName(pl, (char *)"Henry"), 0);
    freePersonList(pl);
}

TEST(sortList, byDate) {
    PersonList *pl = createPersonList();
    Date *d1 = createDate(5, 12, 2019);
    Person *p = createPerson((char *)"Abby", 3.14, d1);
    addPerson(pl, p);
    Date *d2 = createDate(3, 9, 1923);
    p = createPerson((char *)"Barbara", 3.41, d2);
    addPerson(pl, p);
    sortPersonList(pl, SORT_BY_DATE);  // sorting by name or GPA would reverse.
    ASSERT_EQ(findPersonByName(pl, (char *)"Abby"), 1);
    ASSERT_EQ(findPersonByName(pl, (char *)"Barbara"), 0);
    freePersonList(pl);
}

TEST(sortList, byGPA) {
    PersonList *pl = createPersonList();
    Date *d1 = createDate(5, 12, 1923);
    Person *p = createPerson((char *)"Abby", 3.14, d1);
    addPerson(pl, p);
    Date *d2 = createDate(3, 9, 2001);
    p = createPerson((char *)"Barbara", 2.41, d2);
    addPerson(pl, p);
    sortPersonList(pl, SORT_BY_GPA);  // sorting by name or date would reverse.
    ASSERT_EQ(findPersonByName(pl, (char *)"Abby"), 1);
    ASSERT_EQ(findPersonByName(pl, (char *)"Barbara"), 0);
    freePersonList(pl);
}
