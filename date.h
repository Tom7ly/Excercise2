//
// Created by shaig on 8/21/2018.
//
//a date data type definition
//----------------------------------------------------------------------------------------------------------


#ifndef CODE_DATE_H
#define CODE_DATE_H

#include <stdio.h>

//the length of the string of the date
#define DATE_STR_LEN 11

//the definition of date data type:
typedef struct date *Date;

/**Crates a new date data type
 * day - will be the new date day
 * month - will be the new date month
 * year - will be the new date year
 * if successful returns the new created Date
 * if not successful returns NULL
 */
Date dateCreate(int day, int month, int year);

//Destroys and frees the memory of a Date data type
void dateDestroy(Date date);


/** create a copy of a Date data type
 * the new copy will have the same properties of 'date'
 * if not successful returns NULL
 */
Date dateCopy(Date date);

/** converts a string into Date data type
 * date_str is expected to be received in "dd/mm/yyyy" format
 * returns a new Date data type with the values according the string information
 * assert date_str not NULL
 */
Date strToDate(char* date_str);

/** compares 2 Date data types
 * if date1 is chronologically before date2, returns -1
 * if date1 is chronologically after date2, returns 1
 * if date1 equals date2, returns 0
 */


/**chenges 'date_str' to contain the corresponding string of the 'date'
 * assumes that 'date_str' is the start of a char array the size of DATE_STR_LEN
 */
void dateToStr(Date date, char* date_str);

/** compares 2 Date data types
 * if date1 is chronologically before date2, returns -1
 * if date1 is chronologically after date2, returns 1
 * if date1 equals date2, returns 0
 */
int dateCompare(Date date1, Date date2);

/* prints a Date data type as "day/month/year"
 * prints exactly in the format "dd/mm/yyyy" with leading zeros incase it is needed
 * prints it into file_out, assumes it is open for writing
 * */
void datePrint(Date date, FILE* file_out);

#endif //CODE_DATE_H
