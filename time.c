//
// Created by shaig on 8/22/2018.
//

#include "time.h"
#include <stdlib.h>
#include <assert.h>
#include "date_time_utils.h"

#define MAX_HOUR 23
#define MAX_MIN 59
#define HOUR_LEN 2
#define MIN_LEN 2

//the definition of time struct
struct time {
    int hour;
    int min;
};


/**creates a new Time data type
 * dynamicly allocates memory for the new data
 * @param hour is the hour value of the new Time
 * @param min is the minute value of the new Time
 * @return the new Time, if not successful returns NULL
 * validity check - 'hour' in range 0 - MAX_HOUR, 'min' in range 0 - MAX_MIN
 */
Time timeCreate(int hour, int min){
    //check parameters validity
    if(hour > MAX_HOUR || hour < 0) return NULL;
    if(min > MAX_MIN || min < 0) return NULL;

    //allocate memory for the new data type, and check success
    Time new_time = malloc(sizeof(*new_time));
    if(!new_time) return NULL;

    //set 'new_time' values and return it
    new_time->hour = hour;
    new_time->min = min;
    return new_time;
}

//destroys and frees the memory allocated to 'time'
void timeDestroy(Time time){
    //asserts that time is not NULL
    assert(time);

    //frees time memory allocation
    free(time);
}

/** create a copy of 'time'
 * if not successful returns NULL
 */
Time timeCopy(Time time){
    //asserts that 'time' is not NULL
    assert(time);

    //creates a new Time data type with the properties of 'time'
    return timeCreate(time->hour, time->min);
}

/**converts a string to Time data type
 * assumes the format 'hh:mm' to be given
 * @param time_str is a pointer to the start of the string that contains the time
 * @return a new Time data type
 */
Time strToTime(char* time_str){
    //asserts that time_str is not NULL
    assert(time_str);

    //take the hour and progress time_str past the ':'
    int hour = strToInt(time_str, HOUR_LEN);
    time_str += HOUR_LEN + 1;

    //take the min for the new time
    int min = strToInt(time_str, MIN_LEN);

    //create a new time data type and return in
    Time new_time = timeCreate(hour, min);
    return new_time;
}

/**converts a Time data type into a string
 * converts it into the format of 'hh:mm'
 * @param time is the Time data type being converted
 * @param time_str is a pointer to a char array, assumed to be in the size of TIME_STR_LEN
 * int 'time_str' the string will be written in
 */
void timeToStr(Time time, char* time_str){
    //asserts that 'time' and 'time_str' are not NULL
    assert(time && time_str);

    //write the hour in the first part
    intToStr(time->hour, HOUR_LEN, time_str);
    //add ':' after and progress pointer
    time_str[HOUR_LEN] = ':';
    time_str += HOUR_LEN + 1;

    //write the minutes in the second part
    intToStr(time->min, MIN_LEN, time_str);
    //add '\0' to end the string
    time_str[MIN_LEN] = '\0';
}

/**comperes 2 Time types according to chronological order
 * if time1 is after time2, returns 1
 * if time1 is before time2, returns -1
 * if time1 and time2 are equal, returns 0
 */
int timeCompare(Time time1, Time time2){
    //asserts that 'time1' and 'time2' are not NULL
    assert(time1 && time2);

    //compare hours
    if(time1->hour < time2->hour) return -1;
    if(time1->hour > time2->hour) return 1;

    //compare minutes
    if(time1->min < time2->min) return -1;
    if(time1->min > time2->min) return 1;

    //if all test passed then they are equal, return 0
    return 0;
}

/**print a Time type in the format of 'hh:mm' into 'file_out'
 * assumes that 'file_out' is open
 */
void timePrint(Time time, FILE* file_out){
    //asserts that 'file_out' and 'time' are not NULL
    assert(time && file_out);

    //create a string to represent the time
    char time_str[TIME_STR_LEN];
    timeToStr(time, time_str);

    //print it into the file
    fprintf(file_out, "%s", time_str);
}
