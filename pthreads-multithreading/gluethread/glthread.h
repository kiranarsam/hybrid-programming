#ifndef __GLUETHREAD__
#define __GLUETHREAD__

typedef struct glthread__ {

    struct glthread__ *left;
    struct glthread__ *right;
} glthread_t;

void glthread_add_next(glthread_t *pHead, glthread_t *new_glthread);

void glthread_add_before(glthread_t *pHead, glthread_t *new_glthread);

void remove_glthread(glthread_t *glthread);

/** Initialize the glthread structure */
void init_glthread(glthread_t *glthread);

void glthread_add_last(glthread_t *pHead, glthread_t *new_glthread);

#define IS_GLTHREAD_LIST_EMPTY(glthreadptr)  ((glthreadptr)->right == 0 && (glthreadptr)->left == 0)

#define GLTHREAD_TO_STRUCT(fn_name, structure_name, field_name)                        \
    static inline structure_name * fn_name(glthread_t *glthreadptr) {                   \
        return (structure_name *)((char *)(glthreadptr) - (char *)&(((structure_name *)0)->field_name)); \
    }

/* delete safe loop*/
/*Normal continue and break can be used with this loop macro*/

#define BASE(glthreadptr)   ((glthreadptr)->right)

// BEGIN MACRO to iterate from glthread base pointer
#define ITERATE_GLTHREAD_BEGIN(glthreadptrstart, glthread_curr_ptr)             \
 {                                                                              \
    glthread_t *glthread_next_ptr = NULL;                                       \
    glthread_curr_ptr = BASE(glthreadptrstart);                                 \
    for(; glthread_curr_ptr != NULL; glthread_curr_ptr = glthread_next_ptr) {   \
        glthread_next_ptr = (glthread_curr_ptr)->right;

// END MACRO for flthread base pointer
#define ITERATE_GLTHREAD_END(glthreadptrstart, glthread_curr_ptr)               \
    }                                                                           \
  }

#define GLTHREAD_GET_USER_DATA_FROM_OFFSET(glthreadptr, offset)  \
    (void *)((char *)(glthreadptr) - offset)

void delete_glthread_list(glthread_t *pHead);

unsigned int get_glthread_list_count(glthread_t *pHead);

void glthread_priority_insert(glthread_t *pHead,
                         glthread_t *glthread,
                         int (*comp_fn)(void *, void *),
                         int offset);

glthread_t * dequeue_glthread_first(glthread_t *base_glthread);

#endif /* __GLUETHREAD__ */