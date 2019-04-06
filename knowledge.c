/*
 * ICT1002 Assignment 2, 2018-19 Trimester 2.
 *
 * This file implements the chatbot's knowledge base.
 *
 * knowledge_get() retrieves the response to a question.
 * knowledge_put() inserts a new response to a question.
 * knowledge_read() reads the knowledge base from a file.
 * knowledge_reset() erases all of the knowledge.
 * kowledge_write() saves the knowledge base in a file.
 *
 * You may add helper functions as necessary.
 */
 
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "chat1002.h"

/*
 * Get the response to a question.
 *
 * Input:
 *   intent   - the question word
 *   entity   - the entity
 *   response - a buffer to receive the response
 *   n        - the maximum number of characters to write to the response buffer
 *
 * Returns:
 *   KB_OK, if a response was found for the intent and entity (the response is copied to the response buffer)
 *   KB_NOTFOUND, if no response could be found
 *   KB_INVALID, if 'intent' is not a recognised question word
 */
int knowledge_get(const char *intent, const char *entity, char *response, int n) {

    /* ==================================================================================================================================== */
    /* ----------------------------------------------------- If intent=="WHO" ----------------------------------------------------- */
    if (compare_token(intent, "who")==0){
        if (headofWHO!=NULL){                                       /* If a linked-list already exists */
            whoIterator = headofWHO;                                /* Point the whoIterator to head of 'WHO' linked-list */
            do{                                                     /* While no match is found, Make the iterator point to the next node (if last node, it will point to NULL) */
                if (strcmp(whoIterator->entity,entity)==0){         /* If a node with the same entity exists */
                    strncpy(response, whoIterator->response, n);        /* Copy it to the response buffer */
                    return KB_OK;                                   /* After copying to response buffer, return KB_OK (0) */
                }

                whoIterator=whoIterator->next;                      /* If program did not enter the if statement (no entity match), point the iterator to the next node */
            }while(whoIterator);

            /* If code reaches this point, it means that after iterating through all nodes in Linked-list, no match was found */
            /* Hence, return a KB_NOTFOUND code (-1), this makes chatbot_do_question invoke knowledge_put() */
            return KB_NOTFOUND;
        }
        else{                                                       /* Else if linked-list does not exist, return KB_NOTFOUND (-1), this makes chatbot_do_question invoke knowledge_put() */
            return KB_NOTFOUND;
        }
    }
        /* ----------------------------------------------------- ELSE If intent=="WHAT" -----------------------------------------------------*/
    else if (compare_token(intent, "what")==0){
        if (headofWHAT!=NULL){                                      /* If a linked-list already exists */
            whatIterator = headofWHAT;                              /* Point the whatIterator to head of 'WHAT' linked-list */
            do{                                                     /* While no match is found, Make the iterator point to the next node (if last node, it will point to NULL) */
                if (strcmp(whatIterator->entity,entity)==0){        /* If a node with the same entity exists */
                    strncpy(response, whatIterator->response, n);       /* Copy it to the response buffer */
                    return KB_OK;                                   /* After copying to response buffer, return KB_OK (0) */
                }

                whatIterator=whatIterator->next;                    /* If program did not enter the if statement (entity did not match), point the iterator to the next node */
            }while(whatIterator);

            /* If code reaches this point, it means that after iterating through all nodes in Linked-list, no match was found */
            /* Hence, return a KB_NOTFOUND code (-1), this makes chatbot_do_question invoke knowledge_put() */
            return KB_NOTFOUND;
        }
        else{                                                       /* Else if linked-list does not exist, return KB_NOTFOUND (-1), this makes chatbot_do_question invoke knowledge_put() */
            return KB_NOTFOUND;
        }
    }
        /* ----------------------------------------------------- ELSE If intent=="WHERE" ----------------------------------------------------- */
    else if (compare_token(intent, "where")==0){
        if (headofWHERE!=NULL){                                     /* If a linked-list already exists */
            whereIterator = headofWHERE;                            /* Point the whereIterator to head of 'WHERE' linked-list */
            do{                                                     /* While no match is found, Make the iterator point to the next node (if last node, it will point to NULL) */
                if (strcmp(whereIterator->entity,entity)==0){       /* If a node with the same entity exists */
                    strncpy(response, whereIterator->response, n);      /* Copy it to the response buffer */
                    return KB_OK;                                   /* After copying to response buffer, return KB_OK (0) */
                }

                whereIterator=whereIterator->next;                  /* If program did not enter the if statement (entity did not match), point the iterator to the next node */
            }while(whereIterator);

            /* If code reaches this point, it means that after iterating through all nodes in Linked-list, no match was found */
            /* Hence, return a KB_NOTFOUND code (-1), this makes chatbot_do_question invoke knowledge_put() */
            return KB_NOTFOUND;
        }
        else{                                                       /* Else if linked-list does not exist, return KB_NOTFOUND (-1), this makes chatbot_do_question invoke knowledge_put() */
            return KB_NOTFOUND;
        }
    }
        /* -------------------------------- Else if not recognised intent, return KB_INVALID (no such intent) -------------------------------- */
    else {
        return KB_INVALID;
    }
    /* ==================================================================================================================================== */
	
}


/*
 * Insert a new response to a question. If a response already exists for the
 * given intent and entity, it will be overwritten. Otherwise, it will be added
 * to the knowledge base.
 *
 * Input:
 *   intent    - the question word
 *   entity    - the entity
 *   response  - the response for this question and entity
 *
 * Returns:
 *   KB_FOUND, if successful
 *   KB_NOMEM, if there was a memory allocation failure
 *   KB_INVALID, if the intent is not a valid question word
 */
int knowledge_put(const char *intent, const char *entity, const char *response) {

    /* ===================================================================================================================================== */
    char temp_responseBUFFER[MAX_RESPONSE];                                  /* Create a temp buffer for response (needed to call knowledge_get()) */

    int get_code = knowledge_get(intent,entity,temp_responseBUFFER, MAX_RESPONSE);   /* Call knowledge_get() to check if the Intent and Entity pair already exists */
    memset(temp_responseBUFFER,'\0',MAX_RESPONSE);                           /* Clear the temp_response buffer */

    /* Return KB_INVALID if intent is invalid */
    if (abs(get_code)==2){
        return KB_INVALID;
    }

        /* Else, either overwrite or insert the node depending on the return code, and the Intent */
    else{
        /* -------------------------------------------------- Intent == 'WHO' ----------------------------------------------------------------- */
        if (compare_token(intent, "who") == 0){                    /* If intent is 'WHO' */
            //  If Intent and Entity pair already exists, iterate the 'WHO' linked-list & overwrite current response data
            if (abs(get_code)==0){
                whoIterator = headofWHO;                                     /* Point the whoIterator to head of 'WHO' linked-list */
                do{                                                          /* While no match is found, Make the iterator point to the next node (if last node, it will point to NULL) */
                    if (strcmp(whoIterator->entity,entity)==0){              /* If a node with the same Entity exists */
                        strncpy(whoIterator->response, response, MAX_RESPONSE);        /* Overwrite the existing response */
                        printf("\nUpdated Intent: '%s'\nUpdated Entity: '%s'\nUpdated Response: '%s'\n",intent, entity, response);
                        return KB_OK;                                        /* Return code 'KB_OK', which is of value 0 */
                    }

                    whoIterator=whoIterator->next;                           /* If program did not enter the if statement (no entity match), point the iterator to the next node */
                }while(whoIterator);
            }

                //  If no existing record of Intent and Entity exists, create & insert the node to the head of 'WHO' linked-list */
            else if (abs(get_code)==1) {
                response_node *temp = malloc(sizeof(response_node));         /* Create node first */
                if (temp==NULL){                                             /* If not enough memory (memory failure) */
                    return KB_NOMEM;                                         /* Return code 'KB_NOMEM' which is of value -4 */
                }

                strcpy(temp->intent,intent);                                 /* Set node's intent attribute to intent */
                strcpy(temp->entity,entity);                                 /* Set node's entity attribute to entity */
                strcpy(temp->response,response);                             /* Set node's response attribute to response*/
                temp->next = headofWHO;                                      /* Set node to be created to point to where the head of the WHO linked-list is pointing to */
                headofWHO = temp;                                            /* Set 'headofWHO' to point to where temp is */

                /* Testing code */
                printf("\nAdding Intent of headofWHO: '%s'\nAdding Entity of headofWHO: '%s'\nAdding Response of headofWHO: '%s'\n",headofWHO->intent, headofWHO->entity, headofWHO->response);
                return KB_OK;                                                /* Return code 'KB_OK' which is of value 0 */
            }
        }

            /* -------------------------------------------------- Intent == 'WHAT' ----------------------------------------------------------------- */
        else if (compare_token(intent, "what") == 0) {              /* If intent is 'WHAT' */
            //  If Intent and Entity pair already exists, iterate the 'WHAT' linked-list & overwrite current response data
            if (abs(get_code) == 0) {
                whatIterator = headofWHAT;                                    /* Point the whatIterator to head of 'WHAT' linked-list */
                do {                                                          /* While no match is found, Make the iterator point to the next node (if last node, it will point to NULL) */
                    if (strcmp(whatIterator->entity, entity) == 0) {          /* If a node with the same Entity exists */
                        strncpy(whatIterator->response, response, MAX_RESPONSE);        /* Overwrite the existing response */
                        printf("\nUpdated Intent: '%s'\nUpdated Entity: '%s'\nUpdated Response: '%s'\n", intent, entity, response);
                        return KB_OK;                                         /* Return code 'KB_OK', which is of value 0 */
                    }

                    whatIterator = whatIterator->next;                        /* If program did not enter the if statement (no entity match), point the iterator to the next node */
                } while (whatIterator);
            }

                //  If no existing record of Intent and Entity exists, create & insert the node to the head of 'WHAT' linked-list */
            else if (abs(get_code) == 1) {
                response_node *temp = malloc(sizeof(response_node));          /* Create node first */
                if (temp == NULL) {                                           /* If not enough memory (memory failure) */
                    return KB_NOMEM;                                          /* Return code 'KB_NOMEM' which is of value -4 */
                }

                strcpy(temp->intent, intent);                                 /* Set node's intent attribute to intent */
                strcpy(temp->entity, entity);                                 /* Set node's entity attribute to entity */
                strcpy(temp->response, response);                             /* Set node's response attribute to response*/
                temp->next = headofWHAT;                                      /* Set node to be created to point to where the head of the WHAT linked-list is pointing to */
                headofWHAT = temp;                                            /* Set 'headofWHAT' to point to where temp is */

                /* Testing code */
                //printf("\nAdding Intent of headofWHAT: '%s'\nAdding Entity of headofWHAT: '%s'\nAdding Response of headofWHAT: '%s'\n", headofWHAT->intent, headofWHAT->entity, headofWHAT->response);
                return KB_OK;                                                 /* Return code 'KB_OK' which is of value 0 */
            }
        }

            /* ------------------------------------------------- Intent == 'WHERE' ----------------------------------------------------------------- */
        else if (compare_token(intent, "where") == 0) {             /* If intent is 'WHERE' */
            //  If Intent and Entity pair already exists, iterate the 'WHERE' linked-list & overwrite current response data
            if (abs(get_code) == 0) {
                whereIterator = headofWHERE;                                  /* Point the whereIterator to head of 'WHERE' linked-list */
                do {                                                          /* While no match is found, Make the iterator point to the next node (if last node, it will point to NULL) */
                    if (strcmp(whereIterator->entity, entity) ==
                        0) {          /* If a node with the same Entity exists */
                        strncpy(whereIterator->response, response, MAX_RESPONSE);        /* Overwrite the existing response */
                        printf("\nUpdated Intent: '%s'\nUpdated Entity: '%s'\nUpdated Response: '%s'\n", intent, entity, response);
                        return KB_OK;                                         /* Return code 'KB_OK', which is of value 0 */
                    }

                    whereIterator = whereIterator->next;                      /* If program did not enter the if statement (no entity match), point the iterator to the next node */
                } while (whereIterator);
            }

                //  If no existing record of Intent and Entity exists, create & insert the node to the head of 'WHERE' linked-list */
            else if (abs(get_code) == 1) {
                response_node *temp = malloc(sizeof(response_node));          /* Create node first */
                if (temp ==
                    NULL) {                                                   /* If not enough memory (memory failure) */
                    return KB_NOMEM;                                          /* Return code 'KB_NOMEM' which is of value -4 */
                }

                strcpy(temp->intent, intent);                                /* Set node's intent attribute to intent */
                strcpy(temp->entity, entity);                                /* Set node's entity attribute to entity */
                strcpy(temp->response, response);                            /* Set node's response attribute to response*/
                temp->next = headofWHERE;                                     /* Set node to be created to point to where the head of the WHERE linked-list is pointing to */
                headofWHERE = temp;                                           /* Set 'headofWHERE' to point to where temp is */

                /* Testing code */
                printf("\nAdding Intent of headofWHERE: '%s'\nAdding Entity of headofWHERE: '%s'\nAdding Response of headofWHERE: '%s'\n", headofWHERE->intent, headofWHERE->entity, headofWHERE->response);
                return KB_OK;                                                 /* Return code 'KB_OK' which is of value 0 */
            }

        }
        /* ===================================================================================================================================== */
    }
	
}


/*
 * Read a knowledge base from a file.
 *
 * Input:
 *   f - the file
 *
 * Returns: the number of entity/response pairs successful read from the file
 */
int knowledge_read(FILE *f) {
    int linesCount;
    const char ch = '=';

    size_t buffer_size = MAX_INPUT;                              
    char *buffer = malloc(buffer_size * sizeof(char));      // Allocate a Dynamic Buffer for File Line
    while(getline(&buffer, &buffer_size, f) != KB_NOTFOUND)
    {      
        if (strchr(buffer,ch)){                             // Valid Entires have '=', checks how many Valid entries
            linesCount++;
        }
    }
    fflush(stdout);
    free(buffer);                                           // Free Buffer Dyanmic Memory
    fseek(f, 0, SEEK_SET);                                  // Reset File Pointer to Start
    return linesCount;                                      // Return the number of valid entries
}


/*
 * Reset the knowledge base, removing all know entitities from all intents.
 */
void knowledge_reset() {
	
	/* to be implemented */
	
}


/*
 * Write the knowledge base to a file.
 *
 * Input:
 *   f - the file
 */
void knowledge_write(FILE *f) {
	
	/* to be implemented */
	
}