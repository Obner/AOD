/*
 * CIS2750 F2017
 * Assignment 0
 * Obner Usi 0912370
 * 
 */

#include "LinkedListAPI.h"

List initializeList(char* (*printFunction)(void *toBePrinted),void (*deleteFunction)(void *toBeDeleted),int (*compareFunction)(const void *first,const void *second)){
	
	if(printFunction == NULL || deleteFunction == NULL || compareFunction == NULL){
		printf("A function pointer is NULL\n");
	}

	List list;

	list.head = NULL;
	list.tail = NULL;

	//Function Pointers
	list.deleteData = deleteFunction;
	list.compare    = compareFunction;
	list.printData  = printFunction;

	return list;
}

Node *initializeNode(void *data){

	if(data == NULL){
		printf("initalizedNode: data is NULL\n");
		return NULL;
	}

	Node* newNode;
	newNode = malloc(sizeof(Node));

	if(newNode == NULL){
		printf("initializeNode: malloc failed\n");
		return NULL;
	}

	newNode->data     = data;
	newNode->previous = NULL;
	newNode->next     = NULL;

	return newNode;
}

void insertFront(List *list, void *toBeAdded){

	Node *insertNode;

	insertNode = initializeNode(toBeAdded);

	if(insertNode == NULL){
		printf("Failed to insertFront\n");
		return;
	}

	//If list is empty
	if(list->head == NULL){
		list->head = insertNode;
		list->tail = insertNode;
	} else {
		insertNode->next = list->head;
		list->head->previous = insertNode;
		list->head = insertNode;
	}
}

void insertBack(List *list, void *toBeAdded){

	Node *insertNode;

	insertNode = initializeNode(toBeAdded);

	if(insertNode == NULL){
		printf("Failed to insertBack\n");
		return;
	}

	//If list is empty
	if(list->tail == NULL){
		list->head = insertNode;
		list->tail = insertNode;
	} else {
		insertNode->previous = list->tail;
		list->tail->next = insertNode;
		list->tail = insertNode;
	}
}

void clearList(List *list){

	Node* curr;

	while(list->head != NULL){
		curr = list->head;

		//Reached end of the list
		if(curr->next != NULL){
			curr->next->previous = NULL;
		}
		
		list->deleteData(curr->data);
		list->head = curr->next;
		free(curr);
	}
}

void insertSorted(List *list, void *toBeAdded){

	Node* insertNode;
	Node* curr;

	curr = list->head;
	insertNode = initializeNode(toBeAdded);

	if(insertNode == NULL){
		printf("Failed to insertSorted\n");
		return;
	}

	//If list is empty
	if(list->head == NULL){
		list->head = insertNode;
		list->tail = insertNode;
		return;
	}

	//Search the list until a node has data greater than the insertNode data 
	while(curr->next != NULL && (list->compare(curr->data, insertNode->data) < 0)){
		curr = curr->next;
	}

	//If the end of the list is reached
	if(curr->next == NULL){
		if(list->compare(curr->data, insertNode->data) < 0){ //insertNode is the new tail
			curr->next = insertNode;
			insertNode->previous = curr;
			list->tail = insertNode;

		} else if (curr->previous == NULL){ //If curr is the only node in the list
			curr->previous = insertNode;
			insertNode->next = curr;
			list->head = insertNode;

		} else { //Insert node behind the tail
			curr->previous->next = insertNode;
			insertNode->previous = curr->previous;
			insertNode->next = curr;
			curr->previous = insertNode;
		}

	 } else if (curr->previous == NULL){ //Insert node to the front
	 	curr->previous = insertNode;
		insertNode->next = curr;
		list->head = insertNode;

	 } else { //Inserting in the middle of the list
	 	curr->previous->next = insertNode;
		insertNode->previous = curr->previous;
		insertNode->next = curr;
		curr->previous = insertNode;
	}
}

void* deleteDataFromList(List *list, void *toBeDeleted){

	Node* curr;

	curr = list->head;

	//Search the list for the same data
	while(curr->next != NULL && !(list->compare(curr->data, toBeDeleted) == 0)){
		curr = curr->next;
	}

	if(curr->next == NULL && list->compare(curr->data, toBeDeleted) == 0){ //Last node matches
		curr->previous->next = NULL;
		list->tail = curr->previous;
		list->deleteData(curr->data);
		free(curr);

	} else if(curr->next == NULL){ //No match
		return NULL;

	} else if(curr == list->head){ //First node matches
		list->head = curr->next;
		curr->next->previous = NULL;
		list->deleteData(curr->data);
		free(curr);

	} else { //Match found in the middle
		curr->previous->next = curr->next;
		curr->next->previous = curr->previous;
		list->deleteData(curr->data);
		free(curr);
	}

	return toBeDeleted;
}

void* getFromFront(List list){

	return list.head->data;
}

void* getFromBack(List list){

	return list.tail->data;
}

char* toString(List list){

	if(list.head == NULL){
		printf("List does not have element\n");
		return NULL;
	}

	Node* curr;
	char* str;
	char* data;
	int len;

	curr = list.head;

	//Constructing the string of the first node data
	data = list.printData(curr->data);
	len  = strlen(data);
	str  = malloc(sizeof(char)*len + 2);
	strcpy(str, data);
	strcat(str, "\n");
	free(data);

	while(curr->next != NULL){
		char *testStr;

		curr = curr->next;

		//Adjusting the size of the string when adding new data
		data = list.printData(curr->data);
		len  = strlen(data + len + 2);
		testStr = (char*)realloc(str, sizeof(char)*len +2);

		if(testStr == NULL){
			printf("Memory allocation in toString failed\n");
			return NULL;

		} else {
			str = testStr;
		}

		//Adding the new data to the string
		strcat(str, data);
		strcat(str, "\n");
		free(data);
	}

	return str;
}

ListIterator createIterator(List list){

	ListIterator it;

	it.current = list.head;

	return it;
}

void* nextElement(ListIterator* iter){

	void* currData;

	//Reached the end of the list
	if(iter->current == NULL){
		return NULL;
	}

	currData      = iter->current->data;
	iter->current = iter->current->next;

	return currData;
}

//Start

/* 
 * Slightly more complex example - list contents are a simple struct
 */
#include <stdio.h>
#include <string.h>
#include "LinkedListAPI.h"

typedef struct name {
	char* firstName;
	char* lastName;
	unsigned int age;
}Name;

//printFunc will return a string that contains a humanly readable copy of the list contents
char* printFunc(void *toBePrinted){
	
	char* tmpStr;
	Name* tmpName;
	int len;
	
	if (toBePrinted == NULL){
		return NULL;
	}
	
	tmpName = (Name*)toBePrinted;
	
	
	/*
	Length of the string is:
	length of the first and last names+3 spaces+4 chars for "Age:"+1 character for '\0'+20 digits to represent the age
	While we only need 3 digits to represent the human age, if the age is uninitialised, it can be any int value
	An int is 8 bytes on 64-bit system, and needs up to 20 chars to represent it
	If we don't do this, our code will crash if age is uninitialized	
	*/
	len = strlen(tmpName->firstName)+strlen(tmpName->lastName)+28;
	tmpStr = (char*)malloc(sizeof(char)*len);
	
	sprintf(tmpStr, "%s %s Age: %d", tmpName->firstName, tmpName->lastName, tmpName->age);
	
	return tmpStr;
}

//We compare names by last name
int compareFunc(const void *first, const void *second){
	
	Name* tmpName1;
	Name* tmpName2;
	
	if (first == NULL || second == NULL){
		return 0;
	}
	
	tmpName1 = (Name*)first;
	tmpName2 = (Name*)second;
	
	return strcmp((char*)tmpName1->lastName, (char*)tmpName2->lastName);
}

//We need to free the first and last names, and then the Name struct itself
void deleteFunc(void *toBeDeleted){
	
	Name* tmpName;
	
	if (toBeDeleted == NULL){
		return;
	}
	
	tmpName = (Name*)toBeDeleted;
	
	free(tmpName->firstName);
	free(tmpName->lastName);
	free(tmpName);
}

int main(void){
	
	Name* tmpName;
	char tmpStr[100];
	int memLen;
	
	/* 
	Create the list.  The list is allocated on the stack, and initializeList returns the list struct.
	*/
	List list = initializeList(&printFunc, &deleteFunc, &compareFunc);
	
	//Populate the list
	for (int i = 0; i < 4; i++){
		tmpName = (Name*)malloc(sizeof(Name));
		tmpName->age = (i+1)*10;
		
		sprintf(tmpStr, "Name%d", i);
		memLen = strlen(tmpStr)+2;
		tmpName->firstName = (char*)malloc(sizeof(char)*memLen);
		strcpy(tmpName->firstName, tmpStr);
		
		sprintf(tmpStr, "Lastname%d", i);
		memLen = strlen(tmpStr)+2;
		tmpName->lastName = (char*)malloc(sizeof(char)*memLen);
		strcpy(tmpName->lastName, tmpStr);
	
		insertSorted(&list, (void*)tmpName);
		printf("%p\n", tmpName);
	}
	

	tmpName = (Name*)malloc(sizeof(Name));
	tmpName->age = 9;
	
	sprintf(tmpStr, "Name%d", 9);
	memLen = strlen(tmpStr)+2;
	tmpName->firstName = (char*)malloc(sizeof(char)*memLen);
	strcpy(tmpName->firstName, tmpStr);
	
	sprintf(tmpStr, "Lastname%d", 9);
	memLen = strlen(tmpStr)+2;
	tmpName->lastName = (char*)malloc(sizeof(char)*memLen);
	strcpy(tmpName->lastName, tmpStr);

	insertSorted(&list, (void*)tmpName);
	printf("%p\n", tmpName);

	tmpName = (Name*)malloc(sizeof(Name));
	tmpName->age = 1;
	
	sprintf(tmpStr, "Name%d", 1);
	memLen = strlen(tmpStr)+2;
	tmpName->firstName = (char*)malloc(sizeof(char)*memLen);
	strcpy(tmpName->firstName, tmpStr);
	
	sprintf(tmpStr, "Lastname%d", 1);
	memLen = strlen(tmpStr)+2;
	tmpName->lastName = (char*)malloc(sizeof(char)*memLen);
	strcpy(tmpName->lastName, tmpStr);

	insertSorted(&list, (void*)tmpName);
	printf("%p\n", tmpName);


	void* elem;

	char* str = toString(list);
	printf("%s\n", str);
	free(str);

	deleteDataFromList(&list, list.head->next->data);
	
	//Create an iterator - again, the iterator is allocated on the stack
	ListIterator iter = createIterator(list);

	/*
	Traverse the list using an iterator.  
	nextElement() returns NULL ones we reach the end of the list
	*/
	while ((elem = nextElement(&iter)) != NULL){
		Name* tmpName = (Name*)elem;
		
		/*
		We use the printData function that we created to return a string representation 
		of the data associated with the current node
		*/
		char* str = list.printData(tmpName);
		printf("%s\n", str);
		
		//Since list.printData dynamically allocates the string, we must free it
		free(str);
	}
	
	printf("\n");
	
	/*
	Crear list contents - free each node, including its contents
	Since the list is created in the stack, we don't need to free it. 
	*/
	clearList(&list);	
	
	return 0;		
}





//end