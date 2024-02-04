//
// Created by Michael Wolhandler on 13/12/2020.
//
#include "Vector.h"

/**
 * Allocates dynamically new vector element.
 * @param elem_copy_func func which copies the element stored in the vector (returns
 * dynamically allocated copy).
 * @param elem_cmp_func func which is used to compare elements stored in the vector.
 * @param elem_free_func func which frees elements stored in the vector.
 * @return pointer to dynamically allocated vector.
 * @if_fail return NULL.
 */
Vector *VectorAlloc(VectorElemCpy elem_copy_func, VectorElemCmp elem_cmp_func, VectorElemFree elem_free_func){
    if (elem_free_func==NULL || elem_copy_func==NULL || elem_cmp_func==NULL){
        return NULL;
    }
    Vector *new_vector =malloc(sizeof(Vector));
    if(!new_vector){
        return NULL;
    }
    new_vector->elem_copy_func= elem_copy_func;
    new_vector->elem_cmp_func=elem_cmp_func;
    new_vector->elem_free_func = elem_free_func;
    new_vector->capacity =VECTOR_INITIAL_CAP;
    new_vector->size = 0;
    new_vector->data = calloc(1,sizeof(void*)* new_vector->capacity);
    if(!new_vector->data){
        free(new_vector);
        return NULL;
    }
    return new_vector;
}

/**
 * Frees a vector and the elements the vector itself allocated.
 * @param p_vector pointer to dynamically allocated pointer to vector.
 */
void VectorFree(Vector **p_vector) {
    if (!p_vector || !(*p_vector)) {
        return;
    }

    for(size_t i = 0 ;i < (*p_vector)->size;i++){
        (*p_vector)->elem_free_func(&((*p_vector)->data[i]));
    }
    free((*p_vector)->data);
    free((*p_vector));
    *p_vector = NULL;
}

/**
 * Returns the element at the given index.
 * @param vector pointer to a vector.
 * @param ind the index of the element we want to get.
 * @return the element the given index if exists (the element itself, not a copy of it)
 * , NULL otherwise.
 */
void *VectorAt(Vector *vector, size_t ind){
    if(!vector){
        return NULL;
    }
    if(ind < vector->size)
        return vector->data[ind];
    return NULL;
}

/**
 * Gets a value and checks if the value is in the vector.
 * @param vector a pointer to vector.
 * @param value the value to look for.
 * @return the index of the given value if it is in the
 * vector ([0, vector_size - 1]).
 * Returns -1 if no such value in the vector.
 */
int VectorFind(Vector *vector, void *value){
    if (vector== NULL || value == NULL)
        return -1;
    for(size_t i=0; i< vector->size;i++){
        if( vector->elem_cmp_func(vector->data[i],value)==1){
            return i;
        }
    }
    return -1;
}

double VectorGetLoadFactor(Vector *vector){
    if (!vector)
        return -1;
    size_t x =vector->size;
    size_t y = vector->capacity;
    double res = (double) x/y;
    return res;

}

/**
 * Adds a new value to the back (index vector_size) of the vector.
 * @param vector a pointer to vector.
 * @param value the value to be added to the vector.
 * @return 1 if the adding has been done successfully, 0 otherwise.
 */
int VectorPushBack(Vector *vector, void *value){
    if (!vector || !value)
        return 0;
    vector->data[vector->size]= vector->elem_copy_func(value);
    vector->size += 1;
    if(VectorGetLoadFactor(vector)> VECTOR_MAX_LOAD_FACTOR) {
        vector->capacity *= VECTOR_GROWTH_FACTOR;
        vector->data = realloc(vector->data, vector->capacity* sizeof(void *));
        if (!vector->data){
            free(vector);
            return 0;
        }
    }
    return 1;
}

/**
 * Removes the element at the given index from the vector.
 * @param vector a pointer to vector.
 * @param ind the index of the element to be removed.
 * @return 1 if the removing has been done successfully, 0 otherwise.
 */
int VectorErase(Vector *vector, size_t ind){
    if (!vector || vector->size <= ind)
        return 0;
    size_t i;
    if (vector->data[ind])
        vector->elem_free_func(&(vector->data[ind]));
    for(i= ind ; i< vector->size-1;i++){
        vector->data[i]= vector->data[i+1];
    }
    vector->size -=1;
    if( VectorGetLoadFactor(vector)< VECTOR_MIN_LOAD_FACTOR) {
        vector->capacity /= VECTOR_GROWTH_FACTOR;
        vector->data = realloc(vector->data, vector->capacity * sizeof(void*));
        if(!vector->data){
            free((vector->data));
            return 0;
        }
    }
    return 1;
}

/**
 * Deletes all the elements in the vector.
 * @param vector vector a pointer to vector.
 */
void VectorClear(Vector *vector) {
    if (!vector)
        return;
    while (vector->size > 0) {
        VectorErase(vector, (vector->size) - 1);
    }

}
