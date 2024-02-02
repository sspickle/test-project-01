
SWEN 230: Project 1, Building Advanced C Programs
==================================================

This file is formatted in [markdown](https://daringfireball.net/projects/markdown/). You can render this file into HTML using pandoc, or any online markdown renderer (e.g., [stackedit](https://stackedit.io/app#), [dillinger](https://dillinger.io) or similar) or you can use an editor with markdown support (e.g., VS Code, BBEdit, etc.).

SWEN 230 Project 1 is all about learning how to create more complex programs using the C programming language. We'll be learning about using a `Makefile` and building programs that are partially based on "C" and partially "C++". More about that in class! For now let's discuss the project.

You should also have instructions for checking out your repository and either setting up a codespace or building programs using docker.

If you don't have either of these, please contact your instructor!

To complete this project you'll need to write the 14 functions described in 
the header file [`src/impl.h`](src/impl.h)

The project is graded on a 1-10 scale. 8 pts for the functions, and 2 pts for programming style. Style includes issues like appropriate spelling, capitalization and choice of names for variables, files, and functions (if you create your own functions) as well as spacing, indention, and placement of braces.

Each function is described in detail in the [`impl.c`](src/impl.c) file that you'll find in the `src` directory of your project's repository. This *implementation* file is a skeleton of your completed project. All you have to do is to fill in the function bodies with your implementation. For example, one function is:

    int addPerson(PersonList *list, Person *person) {
        /*
        ** Add a person to the end of the PersonList pointed to
        ** by list. The Person object is owned by the list which
        ** will free it when the list is freed, or the Person object
        ** is removed.
        */
        
        /* Enter you code here. */
        
        return 0;
    }

So, `list` is a pointer to a `PersonList` structure, which consists of a pointer to an array of pointers to Person structures, and a count of the number of elements in the array. 

    typedef struct personList_t {
        Person **people;
        unsigned int size;
    } PersonList;

Each Person structure has a char array for `name`, a Date object for `birthDate`, and a floating point value for `gpa`.

    typedef struct person_t {
        char *name;
        float gpa;
        Date *birthDate;
    } Person;

Where `Date` is defined like so:

    typedef struct date_t {
        int month;
        int day;
        int year;
    } Date;

The whole picture of the data structure ends up looking like this:

    +--------------------------+
    |                          |
    |  PersonList              |
    |                          |
    |   int size               |
    |   Person **people        |
    |              +           |
    +--------------------------+
                   |    array of "size" instances of Person,
                   |    name, Date structures/arrays.
                   |
                   v    +---------------------------->
        +----------+--------------------------------------------+
        |                  |                  |                 |
        |Person *people[0] |Person *people[1] |Person *people[2]|
        +--------+-------------------+-----------------+--------+
                 |                   |                 |
       +---------v--------+ +--------v-------+ +-------v--------+
       |                  | |                | |                |
       |  Person          | | Person         | | Person         |
    +--+  char *name      | | char *name     | | char *name     |
    |  |  Date *birthDate | | Date *birthDate| | Date *birthDate|    . . .
    |  |  float gpa       | | float gpa      | | float gpa      |
    |  |                  | |                | |                |
    |  |                  | |                | |                |
    |  +----------------+-- +-+-------------++ +--+-------------+
    |                   |     |             |     |             |
    |  +--------------+ |  +--v-----------+ |  +--v-----------+ |
    +->+ Name 0       | |  | Name 1       | |  | Name 2       | |    . . .
       +--------------+ |  +--------------+ |  +--------------+ |
                        |                   |                   |
       +--------------+ |  +--------------+ |  +--------------+ |
       |              | |  |              | |  |              | |
       | Date0        | |  | Date1        | |  | Date2        | |
       | int month    +<+  | int month    +<+  | int month    +<+    . . .
       | int day      |    | int day      |    | int day      |
       | int year     |    | int year     |    | int year     |
       |              |    |              |    |              |
       |              |    |              |    |              |
       +--------------+    +--------------+    +--------------+

There are functions for creating and freeing Date structures on the heap:

    Date *createDate(int month, int day, int year);
    void freeDate(Date *d);

There are functions for creating and freeing Person structures on the heap:

    Person *createPerson(char *name, float gpa, Date *birthDay);
    void freePersonMemory(char *name, Date *date, Person *p);
    void freePerson(Person *person);

And there are functions for creating and freeing PersonList structures:

    PersonList *createPersonList(void);
    void freePersonList(PersonList *pList);

It should be noted that `freePersonList()`  will free every `Person`, `name`, `Date`, the `people` array, as well as the `PersonList` structure itself!

There are functions to manipulation the PersonList structure:

    int addPerson(PersonList *list, Person *person);
    int removePersonAtIndex(PersonList *list, unsigned int ix);
    int findPersonByName(PersonList *list, char *name);
    int sortPersonList(PersonList *list, SortOption sort);
    
Note, similarly, removePersonAtIndex frees all the memory associated
with that Person structure.

Finally there are *helpers* (compare functions) for the sortPersonList function:

    int cmpPeople_byName(const void *pa, const void *pb);
    int cmpPeople_byBirth(const void *pa, const void *pb);
    int cmpPeople_byGPA(const void *pa, const void *pb);

The directory structure of the repository looks like this:

    ├── Dockerfile
    ├── Makefile
    ├── README.md
    ├── docker-compose.yml
    ├── psrc
    │   ├── cimpl.pyx
    │   ├── flask_app.py
    │   ├── setup.py
    │   ├── static
    │   │   └── display.css
    │   └── templates
    │       └── display.html
    ├── src
    │   ├── impl.c
    │   ├── impl.h
    │   └── main.c
    └── test
        └── test_impl.cpp

Don't worry too much, for the moment, about the `psrc` directory. It contains
the code for a python wrapper to your functions, as well as a web interface
to exersize your functions (see `BONUS` below).

For now, review the required function signatures described in `src/impl.h` and the function skeletons in `src/impl.c`. Write your solutions in 'src/impl.c'.

You can build your project with `make` in a codespace or a docker container.

You can do some baseline testing with `make test` and `make vtest` (including valgrind).

When you're ready to submit just push your repository back to gitkeeper.

Then check your email for feedback!

Your project will be evaluated for: a) functional correctness (80%) and b) style (20%).

You can check for Google Style compliance using `make lint`. If you want the linter to fix your style for you, you can use `make lint-fix`. Sometimes lint cannot fix style problems but many times it can.

**Plagiarism**: You may collaborate with your classmates in discussing ideas, problems and strategies to write your program, so long as you give attribution for the ideas gleaned in this way, but you may not *share* *actual* *code* with anyone.  Your code may be evaluated using an automated tool [(MOSS)](http://theory.stanford.edu/~aiken/moss/) to detect potential plagiarism. 

Enjoy!

P.S. to test your code run:

    make test

and

    make vtest

P.P.S. to run a simple webserver that exercises your code run:

    python3 psrc/flask_app.py

Then you can connect on port 5000

