//
// Created by shaig on 8/23/2018.
//

#include "node.h"
#include <assert.h>
#include <stdlib.h>


//implementation of the linked list in data structure

/**create a new node
 * 'next' property is NULL
 * 'element' will be copied to the node->element
 * returns the new created data type,
 * if not successful returns NULL
 * 'copy' is a pointer to a function that copies the element type
 */
Node nodeCreate(Element element, elemCopyFunc copy){
    //assert that 'element' is not NULL
    assert(element);

    //allocate memory for new Node and check success
    Node new_node = malloc(sizeof(*new_node));
    if(!new_node) return NULL;

    //copy the the element into the new node, and check success
    Element new_element =  copy(element);
    if(!new_element){
        //free memory and return NULL
        free(new_node);
        return NULL;;
    }

    //set 'element' to 'new_element',  and 'next' to NULL
    new_node->element = new_element;
    new_node->next = NULL;

    //return the new created Node
    return new_node;
}

/**destroys a Node
 * 'destroy' is a function used to destroy Element data type
 */
void nodeDestroy(Node node, elemDestroyFunc destroy){
    //assert 'destroy' not NULL
    assert(destroy);

    //check that 'node' is not NULL
    if(!node) return;

    //destroy the node's element
    destroy(node->element);

    //free the node itself
    free(node);
}

//same as nodeDestroy, but for all the linked list
void nodeDestroyList(Node node, elemDestroyFunc destroy){
    //asserts that 'destroy' is not NULL
    assert(destroy);

    //iterate through all of the nodes
    Node ptr = node;
    while(ptr){
        //progress ptr, and destroy the previous Node
        ptr = ptr->next;
        nodeDestroy(node, destroy);
        node = ptr;
    }
}

/**copies a Node
 * 'node' is the Node being copied
 * 'copy' is a function used to copy the element in the Node
 * returns the new copied Node, or NULL if unsuccessful
 * Only copies the 'element' property, sets 'next' to NULL
 */
Node nodeCopy(Node node, elemCopyFunc copy){
    //assert that node is not NULL
    assert(node);

    //build a new node using the create function
    Node new_node = nodeCreate(node->element, copy);

    //return the new created element
    return new_node;
}

//same as nodeCopy, but for the all linked list
//destroy function is necessary
Node nodeCopyList(Node node, elemCopyFunc copy, elemDestroyFunc destroy){
    //assert that parameters are not NULL
    assert(node && copy);

    //make a new node, and set it to the start of the list
    Node new_node = nodeCopy(node, copy);
    //check if copy was successful
    if(!new_node) return NULL;

    //iterate through the list
    Node ptr = new_node;
    node = node->next;

    while(node){
        //copy the next node in the list and set it as the current's 'next'
        ptr->next = nodeCopy(node, copy);
        //check if copy was successful, if not, destroy all the previous created nodes, and return NULL
        if(!ptr->next){
            nodeDestroyList(new_node, destroy);
            return NULL;
        }

        //progress 'ptr' and 'node'
        ptr = ptr->next;
        node = node->next;
    }

    //all the list has been copied, return the head node
    return new_node;
}

//returns the 'next' Node of 'node'
Node nodeGetNext(Node node){
    //assert that 'node' is not NULL
    assert(node);

    //return next
    return node->next;
}

//sets the 'next' node of 'node'
//'next' can be NULL
void nodeSetNext(Node node, Node next){
    //assert that 'node' is not NULL
    assert(node);

    //set next node to be 'next'
    node->next = next;
}

//print the content of one node using a given 'print' function
void nodePrint(FILE* file_out, Node node, elemPrintFunc print){
    //assert that parameters are not NULL
    assert(node && print && file_out);

    //print the node element
    print(file_out, node->element);
}

//print the current node and all the fallowing nodes
void nodePrintList(FILE* file_out, Node node, elemPrintFunc print){
    //assert that parameters are not NULL
    assert(file_out && node && print);

    //iterate through all of the nodes in the list and print them
    for(Node ptr = node; ptr; ptr = ptr->next){
        print(file_out, ptr->element);
    }
}
