//
// Created by Michael Wolhandler on 13/12/2020.
//
#include "HashMap.h"


/**
 * Allocates dynamically new hash map element.
 * @param hash_func a function which "hashes" keys.
 * @param pair_cpy a function which copies pairs.
 * @param pair_cmp a function which compares pairs.
 * @param pair_free a function which frees pairs.
 * @return pointer to dynamically allocated HashMap.
 * @if_fail return NULL.
 */
HashMap *HashMapAlloc(HashFunc hash_func, HashMapPairCpy pair_cpy,HashMapPairCmp pair_cmp, HashMapPairFree pair_free){
    if(hash_func == NULL || pair_cmp == NULL || pair_cpy== NULL || pair_free == NULL)
        return NULL;
    HashMap *hash_map = malloc(sizeof(HashMap));
    if(!hash_map)
        return NULL;
    hash_map->hash_func = hash_func;
    hash_map->pair_cpy = pair_cpy;
    hash_map->pair_cmp = pair_cmp;
    hash_map->pair_free = pair_free;
    hash_map->capacity = HASH_MAP_INITIAL_CAP;
    hash_map->size = 0;
    hash_map->buckets = calloc(1,sizeof(Vector)* hash_map->capacity);
    if (!hash_map->buckets)
        return NULL;
    return hash_map;
}

/**
 * Frees a vector and the elements the vector itself allocated.
 * @param p_hash_map pointer to dynamically allocated pointer to hash_map.
 */
void HashMapFree(HashMap **p_hash_map) {
    if (!p_hash_map || !(*p_hash_map)) {
        return;
    }
    for(size_t i = 0 ;i < (*p_hash_map)->capacity;i++){
        VectorFree(&(*p_hash_map)->buckets[i]);
    }
    free((*p_hash_map)->buckets);
    free((*p_hash_map));
    *p_hash_map = NULL;
}

/**
 * This function returns the load factor of the hash map.
 * @param hash_map a hash map.
 * @return the hash map's load factor, -1 if the function failed.
 */
double HashMapGetLoadFactor(HashMap *hash_map){
    if (!hash_map)
        return -1;
    size_t x =hash_map->size;
    size_t y = hash_map->capacity;
    double res = (double) x/y;
    return res;
}

/**
 * the function create a new hashmap where the function hashes the elements of the given hashmap with the adequate capacity
 * @param hash_map an HashMap
 * @return 1 if the function rehashes successfully and 0 otherwise
 */
int Rehashing(HashMap *hash_map){
    if(!hash_map)
        return 0;
    HashMap *hash_map1 = HashMapAlloc(hash_map->hash_func,hash_map->pair_cpy,hash_map->pair_cmp,hash_map->pair_free);
    if (!hash_map1)
        return 0;

    if (HashMapGetLoadFactor(hash_map) < HASH_MAP_MIN_LOAD_FACTOR) {
        hash_map1->capacity = hash_map->capacity / HASH_MAP_GROWTH_FACTOR;
        hash_map1->buckets = realloc(hash_map1->buckets, hash_map1->capacity * sizeof(Vector*));
        if (!hash_map1->buckets){
            free(hash_map1->buckets);
            return 0;
        }
    }
    if (HashMapGetLoadFactor(hash_map)> HASH_MAP_MAX_LOAD_FACTOR) {
        hash_map1->capacity = hash_map->capacity * HASH_MAP_GROWTH_FACTOR;
        hash_map1->buckets=realloc(hash_map1->buckets,hash_map1->capacity*sizeof(Vector*));
        if (!hash_map1->buckets){
            free(hash_map1->buckets);
            return 0;
        }
    }
    for(size_t j=0; j<hash_map->capacity;j++){
        if (hash_map->buckets[j]){
            for (size_t k =0 ;k<hash_map->buckets[j]->capacity;k++) {
                HashMapInsert(hash_map1, hash_map->buckets[j]->data[k]);
                hash_map->pair_free(&(hash_map->buckets[j]->data[k]));
            }
        }
        VectorFree(&hash_map->buckets[j]);
    }
    free(hash_map->buckets);
    hash_map->buckets = hash_map1->buckets;
    hash_map->capacity= hash_map1->capacity;
    free(hash_map1);
    return 1;
}
/**
 * Inserts a new pair to the hash map.
 * The function inserts *new*, *copied*, *dynamically allocated* pair,
 * NOT the pair it receives as a parameter.
 * @param hash_map the hash map to be inserted with new element.
 * @param pair a pair the hash map would contain.
 * @return returns 1 for successful insertion, 0 otherwise.
 */
int HashMapInsert(HashMap *hash_map, Pair *pair){
    if(!hash_map){
        return 0;
    }
    if (!pair){
        return 0;
    }

    size_t ind = hash_map->hash_func(pair->key) & (hash_map->capacity -1);
    if (!hash_map->buckets[ind]){
        Vector *vector = VectorAlloc(hash_map->pair_cpy,hash_map->pair_cmp, hash_map->pair_free);
        if (!vector) {
            return 0;
        }
        if (VectorPushBack(vector,pair)==1){
            hash_map->buckets[ind] = vector;
            hash_map->size += 1;
        }
        else{
            VectorFree(&vector);
            return 0;
        }

    }
    else{
        for (size_t i =0; i< hash_map->buckets[ind]->size; i++){
            Pair * p_pair = (Pair*) VectorAt(hash_map->buckets[ind],i);
            if(pair->key_cmp(pair->key,p_pair->key)==1){
                VectorErase(hash_map->buckets[ind],i);
                }
            if (VectorPushBack(hash_map->buckets[ind],pair)==1) {
                return 1;
            }
        }

    }
    if ((HashMapGetLoadFactor(hash_map)> HASH_MAP_MAX_LOAD_FACTOR)) {
        if (Rehashing(hash_map) == 1) {
            return 1;
        }
    }
    return 1;
}

/**
 * The function checks if the given key exists in the hash map.
 * @param hash_map a hash map.
 * @param key the key to be checked.
 * @return 1 if the key is in the hash map, 0 otherwise.
 */
int HashMapContainsKey(HashMap *hash_map, KeyT key){
    if(!hash_map || !key)
        return 0;

    for (size_t i = 0; i<hash_map->capacity;i++){
        if (hash_map->buckets[i]){
            for (size_t k = 0 ; k < hash_map->buckets[i]->size;k++){
                Pair * p_pair = (Pair*) hash_map->buckets[i]->data[k];
                if(p_pair->key_cmp(key,p_pair->key)==1){
                    return 1;
                }
            }
        }
    }
    return 0;
}

/**
 * The function checks if the given value exists in the hash map.
 * @param hash_map a hash map.
 * @param value the value to be checked.
 * @return 1 if the value is in the hash map, 0 otherwise.
 */
int HashMapContainsValue(HashMap *hash_map, ValueT value){
    if(!hash_map || !value)
        return 0;

    for (size_t i = 0; i<hash_map->capacity;i++){
        if (hash_map->buckets[i]){
            for (size_t k = 0 ; k < hash_map->buckets[i]->size;k++){
                Pair * p_pair = (Pair*) hash_map->buckets[i]->data[k];
                if(p_pair->value_cmp(value,p_pair->value)==1){
                    return 1;
                }
            }
        }
    }
    return 0;
}

/**
 * The function returns the value associated with the given key.
 * @param hash_map a hash map.
 * @param key the key to be checked.
 * @return the value associated with key if exists, NULL otherwise.
 */
ValueT HashMapAt(HashMap *hash_map, KeyT key) {

    if (!hash_map || !key)
        return NULL;
    if (HashMapContainsKey(hash_map, key) == 0)
        return NULL;
    for (size_t i = 0; i < hash_map->capacity; i++) {
        if (hash_map->buckets[i]) {
            for (size_t k = 0; k < hash_map->buckets[i]->size; k++) {
                Pair *p_pair = (Pair *) hash_map->buckets[i]->data[k];
                if (p_pair->key_cmp(key, p_pair->key) == 1) {
                    return p_pair->value;
                }
            }
        }
    }
    return NULL;
}

/**
 * The function erases the pair associated with key.
 * @param hash_map a hash map.
 * @param key a key of the pair to be erased.
 * @return 1 if the erasing was done successfully, 0 otherwise.
 */
int HashMapErase(HashMap *hash_map, KeyT key){
    if(!hash_map || !key)
        return 0;

    if(HashMapContainsKey(hash_map,key)!=1)
        return 0;
    for(size_t i = 0; i<hash_map->capacity;i++){
        if (hash_map->buckets[i]) {
            for (size_t k=0 ; k < hash_map->buckets[i]->size;k++){
                Pair *p_pair = (Pair *) VectorAt(hash_map->buckets[i],k);
                if (p_pair->key_cmp(key, p_pair->key) == 1) {
                    VectorClear((Vector *) hash_map->buckets[i]->data);
                    hash_map->size -= 1;
                    VectorFree(&hash_map->buckets[i]);
                    break;
                }
            }
        }
    }
    if (HashMapGetLoadFactor(hash_map) < HASH_MAP_MIN_LOAD_FACTOR) {
        if (Rehashing(hash_map)==1)
            return 1;
    }
    return 1;
}

/**
 * This function deletes all the elements in the hash map.
 * @param hash_map a hash map to be cleared.
 */
void HashMapClear(HashMap *hash_map) {
    if (!hash_map)
        return;

    size_t first_capacity = hash_map->capacity;
    for (size_t i = 0; i < first_capacity; ++i) {
        if (hash_map->buckets[i]) {
            VectorClear(hash_map->buckets[i]);
            hash_map->size -= 1;
            VectorFree(&(hash_map->buckets[i]));
            if (HashMapGetLoadFactor(hash_map) < VECTOR_MIN_LOAD_FACTOR)
                hash_map->capacity /= HASH_MAP_GROWTH_FACTOR;
            
        }
    }
}