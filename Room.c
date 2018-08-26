//
// Created by shaig on 8/21/2018.
//

#include "Room.h"
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "sortedList.h"
#include "date.h"
//maximum and minimum class number
#define MAX_NUMBER 9999
#define MIN_NUMBER 1

//maximum and minimum student capacity
#define MAX_SIZE 999
#define MIN_SIZE 1


/**Room stracture contains:
 * char* building_name - the name of the building
 * int number - the class number
 * int size - the student capacity in the class
 * bool multi_media - True if contains ,multimedia,  else False
 * void* orders - the list of allocation of the room
 */

//------------------------------------------------------------------------------------------

/*Status codes:
 * ROOM_OK , ROOM_IN_USE , ROOM_MEMORY_ERROR , ROOM_ILLEGAL_PARAMETER , ROOM_NOT_UPDATED ,
 * ROOM_CAN_NOT_ORDER , ROOM_CAN_NOT_REMOVE, ROOM_CAN_NOT_DISPLAY
*/

//------------------------------------------------------------------------------------------

// create a new room with the details of the parameters building_name , number (number of the
// room), size (number of seat places), mm (multi_media).
// the room is created with no orders yet.
// building_name should be copied into the new crated room by duplication.
// building_name must not be NULL. (handled by assert).
// number should be great than 0 with no more than 4 digits.
// size should be great than 0 with no more than 3 digits.
// if cannot create due to any kind of reason (including illegal parameters, not including
// assert case), then NULL is returned. otherwise the new created room is returned.

Room roomCreate(char *building_name, int number, int size, bool mm){
    //assertion that building_name is not NULL
    assert(building_name != NULL);

    //parameters validity check
    //building_name is not empty string
    int name_length = strlen(building_name) + 1;
    if(name_length <= 1) return NULL;
    //number is in the correct range
    if(number < MIN_NUMBER || number > MAX_NUMBER) return NULL;
    //size is in the correct range
    if(size < MIN_SIZE || size > MAX_SIZE) return NULL;

    //allocate memory for the new room, and name string
    Room new_room = malloc(sizeof(*new_room));
    char* new_name = malloc(sizeof(char) * name_length);

    //check memory allocation success
    if(new_room == NULL || new_name == NULL){
        free(new_room);
        free(new_name);
        return NULL;
    }

    //set the new room properties
    strcpy(new_name, building_name);
    new_room->building_name = new_name;
    new_room->number = number;
    new_room->size = size;
    new_room->multi_media = mm;
    new_room->orders = NULL;

    //returns new created room
    return new_room;
}

//------------------------------------------------------------------------------------------

// deallocate all relevant memory of room (including all relevant orders, if any)
// and stop using it.
// room, current_date, current_time must not be NULL. (handled by assert).
// current_date is in the format "dd/mm/yyyy".
// current_time is in the format ""hh/mm" 24 hour time.
// can assume that all parameters are legal (if they are not NULL).
// return value (in this priority order) :
// ROOM_IN_USE - if the room is currently in use it can not be destroyed.
//              remark - if there is an order upon the room, but the room is not
//              right now in use, then no problem to deallocate it.
// ROOM_OK - operation completes successfully.

RoomResult roomDestroy(Room room, char *current_date, char *current_time){
    //assertion that arguments are not NULL
    assert(room != NULL && current_date != NULL && current_time != NULL);

    //###check if the room is currently clear ###(make a function)


    //free the order list ### make a function

    //free the building_name and room struct
    free(room->building_name);
    free(room);

    //return success code
    return ROOM_OK;
}

//------------------------------------------------------------------------------------------

// update the room size and/or mm according to the parameters.
// room must not be NULL. (handled by assert).
// size should be greater or equal to the current size, otherwise update can not be done.
// mm should be true ONLY, otherwise update can not be done.
// return value (in this priority order) :
// ROOM_NOT_UPDATED - as mentioned above.
// ROOM_ILLEGAL_PARAMETER - if size has more than 3 digits. (no update in this case).
// ROOM_OK - operation completes successfully.

RoomResult roomUpdate(Room room, int size, bool mm){
    assert(room!=NULL);
    int currentSize = room->size;
    if(size < currentSize || !mm){
        return ROOM_NOT_UPDATED;
    }
    if(size > MAX_SIZE) {
        return ROOM_ILLEGAL_PARAMETER;
    }
    room->size=currentSize;
    return ROOM_OK;
}

//------------------------------------------------------------------------------------------

// get the name of the building and the number of the given room.
// all parameters not be NULL. (handled by assert).
// building_name and number are output parameters.
// building_name should be copied by duplication. no assumptions concerning its length.
// return value (in this priority order) :
// ROOM_MEMORY_ERROR in case of any memory problem.
// ROOM_OK if operation completes successfully.

RoomResult roomBuildingNum(Room room, char **building_name, int *number){
    assert(room != NULL && building_name != NULL && number != NULL);
    int len = strlen(room->building_name);
    *building_name = malloc(sizeof(char)*(len+1));
    if(!(*building_name)){
        return ROOM_MEMORY_ERROR;
    }
    strcpy(*building_name, room->building_name);
    *number = room->number;
    return ROOM_OK;
}

//------------------------------------------------------------------------------------------

// checks if room1 should appear before room2 in a sorted list, according to the
// criterions we used in  HW1. (num of places -> MM -> number of room ->
// building name).
// returns true or false accordingly.
// Either room1 or room2 must not be NULL. (handled by assert).
// assume here that room1 is not room2.

bool roomBefore(Room room1, Room room2) {
    assert(room1 || room2);

    if (room1->size != room2->size) {
        return (room1->size < room2->size) ? true : false;
    }

    if (room1->multi_media != room2->multi_media) {
        return (room1->multi_media == false) ? true : false;
    }

    if (room1->number != room2->number) {
        return (room1->number < room2->number) ? true : false;
    }

    return ((strcmp(room1->building_name,room2->building_name) < 0) ?
            true : false);
}



//------------------------------------------------------------------------------------------

// check if room is currently in use according to current_date and current_time.
// room, current_date, current_time must not be NULL. (handled by assert).
// current_date is in the format "dd/mm/yyyy".
// current_time is in the format ""hh/mm" 24 hour time.
// can assume that all parameters are legal (if they are not NULL).
// return value : true or false.

bool roomInUse(Room room, char *current_date, char *current_time){
    assert(room && *current_date && *current_time);

}

//------------------------------------------------------------------------------------------

// check if room can be ordered for the required date and start_time/end_time.
// if so, then the room is updated in its order field.
// the field order should keep all approved orders for this room. The orders MUST be kept
// in a chronological sorted manner regarding the date/start_time of the
// order contents, which means - first chronological date/start_time is in the
// beginning of the list, last chronological date/start_time is in the end of the list.
// NONE of the parameters should be NULL. (handled by assert).
// date_order and date are strings containing legal dates in the format "dd/mm/yyyy".
// time_order, start_time, end_time are strings containing legal times in the format
// "hh:mm" (24 hour time).
// can assume that start_time is chronologically before (not equal) end_time.
// return value (in this priority order) :
// ROOM_CAN_NOT_ORDER - if the order can not be fullfilled (not including memory problem).
//                      this includes also the case that the date/hour of the
//                      order request is greater than the date/hour of the order itself
// ROOM_MEMORY_ERROR - memory problem
// ROOM_OK - the operation has been completed successfully.

RoomResult roomOrder(Room room, char *date_order, char *time_order, char *date,
                     char *start_time, char *end_time);

//------------------------------------------------------------------------------------------

// remove an order that has been already approved upon room.
// the order field of room is updated accordingly.
// such a removal is possible if there exists such an order upon the given room that
// starts in the given date/start_time, as well as that the room is not currently in use
// upon this order. (other order do not matter).
// NONE of the parameters should be NULL. (handled by assert).
// current_date and date are strings containing legal dates in the format "dd/mm/yyyy".
// current_time and start_time are strings containing legal times in the format
// "hh:mm" (24 hour time).
// return value (in this priority order) :
// ROOM_CAN_NOT_REMOVE
// ROOM_OK

RoomResult roomRemoveOrder(Room room, char *current_date, char *current_time,
                           char *date, char *start_time);

//------------------------------------------------------------------------------------------

// remove all orders of room that have been already implemented and now
// they are not longer relevant.
// NONE of the parameters should be NULL. (handled by assert).
// current_date is a string containing a legal date in the format "dd/mm/yyyy".
// current_time is a string containing a legal time in the format "hh:mm" (24 hour time).
// return value : the number of orders that have been removed in this operation.

int roomCleanOrders(Room room, char *current_date, char *current_time);

//------------------------------------------------------------------------------------------

// display a room details.
// room and out_file must not be NULL. (handled by assert).
// assuming room is legal (unless it's NULL).
// out_file is the output_file to which the output is written. assuming it's already
// opened for writing in the appropriate place. the operation does not open the file, nor closes it.
// If cannot write the complete output
// to the file, then ROOM_CAN_NOT_DISPLAY is returned, otherwise ROOM_OK is returned.
// the format of the output is as follows :
// first line :
// <building_name>  <room_number>  <number_of_seat_places> <MM (if has a multimedia) or -MM (if does not have)>
// no leading zeros. no spaces in the beginning or end of the line. in the end of line going to
// the beginning of next line. one space only between every 2 successive words in the line.
// for each order of allocation there will be displayed a whole line in the following format :
// <date> <start_time> <end_time>
// date is displayed in the format dd/mm/yyyy
// time is displayed in the format  hh:mm (24 hours)
// no leading zeros. no spaces in the beginning or end of the line. in the end of line going to
// the beginning of next line. one space only between every 2 successive words in the line.
// all lines concerning orders of allocation are displayed in a chronological sorted
// manner regarding the date/start_time of the order contents, which means - the order with
// the first chronological date/start_time is displayed in the upper line,
// and the order with the last chronological date/start_time is displayed in the lower line.
// If no orders at all, then no lines of orders are displayed.
// return value (as already mentioned) :
// ROOM_CAN_NOT_DISPLAY
// ROOM_OK

RoomResult roomDispaly(Room room, FILE *out_file);


//------------------------------------------------------------------------------------------


