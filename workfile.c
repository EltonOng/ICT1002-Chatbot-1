//
// Created by Javis on 3/20/2019.
// Edited by Jordan
//
#include "cheader.h"



/*
 *  Function to get the response to a question if it exists
 *
 *  Input:
 *      Intent   - the question word
 *      Entity   - the entity
 *      response - a buffer to receive the response
 *
 *  Returns:
 *      KB_OK, if a response was found for the intent and entity (the response is copied to the response buffer)
 *      KB_NOTFOUND, if no response could be found
 *      KB_INVALID, if 'intent' is not a recognised question word
 *
 */
int knowledge_get(const char *Intent, const char *Entity, char *response){
    /* ==================================================================================================================================== */
    /* ----------------------------------------------------- If Intent=="WHO" ----------------------------------------------------- */
    if (strcmp(Intent,"WHO")==0){
        if (headofWHO!=NULL){                                       /* If a linked-list already exists */
            whoIterator = headofWHO;                                /* Point the whoIterator to head of 'WHO' linked-list */
            do{                                                     /* While no match is found, Make the iterator point to the next node (if last node, it will point to NULL) */
                if (strcmp(whoIterator->entity,Entity)==0){         /* If a node with the same Entity exists */
                    strncpy(response, whoIterator->response, MAX_RESPONSE);        /* Copy it to the response buffer */
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
    /* ----------------------------------------------------- ELSE If Intent=="WHAT" -----------------------------------------------------*/
    else if (strcmp(Intent,"WHAT")==0){
        if (headofWHAT!=NULL){                                      /* If a linked-list already exists */
            whatIterator = headofWHAT;                              /* Point the whatIterator to head of 'WHAT' linked-list */
            do{                                                     /* While no match is found, Make the iterator point to the next node (if last node, it will point to NULL) */
                if (strcmp(whatIterator->entity,Entity)==0){        /* If a node with the same Entity exists */
                    strncpy(response, whatIterator->response, MAX_RESPONSE);       /* Copy it to the response buffer */
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
    /* ----------------------------------------------------- ELSE If Intent=="WHERE" ----------------------------------------------------- */
    else if (strcmp(Intent,"WHERE")==0){
        if (headofWHERE!=NULL){                                     /* If a linked-list already exists */
            whereIterator = headofWHERE;                            /* Point the whereIterator to head of 'WHERE' linked-list */
            do{                                                     /* While no match is found, Make the iterator point to the next node (if last node, it will point to NULL) */
                if (strcmp(whereIterator->entity,Entity)==0){       /* If a node with the same Entity exists */
                    strncpy(response, whereIterator->response, MAX_RESPONSE);      /* Copy it to the response buffer */
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
    /* -------------------------------- Else if not recognised Intent, return KB_INVALID (no such Intent) -------------------------------- */
    else {
        return KB_INVALID;
    }
    /* ==================================================================================================================================== */
}




/*
 *  Function to add a node into respective linked list
 *
 *  Input:
 *      uIntent     - the question word
 *      uEntity     - the entity
 *      uResponse   - the response for this question and entity
 *
 *  Returns:
 *      KB_OK       - if a node was added successfully
 *      KB_NOMEM    - if there was a memory allocation failure
 *
 */
int knowledge_put(const char *uIntent, const char *uEntity, const char *uResponse){
    /* ===================================================================================================================================== */
    char temp_responseBUFFER[MAX_RESPONSE];                                  /* Create a temp buffer for response (needed to call knowledge_get()) */

    int get_code = knowledge_get(uIntent,uEntity,temp_responseBUFFER);       /* Call knowledge_get() to check if the Intent and Entity pair already exists */
    memset(temp_responseBUFFER,'\0',MAX_RESPONSE);                           /* Clear the temp_response buffer */

    /* Return KB_INVALID if intent is invalid */
    if (abs(get_code)==2){
        return KB_INVALID;
    }

    /* Else, either overwrite or insert the node depending on the return code, and the Intent */
    else{
        /* -------------------------------------------------- Intent == 'WHO' ----------------------------------------------------------------- */
        if (strcmp(uIntent,"WHO") == 0){                    /* If intent is 'WHO' */
            //  If Intent and Entity pair already exists, iterate the 'WHO' linked-list & overwrite current response data
            if (abs(get_code)==0){
                whoIterator = headofWHO;                                     /* Point the whoIterator to head of 'WHO' linked-list */
                do{                                                          /* While no match is found, Make the iterator point to the next node (if last node, it will point to NULL) */
                    if (strcmp(whoIterator->entity,uEntity)==0){             /* If a node with the same Entity exists */
                        strncpy(whoIterator->response, uResponse, MAX_RESPONSE);        /* Overwrite the existing response */
                        printf("\nUpdated Intent: '%s'\nUpdated Entity: '%s'\nUpdated Response: '%s'\n",uIntent, uEntity, uResponse);
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

                strcpy(temp->intent,uIntent);                                /* Set node's intent attribute to uIntent */
                strcpy(temp->entity,uEntity);                                /* Set node's entity attribute to uEntity */
                strcpy(temp->response,uResponse);                            /* Set node's response attribute to uResponse*/
                temp->next = headofWHO;                                      /* Set node to be created to point to where the head of the WHO linked-list is pointing to */
                headofWHO = temp;                                            /* Set 'headofWHO' to point to where temp is */

                /* Testing code */
                printf("\nAdding Intent of headofWHO: '%s'\nAdding Entity of headofWHO: '%s'\nAdding Response of headofWHO: '%s'\n",headofWHO->intent, headofWHO->entity, headofWHO->response);
                return KB_OK;                                                /* Return code 'KB_OK' which is of value 0 */
            }
        }

        /* -------------------------------------------------- Intent == 'WHAT' ----------------------------------------------------------------- */
        else if (strcmp(uIntent,"WHAT") == 0) {              /* If intent is 'WHAT' */
            //  If Intent and Entity pair already exists, iterate the 'WHAT' linked-list & overwrite current response data
            if (abs(get_code) == 0) {
                whatIterator = headofWHAT;                                    /* Point the whatIterator to head of 'WHAT' linked-list */
                do {                                                          /* While no match is found, Make the iterator point to the next node (if last node, it will point to NULL) */
                    if (strcmp(whatIterator->entity, uEntity) == 0) {         /* If a node with the same Entity exists */
                        strncpy(whatIterator->response, uResponse, MAX_RESPONSE);        /* Overwrite the existing response */
                        printf("\nUpdated Intent: '%s'\nUpdated Entity: '%s'\nUpdated Response: '%s'\n", uIntent, uEntity, uResponse);
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

                strcpy(temp->intent, uIntent);                                /* Set node's intent attribute to uIntent */
                strcpy(temp->entity, uEntity);                                /* Set node's entity attribute to uEntity */
                strcpy(temp->response, uResponse);                            /* Set node's response attribute to uResponse*/
                temp->next = headofWHAT;                                      /* Set node to be created to point to where the head of the WHAT linked-list is pointing to */
                headofWHAT = temp;                                            /* Set 'headofWHAT' to point to where temp is */

                /* Testing code */
                printf("\nAdding Intent of headofWHAT: '%s'\nAdding Entity of headofWHAT: '%s'\nAdding Response of headofWHAT: '%s'\n", headofWHAT->intent, headofWHAT->entity, headofWHAT->response);
                return KB_OK;                                                 /* Return code 'KB_OK' which is of value 0 */
            }
        }

        /* ------------------------------------------------- Intent == 'WHERE' ----------------------------------------------------------------- */
        else if (strcmp(uIntent, "WHERE") == 0) {             /* If intent is 'WHERE' */
            //  If Intent and Entity pair already exists, iterate the 'WHERE' linked-list & overwrite current response data
            if (abs(get_code) == 0) {
                whereIterator = headofWHERE;                                  /* Point the whereIterator to head of 'WHERE' linked-list */
                do {                                                          /* While no match is found, Make the iterator point to the next node (if last node, it will point to NULL) */
                    if (strcmp(whereIterator->entity, uEntity) ==
                        0) {          /* If a node with the same Entity exists */
                        strncpy(whereIterator->response, uResponse, MAX_RESPONSE);        /* Overwrite the existing response */
                        printf("\nUpdated Intent: '%s'\nUpdated Entity: '%s'\nUpdated Response: '%s'\n", uIntent, uEntity, uResponse);
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

                strcpy(temp->intent, uIntent);                                /* Set node's intent attribute to uIntent */
                strcpy(temp->entity, uEntity);                                /* Set node's entity attribute to uEntity */
                strcpy(temp->response, uResponse);                            /* Set node's response attribute to uResponse*/
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
 * Determine whether an intent is LOAD.
 *
 * Input:
 *  intent - the intent
 *
 * Returns:
 *  0, if the intent is "load"
 *  -2, otherwise
 */
int chatbot_is_load(const char *intent) {
    // Commented out as Uppercase check done in main
    // int i = 0;
    // char uppercaseintent[MAX_INTENT];

    // while(intent[i]) {                          // Make Input Intent Uppercase
    //     uppercaseintent[i] = toupper(intent[i]);
    //     i++;
    // }

    if (strcmp(intent, "LOAD")){       // Check if Intent is to LOAD
        return KB_OK;                           // Return 0 if Intent is to LOAD
    }
    else {
        return KB_INVALID;                      // Return -2 if intent not to LOAD
    }
}

/*
 * Load a chatbot's knowledge base from a file.
 *
 * See the comment at the top of the file for a description of how this
 * function is used.
 *
 * Returns:
 *   0  (the chatbot always continues chatting after loading knowledge, even if file not found
 */
int chatbot_do_load(int inc, char *inv[], char *response, int n) {
    
    //Debug Statement to Check what is Parsed.
    printf("Inc: %d\nInv: %s\nResponse: %s\nN: %d\n", inc, inv[0], response, n);

    if (inv[1] == NULL){
        strcpy(response,"No file inputted!");                   // Error Response for No Input for File
    }
    else {
        FILE *file;
        char *splitoutput;
        int noofentries;
        size_t buffer_size = MAX_INTENT;                              
        char *buffer = malloc(buffer_size * sizeof(char));      // Allocate a Dynamic Buffer for File Line
        char intent[MAX_INPUT], entity[MAX_ENTITY], response[MAX_RESPONSE];
        const char ch = '=';

        if (file = fopen(inv[1], "r")){                         // Open File for Reading
            strcpy(response,"");                                // Reset Response as no ERROR
            noofentries = knowledge_read(file);                 // Send to knowledge_read to get Number of lines to parse.
            while(getline(&buffer, &buffer_size, file) != KB_NOTFOUND)
            {   
                if (strstr(buffer, "what")){
                    strcpy(intent, "WHAT");                     // Set Intent to WHAT until Next Intent Found
                }
                else if (strstr(buffer, "where")){
                    strcpy(intent, "WHERE");                    // Set Intent to WHERE until Next Intent Found
                }
                else if (strstr(buffer, "who")){
                    strcpy(intent, "WHO");                      // Set Intent to WHO until Next Intent Found
                }
                if (strchr(buffer,ch)){
                    splitoutput = strtok(buffer, "=");          // Obtain the Entity from line of file
                    strcpy(entity, splitoutput);
                    splitoutput = strtok (NULL, "=");           // Obtain the Response from line of file
                    strcpy(response, splitoutput);

                    knowledge_put(intent, entity, response);    // Send to Knowledge_Put to insert into List
                }
            }
            printf("%d entires inserted into lists\n", noofentries);
            fflush(stdout);                                     // Flush any unecessary remaining input
            free(buffer);                                       // Free buffer dynamic memory
            fclose(file);                                       // Close file pointer
        }
        else{
            strcpy(response,"File not found!");                 // Error response for File Not Found
        }
    }
    return KB_OK;
}


/*
 * Reset the knowledge base, removing all know entitities from all intents.
 */
void knowledge_reset() {
    /* ===================================================================================================================================== */
    /* Check all 3 head pointers */
    /* ------------------------------- If 'WHO' linked-list is not empty (headofWHO not pointing to NULL) ---------------------------------- */
    if (headofWHO!=NULL){
        /* While not end of linked-list, delete/free memory of node pointed by headofWHO currently */
        response_node *temp = headofWHO;
        do{
            printf("\nRemoving Node '%s' '%s'",temp->intent,temp->entity);
            temp = temp->next;
            free(headofWHO);                        /* Free memory allocation of node currently pointed to by headofWHO */
            headofWHO=temp;              /* Point headofWHO to the next node (will point to NULL if current node is last in the list) */
        }while(temp != NULL);
    }

    /* ------------------------------ If 'WHAT' linked-list is not empty (headofWHAT not pointing to NULL) --------------------------------- */
    if (headofWHAT!=NULL){
        /* While not end of linked-list, delete/free memory of node pointed by headofWHAT currently */
        response_node *temp = headofWHAT;
        do{
            printf("\nRemoving Node '%s' '%s'",temp->intent,temp->entity);
            temp = temp->next;
            free(headofWHAT);                        /* Free memory allocation of node currently pointed to by headofWHAT */
            headofWHAT=temp;             /* Point headofWHAT to the next node (will point to NULL if current node is last in the list) */
        }while(temp != NULL);
    }

    /* ------------------------------ If 'WHERE' linked-list is not empty (headofWHERE not pointing to NULL) --------------------------------- */
    if (headofWHERE!=NULL){
        /* While not end of linked-list, delete/free memory of node pointed by headofWHERE currently */
        response_node *temp = headofWHERE;
        do{
            printf("\nRemoving Node '%s' '%s'",temp->intent,temp->entity);
            temp = temp->next;
            free(headofWHERE);                       /* Free memory allocation of node currently pointed to by headofWHERE */
            headofWHERE=temp;           /* Point headofWHERE to the next node (will point to NULL if current node is last in the list) */
        }while(temp != NULL);
    }

    printf("\nEnd of knowledge_reset() function...\n");
    /* ===================================================================================================================================== */
}





/*
 * This int main() is only for testing the code purposes, does not need to be added to the main project files
 */
int main(){
    char userintent[MAX_INTENT];                                    /* Define a char array to store user input of size MAX_INTENT */
    char userentity[MAX_ENTITY];                                    /* Define a char array to store user input of size MAX_ENTITY */
    char userresponse[MAX_RESPONSE];                                /* Define a char array to store user input of size MAX_RESPONSE */
    char chatbot_response[MAX_RESPONSE];                            /* Define a char array to store chatbot's response buffer of size MAX_RESPONSE */
    int returncode, put_return_code;

    /* Get userinput loop */
    for(int i=0; i<3; i++){
        /* ---------------------------------------------------------------------------------------------- */
        /* Get user input */
        printf("\nPlease input a intent: ");
        fgets(userintent, MAX_INPUT, stdin);                        /* Store input into userintent */
        strcpy(userintent,strtok(userintent,"\n"));                 /* Remove \n added by fgets */
        fflush(stdin);

        printf("Please input a entity: ");
        fgets(userentity, MAX_INPUT, stdin);                        /* Store input into userentity */
        strcpy(userentity,strtok(userentity,"\n"));                 /* Remove \n added by fgets */
        fflush(stdin);

        printf("Please input a response: ");
        fgets(userresponse, MAX_INPUT, stdin);                      /* Store input into response */
        strcpy(userresponse,strtok(userresponse,"\n"));             /* Remove \n added by fgets */
        fflush(stdin);

        /* ---------------------------------------------------------------------------------------------- */
        int i = 0;

        while(i < strlen(userintent)) {                          // Make Input Intent Uppercase
            if (userintent[i]>=97 &&  userintent[i] <= 122){
                userintent[i] = userintent[i]-32;
            }
            i++;
        }
        printf("%s\n",userintent);
        if (strcmp(userintent, "LOAD") == 0){
            char * inv[MAX_INPUT];
            inv[0] = userintent;
            inv[1] = userentity;
            returncode = chatbot_do_load(2, inv, userresponse, MAX_RESPONSE);
        }
        else {
            /* Call function to insert_node() */
            returncode = knowledge_get(userintent,userentity,chatbot_response); 
        }


        /* Call Function to Process_File() UNCOMMENT THIS AND COMMENT ABOVE IF WANT TO SEE RESULT */
        

        if (returncode==0){                                         /* If a Response (match) was found for inputted Intent and Entity */
            printf("\n----------------------------------------");
            printf("\nResponse Exists: \n%s\n", chatbot_response);  /* Print out the contents in the response buffer */
            printf("\n----------------------------------------");
            memset(chatbot_response,'\0',MAX_RESPONSE);             /* Flush the response buffer */
        }
        else if (abs(returncode)==(1)){                             /* If failed to find a node of matching Intent and Entity */
            printf("\n----------------------------------------");
            printf("\nNo response was found for:\nIntent '%s'\nEntity '%s'\n--- Proceeding to add node ---", userintent, userentity);
            put_return_code = knowledge_put(strtok(userintent,"\n"), strtok(userentity,"\n"), strtok(userresponse,"\n"));
            printf("\nReturned Code: %d",put_return_code);          /* *******************For trouble shooting purposes, remove once done******************* */
            printf("\n----------------------------------------");
        }
        else if (abs(returncode)==(2)){                             /* If invalid Intent was given */
            printf("\n----------------------------------------");
            printf("\nInvalid Intent given: '%s'\nPlease only type either WHO, WHAT, or WHERE!\n", userintent);
            printf("\n----------------------------------------");
        }
        else if (abs(returncode)==(3)){                             /* If failed to create a node due to memory allocation failure */
            printf("\n----------------------------------------");
            printf("\nMemory allocation failure! Failed to create note for:\nIntent '%s'\nEntity '%s'\nResponse '%s'\n",userintent, userentity, userresponse);
            printf("\n----------------------------------------");
        }

    }
    knowledge_reset();                                              /* Call function to release existing nodes created previously (if any) */
}

