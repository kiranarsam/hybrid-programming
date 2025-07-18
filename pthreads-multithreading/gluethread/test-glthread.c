#include "glthread.h"
#include <memory.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

// structure person
typedef struct person__ {
    int age;
    int weight;
    glthread_t glthread;
} person_t ;

// Comparision function
int senior_citizen(void *per1, void *per2) {

    person_t *p1 = (person_t *)per1;
    person_t *p2 = (person_t *)per2;

    if(p1->age == p2->age) return 0;
    if(p1->age < p2->age) return 1;
    return -1;
}

// Find the structure member field name offset in the defined structure
#define offset(struct_name, fld_name)  ((uintptr_t)(&(((struct_name *)0)->fld_name)))

// define thread_to_person function: from glthread to actual structure pointer
GLTHREAD_TO_STRUCT(glthread_to_person, person_t, glthread);

int main(int argc, char **argv)
{
  printf("offset value = %ld\n", offset(person_t, glthread));
    person_t person[5];
    memset(person, 0, sizeof(person_t) * 5);
    person[0].age = 1;
    person[0].weight = 2;
    person[1].age = 3;
    person[1].weight = 4;
    person[2].age = 5;
    person[2].weight = 6;
    person[3].age = 7;
    person[3].weight = 8;
    person[4].age = 9;
    person[4].weight = 10;

    glthread_t base_glthread;
    init_glthread(&base_glthread);

    glthread_priority_insert(&base_glthread, &person[4].glthread, senior_citizen, (int)offset(person_t, glthread));
    glthread_priority_insert(&base_glthread, &person[3].glthread, senior_citizen, (int)offset(person_t, glthread));
    glthread_priority_insert(&base_glthread, &person[2].glthread, senior_citizen, (int)offset(person_t, glthread));
    glthread_priority_insert(&base_glthread, &person[1].glthread, senior_citizen, (int)offset(person_t, glthread));
    glthread_priority_insert(&base_glthread, &person[0].glthread, senior_citizen, (int)offset(person_t, glthread));

    glthread_t *curr = NULL;
    ITERATE_GLTHREAD_BEGIN(&base_glthread, curr) {
        person_t *p = glthread_to_person(curr);
        printf("Age = %d\n", p->age);
    } ITERATE_GLTHREAD_END(&base_glthread, curr);

    return 0;
}