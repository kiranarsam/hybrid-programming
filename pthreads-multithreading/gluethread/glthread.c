#include "glthread.h"
#include <stdlib.h>

void init_glthread(glthread_t *glthread){

    glthread->left = NULL;
    glthread->right = NULL;
}

void glthread_add_next(glthread_t *curr_glthread, glthread_t *new_glthread) {

    if(!curr_glthread->right){
        curr_glthread->right = new_glthread;
        new_glthread->left = curr_glthread;
        return;
    }

    glthread_t *temp = curr_glthread->right;
    curr_glthread->right = new_glthread;
    new_glthread->left = curr_glthread;
    new_glthread->right = temp;
    temp->left = new_glthread;
}

void glthread_add_before(glthread_t *curr_glthread, glthread_t *new_glthread){

    if(!curr_glthread->left){
        new_glthread->left = NULL;
        new_glthread->right = curr_glthread;
        curr_glthread->left = new_glthread;
        return;
    }

    glthread_t *temp = curr_glthread->left;
    temp->right = new_glthread;
    new_glthread->left = temp;
    new_glthread->right = curr_glthread;
    curr_glthread->left = new_glthread;
}

void remove_glthread(glthread_t *curr_glthread) {

    if(!curr_glthread->left){
        if(curr_glthread->right){
            curr_glthread->right->left = NULL;
            curr_glthread->right = 0;
            return;
        }
        return;
    }
    if(!curr_glthread->right){
        curr_glthread->left->right = NULL;
        curr_glthread->left = NULL;
        return;
    }

    curr_glthread->left->right = curr_glthread->right;
    curr_glthread->right->left = curr_glthread->left;
    curr_glthread->left = 0;
    curr_glthread->right = 0;
}

void delete_glthread_list(glthread_t *glthread_head){

    glthread_t *glthreadptr = NULL;

    ITERATE_GLTHREAD_BEGIN(glthread_head, glthreadptr){
        remove_glthread(glthreadptr);
    } ITERATE_GLTHREAD_END(glthread_head, glthreadptr);
}

void glthread_add_last(glthread_t *glthread_head, glthread_t *new_glthread){

    glthread_t *glthreadptr = NULL,
               *prevglthreadptr = NULL;

    ITERATE_GLTHREAD_BEGIN(glthread_head, glthreadptr){
        prevglthreadptr = glthreadptr;
    } ITERATE_GLTHREAD_END(glthread_head, glthreadptr);

    if(prevglthreadptr)
    {
        glthread_add_next(prevglthreadptr, new_glthread);
    }
    else
    {
        glthread_add_next(glthread_head, new_glthread);
    }
}

unsigned int get_glthread_list_count(glthread_t *glthread_head){

    unsigned int count = 0;
    glthread_t *glthreadptr = NULL;

    ITERATE_GLTHREAD_BEGIN(glthread_head, glthreadptr){
        count++;
    } ITERATE_GLTHREAD_END(glthread_head, glthreadptr);
    return count;
}


void glthread_priority_insert(glthread_t *glthread_head,
                         glthread_t *glthread,
                         int (*comp_fn)(void *, void *),
                         int offset){

    glthread_t *curr = NULL,
               *prev = NULL;

    init_glthread(glthread);

    if(IS_GLTHREAD_LIST_EMPTY(glthread_head)){
        glthread_add_next(glthread_head, glthread);
        return;
    }

    /* Only one node*/
    if(glthread_head->right && !glthread_head->right->right){
        if(comp_fn(GLTHREAD_GET_USER_DATA_FROM_OFFSET(glthread, offset),
            GLTHREAD_GET_USER_DATA_FROM_OFFSET(glthread_head->right, offset)) == -1){
            glthread_add_next(glthread_head, glthread);
        }
        else{
            glthread_add_next(glthread_head->right, glthread);
        }
        return;
    }

    ITERATE_GLTHREAD_BEGIN(glthread_head, curr) {

        if(comp_fn(GLTHREAD_GET_USER_DATA_FROM_OFFSET(glthread, offset),
                GLTHREAD_GET_USER_DATA_FROM_OFFSET(curr, offset)) != -1){
            prev = curr;
            continue;
        }

		if(!prev)
			glthread_add_next(glthread_head, glthread);
		else
			glthread_add_next(prev, glthread);

		return;

    }ITERATE_GLTHREAD_END(glthread_head, curr);

    /*Add in the end*/
    glthread_add_next(prev, glthread);
}

glthread_t * dequeue_glthread_first(glthread_t *base_glthread){

    glthread_t *temp;
    if(!base_glthread->right)
        return NULL;
    temp = base_glthread->right;
    remove_glthread(temp);
    return temp;
}
