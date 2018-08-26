//
// Created by shaig on 8/23/2018.

/**This is the interface of a generic sorted list
 * abilitiy to insert a new object only with sorted_insert function
 */

#ifndef SORTED_LIST_H
#define SORTED_LIST_H

#include "node.h"

//SortedList is defined as a pointer to a sortedList_t struct
typedef struct sortedList_t* SortedList;

//functions status return
typedef enum {SORTED_LIST_OK, SORTED_LIST_MEMORY_ERROR, SORTED_LIST_NOT_FOUND, SORTED_LIST_EMPTY} SortedListResult;

/**create function
 * creates a new empty SortedList data type
 */
SortedList sortedListCreate(elemCopyFunc copy, elemDestroyFunc destroy, elemCompareFunc isBefore);

/**destroy function
 * frees all allocated memory of all the elements in the list,
 * frees the memory allocated to the list itself
 */
void sortedListDestroy(SortedList list);

/**copies a SortedList
 * returns a copy of 'list'
 * if not successful returns NULL (do to memory allocation)
 */
SortedList sortedListCopy(SortedList list);

/**checks if a SortedList is empty
 * 'list' is the list being tested
 * returns TRUE if it is empty, FALSE if it is not
 */
bool sortedListIsEmpty(SortedList list);

/**inserts a new element to the list
 * use the supplied 'isBefore' function to determine the order
 * returns:
 * 'SORTED_LIST_OK' if successful
 * 'SORTED_LIST_MEMORY_ERROR' if a memory error accrued in the process
 */
SortedListResult sortedListInsert(SortedList list, Element element);

/**removes the first element in the list that compares with a given element
 * 'list' - the list that is being processed
 * 'element' - the element that the list elements are being compared to
 * 'compare' - the bool function that the comparison is done with
 * removes the first element that returns TRUE
 * returns:
 * 'SORTED_LIST_OK' if successful
 * 'SORTED_LIST_EMPTY' if the given SortedList is empty
 * 'SORTED_LIST_NOT_FOUND' if did not found an element in the list that compares
 */
SortedListResult sortedListRemove(SortedList list, Element element, elemCompareFunc compare);

/**removes and destroys all the elements that are ordered before a given element(according to the given function)
 * 'list' is the Sorted list that the function works on
 * 'element' is an element that signifies where to stop
 * updates 'list' to start from the first element that returns FALSE from 'isBefore(list_element, element)'
 * and destroys all the elements that comes before it
 * returns:
 * 'SORTED_LIST_OK' if successful
 * 'SORTED_LIST_EMPTY' if the list is empty
 */
SortedListResult sortedListRemoveStart(SortedList list, Element element);

/**prints a list according to a specified function, into a file
 * 'file_out' is the file being printed into, assumes it is open for writing
 * 'list' is the list being printed
 * 'print' is a function that prints an Element into a file in the desired fashion
 */
void sortedListPrint(FILE* file_out, SortedList list, elemPrintFunc print);

/**check if there is any element in the list that compares to a specific element
 * 'list' is the list that is being checked
 * 'element' is the other element that is being compared to
 * 'compare' is a function used to compare the list elements with 'element'
 * returns -
 * TRUE if there is such an element
 * FALSE if there is not such an element
 */
bool sortedListFind(SortedList list, Element element, elemCompareFunc compare);


#endif //SORTED_LIST_H
