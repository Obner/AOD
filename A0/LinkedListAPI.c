/*
 Obner Usi
 ousi@uoguelph.ca
 0912370
 Assignment 0
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
	int len;

	curr = list.head;

	//Constructing the string of the first node data
	len  = strlen(list.printData(curr->data));
	str  = malloc(sizeof(char)*len + 2);
	strcpy(str, list.printData(curr->data));
	strcat(str, "\n");

	while(curr->next != NULL){
		char *testStr;

		curr = curr->next;

		//Adjusting the size of the string when adding new data
		len  = strlen(list.printData(curr->data)) + len + 2;
		testStr = (char*)realloc(str, sizeof(char)*len);

		if(testStr == NULL){
			printf("Memory allocation in toString failed\n");
			return NULL;

		} else {
			str = testStr;
		}

		//Adding the new data to the string
		strcat(str, list.printData(curr->data));
		strcat(str, "\n");
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
