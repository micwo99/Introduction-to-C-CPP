//
// Created by Michael Wolhandler on 29/11/2020.
//
//
#include "SpreaderDetector.h"
#define FILE_READ_MODE "r"
#define FILE_WRITE_MODE "w"
/**
 * the function swaps the addresses of two persons
 * @param person_1  a person
 * @param person_2  a person
 */
void Swap(Person *person_1, Person *person_2) {
    Person temp = *person_1;
    *person_1 = *person_2;
    *person_2= temp;
}

SpreaderDetector *SpreaderDetectorAlloc() {
    SpreaderDetector *spreader_detector = calloc(1, sizeof(SpreaderDetector));
    spreader_detector->meeting_cap = SPREADER_DETECTOR_INITIAL_SIZE;
    spreader_detector->people_cap = SPREADER_DETECTOR_INITIAL_SIZE;
    spreader_detector->people = malloc(sizeof(Person) * SPREADER_DETECTOR_INITIAL_SIZE);
    if (spreader_detector->people == NULL) {
        free(spreader_detector);
        return NULL;
    }
    spreader_detector->meetings = malloc(sizeof(Meeting) * SPREADER_DETECTOR_INITIAL_SIZE);
    if (spreader_detector->meetings == NULL) {
        free(spreader_detector->people);
        free(spreader_detector);
        return NULL;
    }
    return spreader_detector;
}

void SpreaderDetectorFree(SpreaderDetector **p_spreader_detector){
    if(!p_spreader_detector || !(*p_spreader_detector))
        return;
    if((*p_spreader_detector)->people){
        free((*p_spreader_detector)->people);
    }
    if((*p_spreader_detector)->meetings) {
        free((*p_spreader_detector)->meetings);
    }
    free(*p_spreader_detector);
}

int SpreaderDetectorAddPerson(SpreaderDetector *spreader_detector, Person *person){
    size_t i;
    if (person==NULL){
        free(person);
        return 0;
    }
    else if(spreader_detector==NULL){
        return 0;
    }

    for (i = 0; i < spreader_detector->people_size; i++) {
        if (PersonCompareById(spreader_detector->people[i], person) == 0) {
            return 0;
        }
    }
    if (spreader_detector->people_cap == spreader_detector->people_size){
        spreader_detector->people_cap =spreader_detector->people_cap * SPREADER_DETECTOR_GROWTH_FACTOR;
        spreader_detector->people=
            realloc(spreader_detector->people, sizeof(Person) *spreader_detector->people_cap);
        if (spreader_detector->people == NULL){
            spreader_detector->people = NULL;
            return 0;
        }
    }

    spreader_detector->people[spreader_detector->people_size] = person;
    spreader_detector->people_size+=1;
    return 1;
}

/**
 * the function add the given meeting to the first person who are in this meeting
 * if meetings of the first person is NULL so the function Allocates (dynamically) for meetings
 * @param spreader_detector where is the person
 * @param meeting given meeting
 * @return if we added successfully the meeting to the person the function returns 1;
 * @if_fails  return 0
 */
int AddMeetingToPerson(SpreaderDetector *spreader_detector, Meeting *meeting){
    for (size_t j = 0; j < spreader_detector->people_size; j++) {
        if (meeting->person_1 == spreader_detector->people[j]) {
            size_t meeting_cap = spreader_detector->people[j]->meetings_capacity;
            size_t num_meetings = spreader_detector->people[j]->num_of_meetings;
            if(spreader_detector->people[j]->meetings==NULL){
                spreader_detector->people[j]->meetings=malloc(sizeof(Meeting)*PERSON_INITIAL_SIZE);
                if (spreader_detector->people[j]->meetings== NULL){
                    return 0;
                }
            }
            else {
                if (num_meetings == meeting_cap) {
                    spreader_detector->people[j]->meetings_capacity =
                        spreader_detector->people[j]->meetings_capacity * PERSON_GROWTH_FACTOR;
                    spreader_detector->people[j]->meetings =
                        realloc(spreader_detector->people[j]->meetings,sizeof(Meeting) * meeting_cap);
                    if (spreader_detector->people[j]->meetings == NULL) {
                        return 0;
                    }
                }
            }
            spreader_detector->people[j]->meetings[spreader_detector->people[j]->num_of_meetings] = meeting;
            spreader_detector->people[j]->num_of_meetings += 1;
        }
    }
    return 1;
}

/**
 * the functions checks if the persons in the meetings are in the array people of the SpreaderDetector given
 * @param spreader_detector  a SpreaderDetector
 * @param meeting  a Meeting
 * @return if the persons of the meeting are in spreader_detector the function returns 1
 * @if_fails  return 0
 */
int CheckPersonsOfTheMeetingInSpr(SpreaderDetector *spreader_detector,Meeting *meeting){
    size_t i;
    int counter = 0;
    for (i = 0; i < spreader_detector->people_size; i++) {
        if (meeting->person_1 == spreader_detector->people[i]
            || meeting->person_2 == spreader_detector->people[i]) {
            counter += 1;
        }
    }
    if(counter==2){
        return 1;
    }
    return 0;
}

int SpreaderDetectorAddMeeting(SpreaderDetector *spreader_detector, Meeting *meeting) {

    if (spreader_detector==NULL)
        return 0;

    if (spreader_detector->meeting_cap == spreader_detector->meeting_size) {
        spreader_detector->meeting_cap = spreader_detector->meeting_cap * SPREADER_DETECTOR_GROWTH_FACTOR;
        size_t meeting_cap =spreader_detector->meeting_cap;
        spreader_detector->meetings = realloc(spreader_detector->meetings,sizeof(Meeting) * meeting_cap);
        if (spreader_detector->meetings == NULL) {
            spreader_detector->meetings = NULL;
            return 0;
        }
    }
    if(CheckPersonsOfTheMeetingInSpr(spreader_detector,meeting)==1){
        spreader_detector->meetings[spreader_detector->meeting_size] = meeting;
        spreader_detector->meeting_size += 1;
        AddMeetingToPerson(spreader_detector, meeting);
        return 1;
    }
    return 0;
}

/**
 * the functions checks if there is a person with the tz given into the array people of spreader_detector
 * @param spreader_detector a SpreaderDetector
 * @param tz a Id
 * @return   returns the person if is in people
 * @if_fails  return NULL
 */
Person *  FoundIdsIntoPeople(SpreaderDetector *spreader_detector, IdT tz){
    size_t i;
    if (spreader_detector==NULL){
        return NULL;
    }
    for(i=0;i<spreader_detector->people_size;i++) {
        if (spreader_detector->people[i]->id == tz) {
            return spreader_detector->people[i];
        }
    }
    return NULL;
}

void SpreaderDetectorReadMeetingsFile(SpreaderDetector *spreader_detector, const char *path) {

    FILE *file;
    file = fopen(path, FILE_READ_MODE);
    size_t tz1 = 0, tz2 = 0;
    double measure = 0, distance = 1;
    char buffer[MAX_LEN_OF_LINE];
    while (fgets(buffer, MAX_LEN_OF_LINE, file) != NULL) {
        sscanf(buffer, "%lu %lu %lf %lf", &tz1, &tz2, &measure, &distance);
        Person *person_1 = FoundIdsIntoPeople(spreader_detector, tz1);
        Person *person_2 = FoundIdsIntoPeople(spreader_detector, tz2);
        if (person_2 != person_1) {
            if (person_1 != NULL && person_2 != NULL && measure < MAX_MEASURE && distance > MIN_DISTANCE) {
                Meeting *meeting = MeetingAlloc(person_1, person_2, measure, distance);
                SpreaderDetectorAddMeeting(spreader_detector, meeting);
            }
        }
    }
    fclose(file);
}

void SpreaderDetectorReadPeopleFile(SpreaderDetector *spreader_detector, const char *path){
    FILE *file;
    file = fopen(path, FILE_READ_MODE);
    IdT tz;
    char name[MAX_LEN_OF_LINE],buffer[MAX_LEN_OF_LINE];
    size_t age;
    int is_sick;
    while (fgets(buffer, MAX_LEN_OF_LINE, file) != NULL){
        char sick[MAX_LEN_OF_LINE]={0};
        sscanf(buffer, "%s %lu %lu %s",name,&tz,&age,sick);
        if (strcmp(sick,"SICK")==0){
            is_sick = 1;
        }
        else{
            is_sick =0;
        }
        if(FoundIdsIntoPeople(spreader_detector,tz)== NULL){
            Person *person = PersonAlloc(tz,name,age,is_sick);
            if(is_sick==1){
                person->infection_rate=1;
                if(spreader_detector!=NULL) {
                    if (spreader_detector->people_size > 1) {
                        Swap(person, spreader_detector->people[0]);
                        SpreaderDetectorAddPerson(spreader_detector, person);
                    }
                }
                if(spreader_detector==NULL){
                    free(person->name);
                    free(person);
                }
                SpreaderDetectorAddPerson(spreader_detector,person);
            }
            else{
                if(spreader_detector==NULL){
                    free(person->name);
                    free(person);
                }
                else
                    SpreaderDetectorAddPerson(spreader_detector,person);
            }
        }
    }
    fclose(file);
}

double SpreaderDetectorGetInfectionRateById(SpreaderDetector *spreader_detector, IdT id)
{
    Person *person = FoundIdsIntoPeople(spreader_detector,id);
    if (!person)
        return -1;
    return person->infection_rate;
}

/**
 * the function calculates the infection rate of a person according to the person he met in the given meeting
 * @param meeting a Meeting where curr_person is into
 * @param curr_person a Person
 */
void  CalculateInfectionChancesOfMeeting(Meeting *meeting, Person *curr_person) {
    double crna = (meeting->measure * MIN_DISTANCE) / (meeting->distance * MAX_MEASURE);
    curr_person->infection_rate = meeting->person_1->infection_rate * crna;
    if (curr_person->age > AGE_THRESHOLD) {
        curr_person->infection_rate += INFECTION_RATE_ADDITION_DUE_TO_AGE;
    }
}

/**
 * the function checks if there is already the given person in the given array of persons
 * @param counter length of the array
 * @param arr array of persons
 * @param person  a Person
 * @return  if there isn't the given person in the arr the function returns 1 otherwise it returns 0
 */
int CheckPersonInArray(int counter,Person **arr,Person * person) {
    int count = 0, k;
    for (k = 0; k < counter; k++) {
        if (person != arr[k]) {
            count++;
        }
    }
    if (count == counter){
        return 1;
    }
    return 0;
}

void SpreaderDetectorCalculateInfectionChances(SpreaderDetector *spreader_detector) {
    size_t i, j;
    size_t  counter=1;
    if(spreader_detector!=NULL) {
        Person **arr = malloc(sizeof(Person *) * spreader_detector->people_size);
        if (spreader_detector->people_size != 0) {
            arr[0] = spreader_detector->people[0];
            if (arr[0]->num_of_meetings != 0) {
                for (i = 0; i <counter; i++) {
                    for (j = 0; j < arr[i]->num_of_meetings; j++) {
                        Person *person2 = arr[i]->meetings[j]->person_1;
                        Person *person1 = arr[i]->meetings[j]->person_2;

                        if (arr[i]->meetings[j]->person_1 == arr[i]) {
                            if (CheckPersonInArray(counter, arr, person1) == 1) {
                                arr[counter] = person1;
                                CalculateInfectionChancesOfMeeting(arr[i]->meetings[j], arr[counter]);
                                counter++;
                            }
                        }
                        if (arr[i]->meetings[j]->person_2 == arr[i]) {
                            if (CheckPersonInArray(counter, arr, person2) == 1) {
                                arr[counter] = person2;
                                CalculateInfectionChancesOfMeeting(arr[i]->meetings[j], arr[counter]);
                                counter++;
                            }
                        }
                    }
                }
            }
        }
        free(arr);
    }
}

int SpreaderDetectorPrintRecommendTreatmentToAll(SpreaderDetector *spreader_detector, const char *file_path){
    FILE *file;
    file = fopen(file_path, FILE_WRITE_MODE);
    if(file == NULL){
        fclose(file);
        return 0;
    }
    if(spreader_detector== NULL){
        fclose(file);
        return 0;
    }
    for(size_t k=0; k < spreader_detector->people_size;k++){
        char *name= spreader_detector->people[k]->name;
        size_t tz = spreader_detector->people[k]->id;
        size_t age =spreader_detector->people[k]->age;
        double infection_rate =spreader_detector->people[k]->infection_rate;

        if(infection_rate > MEDICAL_SUPERVISION_THRESHOLD){
            fprintf(file,MEDICAL_SUPERVISION_THRESHOLD_MSG,name,tz,age,infection_rate);
        }
        else if(infection_rate >= REGULAR_QUARANTINE_THRESHOLD){
            fprintf(file,REGULAR_QUARANTINE_MSG,name,tz,age,infection_rate);
        }
        else{
            fprintf(file,CLEAN_MSG,name,tz,age,infection_rate);
        }
    }
    fclose(file);
    return 1;
}

size_t SpreaderDetectorGetNumOfPeople(SpreaderDetector *spreader_detector){
    if (spreader_detector==NULL){
        return 0;
    }
    return spreader_detector->people_size;

}

size_t SpreaderDetectorGetNumOfMeetings(SpreaderDetector *spreader_detector){
    if (spreader_detector==NULL){
        return 0;
    }
    return spreader_detector->meeting_size;
}


