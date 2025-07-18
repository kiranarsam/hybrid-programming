#include "glthread.h"
#include <stdlib.h>
#include <stdio.h>
#include <memory.h>

typedef struct employee__ {
    char name[30];
    unsigned int salary;
    char designation[30];
    unsigned int emp_id;
    glthread_t glthread;
} emp_t;

void print_emp_details(emp_t *emp) {
    printf("Employee name = %s\n", emp->name);
    printf("salary = %u\n", emp->salary);
    printf("designation = %s\n", emp->designation);
    printf("emp_id = %u\n", emp->emp_id);
}

// Construct glthread to emp_t structure
GLTHREAD_TO_STRUCT(glthread_to_emp, emp_t, glthread);

int main(int argc, char **argv)
{
    emp_t *emp1  = calloc(1, sizeof(emp_t));
    strncpy(emp1->name, "Neha", strlen("Neha"));
    emp1->salary = 50000;
    strncpy(emp1->designation, "HR", strlen("HR"));
    emp1->emp_id = 21;
    init_glthread(&emp1->glthread);

    emp_t *emp2  = calloc(1, sizeof(emp_t));
    strncpy(emp2->name, "Abhishek", strlen("Abhishek"));
    emp1->salary = 150000;
    strncpy(emp2->designation, "SE3", strlen("SE3"));
    emp2->emp_id = 32;
    init_glthread(&emp2->glthread);

    emp_t *emp3  = calloc(1, sizeof(emp_t));
    strncpy(emp3->name, "Arun", strlen("Arun"));
    emp3->salary = 60000;
    strncpy(emp3->designation, "SE4", strlen("SE4"));
    emp3->emp_id = 27;
    init_glthread(&emp3->glthread);

    /*Now Create a glthread*/
    glthread_t *emp_list = calloc(1, sizeof(glthread_t));
    init_glthread(emp_list);

    /*Now insert the records in glthread*/
    glthread_add_next(emp_list, &emp1->glthread);
    glthread_add_next(emp_list, &emp2->glthread);
    glthread_add_next(emp_list, &emp3->glthread);

    /*Walk over glthread*/
    glthread_t *ptr = NULL;
    ITERATE_GLTHREAD_BEGIN(emp_list, ptr) {
      emp_t *p = glthread_to_emp(ptr);
      print_emp_details(p);
    } ITERATE_GLTHREAD_END(emp_list, ptr);

    /*Let us remove one record at random*/
    remove_glthread(&emp2->glthread);
    free(emp2);
    printf("\nprinting again . . . \n");

    ptr = NULL;
    ITERATE_GLTHREAD_BEGIN(emp_list, ptr) {
      emp_t *p = glthread_to_emp(ptr);
      print_emp_details(p);
    } ITERATE_GLTHREAD_END(emp_list, ptr);


    /*Free all Dynamicall allocations*/
    ptr = NULL;
    ITERATE_GLTHREAD_BEGIN(emp_list, ptr) {
      emp_t *p = glthread_to_emp(ptr);
      free(p);
    } ITERATE_GLTHREAD_END(emp_list, ptr);
    free(emp_list);

    return 0;
}
