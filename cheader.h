//
// Created by Javis on 3/21/2019.
//

#ifndef UNTITLED_CHEADER_H
#define UNTITLED_CHEADER_H

/* Include the libraries */
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <setjmp.h>

/* the maximum number of characters we expect in a line of input (including the terminating null)  */
#define MAX_INPUT    256

/* the maximum number of characters allowed in the name of an intent (including the terminating null)  */
#define MAX_INTENT   32

/* the maximum number of characters allowed in the name of an entity (including the terminating null)  */
#define MAX_ENTITY   64

/* the maximum number of characters allowed in a response (including the terminating null) */
#define MAX_RESPONSE 256

/* return codes for knowledge_get() and knowledge_put() */
#define KB_OK        0
#define KB_NOTFOUND -1
#define KB_INVALID  -2
#define KB_NOMEM    -3


/* Defining the structure of the linked-list nodes */
typedef struct response_node{
    char intent[MAX_INTENT];   // Defining attribute 'intent', with max char size of 32 (including the terminating null)
    char entity[MAX_ENTITY];   // Defining attribute 'entity', with max char size of 64 (including the terminating null)
    char response[MAX_RESPONSE]; // Defining attribute 'response', with max char size of 256 (including the terminating null)
    struct response_node *next;
}response_node;

/* Define the three sets of pointers that will point to the head and tail of each of the 3 linked-lists */
response_node *headofWHO, *headofWHAT, *headofWHERE;

/* Define the poitners that will be used to traverse the 3 respective linked-lists */
response_node *whoIterator, *whatIterator, *whereIterator;

#endif //UNTITLED_CHEADER_H
