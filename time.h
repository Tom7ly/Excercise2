//
// Created by shaig on 8/22/2018.
//

#ifndef CODE_TIME_H
#define CODE_TIME_H

#include <stdio.h>

//The length of a time string
#define TIME_STR_LEN 6

typedef struct time* Time;

/**creates a new Time data type
 * dynamicly allocates memory for the new data
 * @param hour is the hour value of the new Time
 * @param minute is the minute value of the new Time
 * @return the new Time
 */
Time timeCreate(int hour, int minute);

//destroys and frees the memory allocated to 'time'
void timeDestroy(Time time);

/** create a copy of 'time'
 * if not successful returns NULL
 */
Time timeCopy(Time time);

/**converts a string to Time data type
 * assumes the format 'hh:mm' to be given
 * @param time_str is a pointer to the start of the string that contains the time
 * @return a new Time data type
 */
Time strToTime(char* time_str);

/**converts a Time data type into a string
 * converts it into the format of 'hh:mm'
 * @param time is the Time data type being converted
 * @param time_str is a pointer to a char array, assumed to be in the size of TIME_STR_LEN
 * int 'time_str' the string will be written in
 */
void timeToStr(Time time, char* time_str);

/**comperes 2 Time types according to chronological order
 * if time1 is after time2, returns 1
 * if time1 is before time2, returns -1
 * if time1 and time2 are equal, returns 0
 */
int timeCompare(Time time1, Time time2);

/**print a Time type in the format of 'hh:mm' into 'file_out'
 * assumes that 'file_out' is open
 */
void timePrint(Time time, FILE* file_out);

#endif //CODE_TIME_H
