//
// Created by Michael Wolhandler on 29/11/2020.
//
#include "Meeting.h"

Meeting *MeetingAlloc(Person *person_1, Person *person_2, double measure, double distance){
    Meeting *meeting = malloc(sizeof(Meeting)*PERSON_INITIAL_SIZE);
    if (!meeting)
        return NULL;
    if(meeting==NULL){
        return NULL;

    }
    meeting->person_1 = person_1;
    meeting->person_2 = person_2;
    meeting->measure = measure;
    meeting->distance = distance;
    return meeting;

}

void MeetingFree(Meeting **p_meeting){
    if (!p_meeting || !(*p_meeting)){
        return;
    }
    free(*p_meeting);
}

Person *MeetingGetPerson(const Meeting * const meeting, size_t person_ind){
    if(meeting==NULL){
        return NULL;
    }
    else if (person_ind == 1){
        return meeting->person_1;
    }
    else if (person_ind == 2){
        return meeting->person_2;
    }
    else
        return NULL;

}
