//
// Created by Michael Wolhandler on 29/11/2020.
//
#include "Person.h"
#include "Constants.h"

struct Person * PersonAlloc(IdT id, char *name, size_t age, int is_sick) {
    Person *person = malloc(sizeof(Person));
    if (person == NULL) {
        return NULL;
    }
    if(name==NULL){
        return NULL;
    }
    char *tmp = malloc(sizeof(char)*(strlen(name)+1));


    if(tmp==NULL){
        free(person);
        return NULL;
    }
    strcpy(tmp,name);
    person->age = age;
    person->id = id;
    person->name = tmp;
    person->is_sick = is_sick;
    person->infection_rate = is_sick;
    person->meetings = NULL;
    person->num_of_meetings = 0;
    person->meetings_capacity = PERSON_INITIAL_SIZE;
    return person;
}

void PersonFree(Person **p_person){
   if(!p_person || !(*p_person))
       return;
   if((*p_person)->name)
       free((*p_person)->name);
   if((*p_person)->meetings!= NULL) {
       free((*p_person)->meetings);
   }
    free(*p_person);
}

Meeting *PersonGetMeetingById(const Person *const person, IdT id){
    int i;
    if(person== NULL){
        return NULL;
    }
    int num_of_mettings = person->num_of_meetings;

    for (i=0;i < num_of_mettings; i++){
        if (person->meetings[i]->person_2->id == id ) {
            return person->meetings[i];
        }
        if (person->meetings[i]->person_1->id == id ) {
                return person->meetings[i];
        }
    }
    return NULL;

}

int PersonCompareById(const Person *person_1, const Person *person_2){
    if (person_1->id == person_2->id) {
        return 0;
    }
    else if (person_1->id > person_2->id) {
        return 1;
    }
    return -1;
}

int PersonCompareByName(const Person *person_1, const Person *person_2) {
    if (strcmp(person_1->name, person_2->name) == 0) {
        return 0;
    }
    if (strcmp(person_1->name, person_2->name) < 0) {
        return -1;
    }
    return 1;
}


int PersonCompareByInfectionRate(const Person *person_1, const Person *person_2){
    if (person_1->infection_rate == person_2->infection_rate ){
        return 0;
    }
    else if (person_1->infection_rate < person_2->infection_rate){
        return 1;
    }
    return -1;
}

int PersonCompareByAge(const Person *person_1, const Person *person_2){
    if (person_1->age == person_2-> age) {
        return 0;
    }
    else if (person_1->age > person_2->age){
        return -1;
    }
    return 1;
}