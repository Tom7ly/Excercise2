//
// Created by shaig on 8/23/2018.
//

#include "sortedList.h"
#include <assert.h>
#include <stdlib.h>

//SortedList definition including functions pointers
struct sortedList_t{
    Node head;
    elemCopyFunc copy;
    elemDestroyFunc destroy;
    elemCompareFunc isBefore;
};


/**create function
 * creates a new empty SortedList data type
 */
SortedList sortedListCreate(elemCopyFunc copy, elemDestroyFunc destroy, elemCompareFunc isBefore){
    //assert that parameters are not NULL
    assert(copy && destroy && isBefore);

    //allocate memory for the new data type, check if successful
    SortedList new_list = malloc(sizeof(*new_list));
    if(!new_list) return NULL;

    //set the 'new_list' properties according to the parameters
    new_list->copy = copy;
    new_list->destroy = destroy;
    new_list->isBefore = isBefore;

    //set the head of 'new_list' to be NULL
    new_list->head = NULL;

    //return the new created SortedList
    return new_list;
}

/**destroy function
 * frees all allocated memory of all the elements in the list,
 * frees the memory allocated to the list itself
 */
void sortedListDestroy(SortedList list){
    //check that 'list' is not NULL, in this case end the function
    if(!list) return;

    //destroy the list elements, if list is not empty
    if(!sortedListIsEmpty(list)){
        nodeDestroyList(list->head, list->destroy);
    }

    //destroy the SortedList struct
    free(list);
}

/**copies a SortedList
 * returns a copy of 'list'
 * if not successful returns NULL (do to memory allocation)
 */
SortedList sortedListCopy(SortedList list){
    //assert that 'list' is not NULL
    assert(list);

    //create a new list with the same functions, and check if successful
    SortedList new_list = sortedListCreate(list->copy, list->destroy, list->isBefore);
    if(!new_list) return NULL;


    //check if 'list' is an empty list, in that case no need to copy
    if(sortedListIsEmpty(list)) return new_list;

    //copy the head of 'list' to 'new_list' head
    assert(list->head); //assert that list is not empty
    new_list->head = nodeCopyList(list->head, list->copy, list->destroy);
    //check success of copy function, if fails free allocated memory and return NULL
    if(!new_list->head){
        free(new_list);
        return NULL;
    }

    //the new list was successfully created, return it
    return new_list;
}

/**checks if a SortedList is empty
 * 'list' is the list being tested
 * returns TRUE if it is empty, FALSE if it is not
 */
bool sortedListIsEmpty(SortedList list){
    //assert that 'list' is not NULL
    assert(list);

    //check if head is NULL. if it is then the list is empty, otherwise it is not
    return (list->head == NULL);
}

/**inserts a new element to the list
 * use the supplied 'isBefore' function to determine the order
 * returns:
 * 'SORTED_LIST_OK' if successful
 * 'SORTED_LIST_MEMORY_ERROR' if a memory error accrued in the process
 */
SortedListResult sortedListInsert(SortedList list, Element element) {
    //asserts that parameters are not NULL
    assert(list && element);

    //copies 'element' to insert in the list
    Node new_node = nodeCreate(element, list->copy);
    //check if successful, if not return memory error flag
    if(!new_node) return SORTED_LIST_MEMORY_ERROR;

    //check if the list is empty, if so put the 'new_node' at the head
    if(sortedListIsEmpty(list)){
        list->head = new_node;
        //function ended successfully
        return SORTED_LIST_OK;
    }

    //check if 'new_node' is before the head, in this case put it in the start
    if(list->isBefore(new_node->element, list->head->element)){
        //set 'new_node' next node to be head, and set the new head to be 'new_node'
        new_node->next = list->head;
        list->head = new_node;
        //function ended successfully
        return SORTED_LIST_OK;
    }

    //iterate through the chain and put 'new_node' in the right place
    //'before' is the node that need to come before 'new_node', 'after' needs to come after 'new_node'
    Node before = list->head;
    Node after = nodeGetNext(list->head);
    while(after && !list->isBefore(element, after->element)){
        //progress 'before' and 'after'
        before = after;
        after = nodeGetNext(after);
    }

    //now 'before' is the node that is ordered before 'new_node', and 'after' after it
    //assert that 'before' is not NULL
    assert(before);
    before->next = new_node;
    new_node->next = after;
    //function ended successfully
    return SORTED_LIST_OK;
}

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
SortedListResult sortedListRemove(SortedList list, Element element, elemCompareFunc compare){
    //assert that parameters are not NULL
    assert(list && element && compare);

    //check if list is empty, if so return 'SORTED_LIST_EMPTY'
    if(sortedListIsEmpty(list)) return SORTED_LIST_EMPTY;

    //check separately the head node
    if(compare(list->head->element, element)){
        //set new head to be head's next, and destroy head
        Node ptr = list->head;
        list->head = nodeGetNext(list->head);
        nodeDestroy(ptr, list->destroy);
        //function ended successfully
        return SORTED_LIST_OK;
    }

    //iterate through the list
    //before is the last element that has been checked, and after is the current one being checked
    Node before = list->head;
    Node after = nodeGetNext(list->head);
    while(after){
        //check if 'after' compares, if so remove and destroy it
        if(compare(after->element, element)){
            //connect 'before' to the node next 'after'
            before->next = nodeGetNext(after);
            //destroy 'after' and end function successfully
            nodeDestroy(after, list->destroy);
            return SORTED_LIST_OK;
        }

        //progress 'before' and 'after'
        before = after;
        after = nodeGetNext(after);
    }

    //if function got here then non of the elements compared to 'element'
    return SORTED_LIST_NOT_FOUND;
}

/**removes and destroys all the elements that are ordered before a given element(according to the given function)
 * 'list' is the Sorted list that the function works on
 * 'element' is an element that signifies where to stop
 * updates 'list' to start from the first element that returns FALSE from 'isBefore(list_element, element)'
 * and destroys all the elements that comes before it
 * returns:
 * 'SORTED_LIST_OK' if successful
 * 'SORTED_LIST_EMPTY' if the list is empty
 */
SortedListResult sortedListRemoveStart(SortedList list, Element element){
    //asserts that parameters are not NULL
    assert(list && element);

    //check if list is empty. if so end the function
    if(sortedListIsEmpty(list)) return SORTED_LIST_EMPTY;

    //check the head node of the list, if it is after it than no element of the list is before 'element'
    //end the function with success
    if(!list->isBefore(list->head->element, element)) return SORTED_LIST_OK;

    //assuming that the list is sorted, find the first node that is ordered after "element"
    //make it the new head, and destroy the start of the list
    //iterate through the nodes, until the last one
    Node current = list->head;
    Node next = nodeGetNext(current);
    while(next){
        //check if the next node is not before 'element'
        if(!list->isBefore(next->element, element)){
            //cut the list after ptr, and destroy it
            current->next = NULL;
            nodeDestroyList(list->head, list->destroy);

            //set the new head to be 'next', and end the function successfully
            list->head = next;
            return SORTED_LIST_OK;
        }

        //progress 'current' and 'next'
        current = next;
        next = nodeGetNext(next);
    }

    //if got to here then all of the list is ordered before 'element'
    //destroy all the list and set head to NULL
    nodeDestroyList(list->head, list->destroy);
    list->head = NULL;

    //end the function successfully
    return SORTED_LIST_OK;
}

/**prints a list according to a specified function, into a file
 * 'file_out' is the file being printed into, assumes it is open for writing
 * 'list' is the list being printed
 * 'print' is a function that prints an Element into a file in the desired fashion
 */
void sortedListPrint(FILE* file_out, SortedList list, elemPrintFunc print){
    //assert that parameters are not NULL
    assert(file_out && list && print);

    //check if list is empty, in that case print nothing
    if(sortedListIsEmpty(list)) return;

    //print all of the nodes with the given function
    nodePrintList(file_out, list->head, print);
}

/**check if there is any element in the list that compares to a specific element
 * 'list' is the list that is being checked
 * 'element' is the other element that is being compared to
 * 'compare' is a function used to compare the list elements with 'element'
 * returns -
 * TRUE if there is such an element
 * FALSE if there is not such an element
 */
bool sortedListFind(SortedList list, Element element, elemCompareFunc compare){
    //assert that parameters are not NULL
    assert(list && element && compare);

    //iterate through all of the nodes of the list
    for(Node ptr = list->head; ptr; ptr = nodeGetNext(ptr)){
        //check if the current element compares with 'element'
        if(compare(ptr->element, element)) return true;
    }

    //if got to here, then non of the elements compares to 'element'
    return false;
}
