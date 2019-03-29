/*
 * ICT1002 Assignment 2, 2018-19 Trimester 2.
 *
 * This file implements the behaviour of the chatbot. The main entry point to
 * this module is the chatbot_main() function, which identifies the intent
 * using the chatbot_is_*() functions then invokes the matching chatbot_do_*()
 * function to carry out the intent.
 *
 * chatbot_main() and chatbot_do_*() have the same method signature, which
 * works as described here.
 *
 * Input parameters:
 *   inc      - the number of words in the question
 *   inv      - an array of pointers to each word in the question
 *   response - a buffer to receive the response
 *   n        - the size of the response buffer
 *
 * The first word indicates the intent. If the intent is not recognised, the
 * chatbot should respond with "I do not understand [intent]." or similar, and
 * ignore the rest of the input.
 *
 * If the second word may be a part of speech that makes sense for the intent.
 *    - for WHAT, WHERE and WHO, it may be "is" or "are".
 *    - for SAVE, it may be "as" or "to".
 *    - for LOAD, it may be "from".
 * The word is otherwise ignored and may be omitted.
 *
 * The remainder of the input (including the second word, if it is not one of the
 * above) is the entity.
 *
 * The chatbot's answer should be stored in the output buffer, and be no longer
 * than n characters long (you can use snprintf() to do this). The contents of
 * this buffer will be printed by the main loop.
 *
 * The behaviour of the other functions is described individually in a comment
 * immediately before the function declaration.
 *
 * You can rename the chatbot and the user by changing chatbot_botname() and
 * chatbot_username(), respectively. The main loop will print the strings
 * returned by these functions at the start of each line.
 */
 
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "chat1002.h"

 
/*
 * Get the name of the chatbot.
 *
 * Returns: the name of the chatbot as a null-terminated string
 */
const char *chatbot_botname() {

	return "Chatbot";
	
}


/*
 * Get the name of the user.
 *
 * Returns: the name of the user as a null-terminated string
 */
const char *chatbot_username() {

	return "User";
	
}


/*
 * Get a response to user input.
 *
 * See the comment at the top of the file for a description of how this
 * function is used.
 *
 * Returns:
 *   0, if the chatbot should continue chatting
 *   1, if the chatbot should stop (i.e. it detected the EXIT intent)
 */
int chatbot_main(int inc, char *inv[], char *response, int n) {
	
	/* check for empty input */
	if (inc < 1) {
		snprintf(response, n, "");
		return 0;
	}

	/* look for an intent and invoke the corresponding do_* function */
	if (chatbot_is_exit(inv[0]))
		return chatbot_do_exit(inc, inv, response, n);
	else if (chatbot_is_smalltalk(inv[0]))
		return chatbot_do_smalltalk(inc, inv, response, n);
	else if (chatbot_is_load(inv[0]))
		return chatbot_do_load(inc, inv, response, n);
	else if (chatbot_is_question(inv[0]))
		return chatbot_do_question(inc, inv, response, n);
	else if (chatbot_is_reset(inv[0]))
		return chatbot_do_reset(inc, inv, response, n);
	else if (chatbot_is_save(inv[0]))
		return chatbot_do_save(inc, inv, response, n);
	else {
		snprintf(response, n, "I don't understand \"%s\".", inv[0]);
		return 0;
	}

}


/*
 * Determine whether an intent is EXIT.
 *
 * Input:
 *  intent - the intent
 *
 * Returns:
 *  1, if the intent is "exit" or "quit"
 *  0, otherwise
 */
int chatbot_is_exit(const char *intent) {
	
	return compare_token(intent, "exit") == 0 || compare_token(intent, "quit") == 0;
	
}


/*
 * Perform the EXIT intent.
 *
 * See the comment at the top of the file for a description of how this
 * function is used.
 *
 * Returns:
 *   0 (the chatbot always continues chatting after a question)
 */
int chatbot_do_exit(int inc, char *inv[], char *response, int n) {
	 
	snprintf(response, n, "Goodbye!");
	 
	return 1;
	 
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
	int i = 0;
	char uppercaseintent[MAX_INTENT];

	while(intent[i]) {							// Make Input Intent Uppercase
    	uppercaseintent[i] = toupper(intent[i]);
    	i++;
   	}

	if (strcmp(uppercaseintent, "LOAD")){		// Check if Intent is to LOAD
		return KB_OK;							// Return 0 if Intent is to LOAD
	}
	else {
		return KB_INVALID;						// Return -2 if intent not to LOAD
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
        strcpy(response,"No file inputted!");					// Error Response for No Input for File
    }
    else {
        FILE *file;
        char *splitoutput;
        int noofentries;
        size_t buffer_size = MAX_INTENT;                              
        char *buffer = malloc(buffer_size * sizeof(char));      // Allocate a Dynamic Buffer for File Line
        char intent[MAX_INPUT], entity[MAX_ENTITY], response[MAX_RESPONSE];
        const char ch = '=';

        if (file = fopen(inv[1], "r")){							// Open File for Reading
            strcpy(response,"");								// Reset Response as no ERROR
            noofentries = knowledge_read(file);					// Send to knowledge_read to get Number of lines to parse.
            while(getline(&buffer, &buffer_size, file) != KB_NOTFOUND)
            {   
                if (strstr(buffer, "what")){
                    strcpy(intent, "WHAT");						// Set Intent to WHAT until Next Intent Found
                }
                else if (strstr(buffer, "where")){
                    strcpy(intent, "WHERE");					// Set Intent to WHERE until Next Intent Found
                }
                else if (strstr(buffer, "who")){
                    strcpy(intent, "WHO");						// Set Intent to WHO until Next Intent Found
                }
                if (strchr(buffer,ch)){
                    splitoutput = strtok(buffer, "=");			// Obtain the Entity from line of file
                    strcpy(entity, splitoutput);
                    splitoutput = strtok (NULL, "=");			// Obtain the Response from line of file
                    strcpy(response, splitoutput);

                    knowledge_put(intent, entity, response);	// Send to Knowledge_Put to insert into List
                }
            }
            printf("%d entires inserted into lists\n", noofentries);
            fflush(stdout);										// Flush any unecessary remaining input
            free(buffer);										// Free buffer dynamic memory
            fclose(file);										// Close file pointer
        }
        else{
            strcpy(response,"File not found!");					// Error response for File Not Found
        }
    }
    return KB_OK;
	 
}


/*
 * Determine whether an intent is a question.
 *
 * Input:
 *  intent - the intent
 *
 * Returns:
 *  1, if the intent is "what", "where", or "who"
 *  0, otherwise
 */
int chatbot_is_question(const char *intent) {
	
	/* to be implemented */
	
	return 0;
	
}


/*
 * Answer a question.
 *
 * inv[0] contains the the question word.
 * inv[1] may contain "is" or "are"; if so, it is skipped.
 * The remainder of the words form the entity.
 *
 * See the comment at the top of the file for a description of how this
 * function is used.
 *
 * Returns:
 *   0 (the chatbot always continues chatting after a question)
 */
int chatbot_do_question(int inc, char *inv[], char *response, int n) {
	
	/* to be implemented */
	 
	return 0;
	 
}


/*
 * Determine whether an intent is RESET.
 *
 * Input:
 *  intent - the intent
 *
 * Returns:
 *  1, if the intent is "reset"
 *  0, otherwise
 */
int chatbot_is_reset(const char *intent) {
	
	/* to be implemented */
	
	return 0;
	
}


/*
 * Reset the chatbot.
 *
 * See the comment at the top of the file for a description of how this
 * function is used.
 *
 * Returns:
 *   0 (the chatbot always continues chatting after beign reset)
 */
int chatbot_do_reset(int inc, char *inv[], char *response, int n) {
	
	/* to be implemented */
	 
	return 0;
	 
}


/*
 * Determine whether an intent is SAVE.
 *
 * Input:
 *  intent - the intent
 *
 * Returns:
 *  1, if the intent is "what", "where", or "who"
 *  0, otherwise
 */
int chatbot_is_save(const char *intent) {
	
	/* to be implemented */
	
	return 0;
	
}


/*
 * Save the chatbot's knowledge to a file.
 *
 * See the comment at the top of the file for a description of how this
 * function is used.
 *
 * Returns:
 *   0 (the chatbot always continues chatting after saving knowledge)
 */
int chatbot_do_save(int inc, char *inv[], char *response, int n) {
	
	/* to be implemented */
	
	return 0;
	 
}
 
 
/*
 * Determine which an intent is smalltalk.
 *
 *
 * Input:
 *  intent - the intent
 *
 * Returns:
 *  1, if the intent is the first word of one of the smalltalk phrases
 *  0, otherwise
 */
int chatbot_is_smalltalk(const char *intent)
{

	char lowerIntent[MAX_INTENT];
	int i;
	for (i = 0; i < strlen(intent); i++)
	{
		lowerIntent[i] = tolower(intent[i]);
	}
	lowerIntent[i] = '\0'; // end of lowerIntent

	if (strcmp(lowerIntent, "hi") == 0 ||strcmp(lowerIntent, "hello") == 0 || strcmp(lowerIntent, "hey") == 0 || strcmp(lowerIntent, "howdy") == 0 || strcmp(lowerIntent, "yo") == 0 || strcmp(lowerIntent, "sup") == 0 ||strcmp(lowerIntent, "hiya") == 0)
	{
		return 1;
	}
	return 0;
}

/*
 * Respond to smalltalk.
 *
 * See the comment at the top of the file for a description of how this
 * function is used.
 *
 * Returns:
 *   0, if the chatbot should continue chatting
 *   1, if the chatbot should stop chatting (e.g. the smalltalk was "goodbye" etc.)
 */
int chatbot_do_smalltalk(int inc, char *inv[], char *response, int n)
{

	char intent[MAX_INTENT];
	intent == inv[0];
	int i;
	for (i = 0; i < strlen(intent); i++)
	{
		intent[i] = tolower(intent[i]);
	}
	intent[i] = '\0'; // end of intent

	if (strcmp(intent, "hi") == 0)
	{
		snprintf(response, n, "Hi, Welcome to 1002 Chatbox programmed by Jordan, Xiu Qi, Jun Ming, Dominic and Guang Jun.");
	}
	else if (strcmp(intent, "hello") == 0)
	{
		snprintf(response, n, "Hello, Welcome to 1002 Chatbox programmed by Jordan, Xiu Qi, Jun Ming, Dominic and Guang Jun.");
	}
	else if (strcmp(intent, "hey") == 0)
	{
		snprintf(response, n, "Hey!");
	}
	else if (strcmp(intent, "howdy") == 0)
	{
		snprintf(response, n, "Howdy!");
	}
	else if (strcmp(intent, "yo") == 0)
	{
		snprintf(response, n, "Yo!");
	}
	else if (strcmp(intent, "sup") == 0)
	{
		snprintf(response, n, "Sup!");
	}
	else if (strcmp(intent, "hiya") == 0)
	{
		snprintf(response, n, "Hiya!");
	}

	return 0;
}