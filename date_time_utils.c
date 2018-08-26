//
// Created by shaig on 8/21/2018.
//

#include "date_time_utils.h"
#include <assert.h>

/**converts a single digit into integer
 * if 'digit' is a character between 0 - 9 it returns his numeric value;
 * if not returns -1
 */
int digitToInt(char digit){
    //checks if it is a digit
    if(digit < '0' || digit > '9') return NOT_DIGIT;

    //returns the numeric value of digit
    return (digit - '0');
}

/**converts a single digit into integer
 * if 'digit' is a number between 0 - 9 it returns his ascii value;
 * if not returns -1
 */
char digitToChar(int digit){
    //checks if it is a digit
    if(digit < 0 || digit > 9) return NOT_DIGIT;

    //returns the ascii value of digit
    return (char)(digit + '0');
}

/**converts an array of digits into a number
 * if in the array there is a character that is not a digit returns -1
 * returns the numeric value of the array of characters representing a number
 * assumes not-negative numbers
 */
int strToInt(char* str, int len){
    //assertion that str is not NULL
    assert(str);

    //initializing return value
    int num = 0;

    //iterate through the array
    for(int i = 0; i < len; ++i){
        //process the current character and check if it is a digit
        int current_digit = digitToInt(str[i]);
        if(current_digit == NOT_DIGIT) return NOT_DIGIT;

        //move all digits one place to the left and add the new digit
        num *= 10;
        num += current_digit;
    }

    //return the number calculated
    return num;
}

/**turns a number into a string
 * @param num is the number to be converted into a string
 * @param len is the length of the string, if necessary with leading zeros
 * @param num_str is the pointer to the start of the string the number will be written into
 */
void intToStr(int num, int len, char* num_str){
    //asserts that 'num_str' is not NULL
    assert(num_str);

    //iterate through the digits of num, from the LSD, to MSD
    for(int i = len - 1; i >= 0; --i) {
        //take the last digit of 'num', and remove it from 'num'
        int curr_digit = num % 10;
        num /= 10;

        //set the last char of num_str
        num_str[i] = digitToChar(curr_digit);
    }
}
