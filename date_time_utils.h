//
// Created by shaig on 8/21/2018.
//

#ifndef CODE_DATE_TIME_UTILS_H
#define CODE_DATE_TIME_UTILS_H

#define NOT_DIGIT -1

/**converts a single digit into integer
 * if 'digit' is a character between 0 - 9 it returns his numeric value;
 * if not returns -1
 */
int digitToInt(char digit);

/**converts a single digit into integer
 * if 'digit' is a number between 0 - 9 it returns his ascii value;
 * if not returns -1
 */
char digitToChar(int digit);

/**converts an array of digits into a number
 * if in the array there is a character that is not a digit returns -1
 * returns the numeric value of the array of characters representing a number
 * assumes not-negative numbers
 */
int strToInt(char* str, int len);

/**turns a number into a string
 * @param num is the number to be converted into a string
 * @param len is the length of the string, if necessary with leading zeros
 * @param num_str is the pointer to the start of the string the number will be written into
 */
void intToStr(int num, int len, char* num_str);

#endif //CODE_DATE_TIME_UTILS_H
