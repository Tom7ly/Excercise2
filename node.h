//
// Created by shaig on 8/23/2018.
//

#ifndef CODE_NODE_H
#define CODE_NODE_H

#include <stdbool.h>
#include <stdio.h>

//Element describes a single generic data type
typedef void* Element;

//function used to copy a new element will be called 'elemCopyFunc'
typedef Element (*elemCopyFunc)(Element);

//function used to destroy an element will be called 'elemDestroyFunc'
typedef void (*elemDestroyFunc)(Element);

/**function used to print an element to a file will be called 'elemPrintFunc'
 * assumes that the output file is open for writing
 */
typedef void (*elemPrintFunc)(FILE*, Element);

/**function to compare 2 elements, will be called 'elemCompareFunc'
 * if the comparison is positive, returns True
 * else returns false
 */
typedef bool (*elemCompareFunc)(Element, Element);

//Node is a single element in the linked list
typedef struct node_t{
    Element element;
    struct node_t* next;
} *Node;

/**create a new node
 * 'next' property is NULL
 * 'element' will be copied to the node->element
 * returns the new created data type,
 * if not successful returns NULL
 * 'copy' is a pointer to a function that copies the element type
 */
Node nodeCreate(Element element, elemCopyFunc copy);

/**destroys a Node
 * 'destroy' is a function used to destroy Element data type
 */
void nodeDestroy(Node node, elemDestroyFunc destroy);

//same as nodeDestroy, but for all the linked list
void nodeDestroyList(Node node, elemDestroyFunc destroy);

/**copies a Node
 * 'node' is the Node being copied
 * 'copy' is a function used to copy the element in the Node
 * returns the new copied Node, or NULL if unsuccessful
 * Only copies the 'element' property, sets 'next' to NULL
 */
Node nodeCopy(Node node, elemCopyFunc copy);

//same as nodeCopy, but for the all linked list
//destroy function is necessary
Node nodeCopyList(Node node, elemCopyFunc copy, elemDestroyFunc destroy);

//returns the 'next' Node of 'node'
Node nodeGetNext(Node node);

//sets the 'next' node of 'node'
//'next' can be NULL
void nodeSetNext(Node node, Node next);

//print the content of one node using a given 'print' function
void nodePrint(FILE* file_out, Node node, elemPrintFunc print);

//print the current node and all the fallowing nodes
void nodePrintList(FILE* file_out, Node node, elemPrintFunc print);

#endif //CODE_NODE_H
