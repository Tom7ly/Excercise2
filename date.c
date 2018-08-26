//
// Created by shaig on 8/21/2018.
//

#include "date.h"
#include <stdlib.h>
#include <assert.h>
#include "date_time_utils.h"

//--------------------------------------------------------------------------------------------------

#define MAX_DAY 31
#define MAX_MONTH 12
#define MAX_YEAR 9999
#define DAY_LEN 2
#define MONTH_LEN 2
#define YEAR_LEN 4

//--------------------------------------------------------------------------------------------------
//definition of Date
struct date {
    int day;
    int month;
    int year;
};




/**Crates a new date data type
 * day - will be the new date day
 * month - will be the new date month
 * year - will be the new date year
 *
 * validity check - day is positive and smaller or equal to MAX_DAY
 *                  month is positive and smaller or equal to MAX_MONTH
 *                  year is not-negative and smaller or equal to MAX_YEAR
 *
 * if successful returns the new created Date
 * if not successful returns NULL
 */
Date dateCreate(int day, int month, int year){
    //check parameters validity
    if(day < 1 || day > MAX_DAY) return NULL;
    if(month < 1 || month > MAX_MONTH) return NULL;
    if(year < 0 || year > MAX_YEAR) return NULL;

    //allocate memory for new Date type
    Date new_date = malloc(sizeof(*new_date));

    //check memory allocation success
    if(new_date == NULL) return NULL;

    //set values
    new_date->day = day;
    new_date->month = month;
    new_date->year = year;

    //return new created date
    return new_date;
}

//Destroys and frees the memory of a Date data type
//asserts date is not NULL
void dateDestroy(Date date){
    //asserts that 'date' is not NULL
    assert(date);

    //frees date allocated memory
    free(date);
}

/** create a copy of a Date data type
 * the new copy will have the same properties of 'date'
 * if not successful returns NULL
 */
Date dateCopy(Date date){
    //asserts that 'date' is not NULL
    assert(date);

    //make a new Date data type with the properties of 'date'
    return dateCreate(date->day, date->month, date->year);
}

/** converts a string into Date data type
 * date_str is expected to be received in "dd/mm/yyyy" format
 * if successful returns new Date data type with the values according the string information
 * if not successful returns NULL(memory allocation failure or date not valid)
 * assert date_str not NULL
 */
Date strToDate(char* date_str){
    //assertion that date_str is not NULL
    assert(date_str);

    //assumes that the date_str is in the right format
    //take day and progress string pointer after the '/'
    int day = strToInt(date_str, DAY_LEN);
    date_str += DAY_LEN + 1;

    //take month and progress string pointer
    int month = strToInt(date_str, MONTH_LEN);
    date_str += MONTH_LEN + 1;

    //take year
    int year = strToInt(date_str, YEAR_LEN);

    //create a new Date data type with day, month, year
    Date new_date = dateCreate(day, month, year);

    //return the new created date, validity checks and memory allocations are done in dateCreate
    return new_date;
}

/**chenges 'date_str' to contain the corresponding string of the 'date'
 * assumes that 'date_str' is the start of a char array the size of DATE_STR_LEN
 */
void dateToStr(Date date, char* date_str){
    //assertion that 'date' and 'date_str' are not NULL
    assert(date && date_str);

    //set first digits to be day and set after '/'
    intToStr(date->day, DAY_LEN, date_str);
    date_str[DAY_LEN] = '/';
    date_str += DAY_LEN + 1;

    //set second the month, and set after '/'
    intToStr(date->month, MONTH_LEN, date_str);
    date_str[MONTH_LEN] = '/';
    date_str += MONTH_LEN + 1;

    //set third the year, and set after '\0'
    intToStr(date->year, YEAR_LEN, date_str);
    date_str[YEAR_LEN] = '\0';
}
/** compares 2 Date data types
 * if date1 is chronologically before date2, returns -1
 * if date1 is chronologically after date2, returns 1
 * if date1 equals date2, returns 0
 */
int dateCompare(Date date1, Date date2){
    //asserts that date1 and date2 are not NULL
    assert(date1 && date2);

    //compare years
    if(date1->year > date2->year) return 1;
    if(date1->year < date2->year) return -1;

    //compare months
    if(date1->month > date2->month) return 1;
    if(date1->month < date2->month) return -1;

    //compare days
    if(date1->day > date2->day) return 1;
    if(date1->day < date2->day) return -1;

    //all tests passed, so the dates are the same, return 0
    return 0;
}


/* prints a Date data type as "day/month/year"
 * prints exactly in the format "dd/mm/yyyy" with leading zeros incase it is needed
 * prints it into file_out, assumes it is open for writing
 * */
void datePrint(Date date, FILE* file_out){
    //asserts that date is not NULL
    assert(date && file_out);

    //set a string for the date
    char date_str[DATE_STR_LEN];

    //use 'dateToStr' function to turn the date into a string
    dateToStr(date, date_str);

    //print the string of the date
    fprintf(file_out, "%s", date_str);
}
