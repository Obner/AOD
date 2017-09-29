/*
 * CIS2750 F2017
 * Assignment 0
 * Obner Usi 0912370
 * This file contains a LinkedListAPI that coresponds with
   LinkedListAPI.h. It implements functions for a doubly linked
   list and follows the struct specified in LinkedList.h
 * This file does not contain any reused code. In data structures
   I implemented a singly linked list. I referred to lecture notes
   in both CIS2520 and CIS2750
 * My current CIS2750 professor is, Denis Nikitenko
 */

#include "LinkedListAPI.h"

List initializeList(char* (*printFunction)(void *toBePrinted),void (*deleteFunction)(void *toBeDeleted),int (*compareFunction)(const void *first,const void *second)){

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

	//Check for NULL list
	if(data == NULL){
		return NULL;
	}

	Node* newNode;
	newNode = malloc(sizeof(Node));

	//If malloc fails
	if(newNode == NULL){
		return NULL;
	}

	newNode->data     = data;
	newNode->previous = NULL;
	newNode->next     = NULL;

	return newNode;
}

void insertFront(List *list, void *toBeAdded){

	//Checks for NULL list
	if(list == NULL){
		return;
	}

	Node *insertNode;
	insertNode = initializeNode(toBeAdded);

	//If initilizeNode sends a fail node
	if(insertNode == NULL){
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

	//If list is NULL
	if(list == NULL){
		return;
	}

	Node *insertNode;
	insertNode = initializeNode(toBeAdded);

	//If initilizeNode sends a failed node
	if(insertNode == NULL){
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

	//If the list or delete function is NULL 
	if(list == NULL || list->deleteData == NULL){
		return;
	}

	Node* curr;

	while(list->head != NULL){
		curr = list->head;
		list->head = curr->next;

		if(curr->next != NULL){
			curr->next->previous = NULL;	
		}
		
		list->deleteData(curr->data);
		free(curr);
	}
	list->tail = NULL;
}

void insertSorted(List *list, void *toBeAdded){

	//If the list or compare funtion is NULL
	if(list == NULL || list->compare == NULL){
		return;
	}

	Node* insertNode;
	Node* curr;

	curr = list->head;
	insertNode = initializeNode(toBeAdded);

	//If initializeNode returns a NULL node
	if(insertNode == NULL){
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

	if(list == NULL || toBeDeleted == NULL || list->compare == NULL || list->deleteData == NULL){
		return NULL;
	}

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

	if(list.head == NULL){
		return NULL;
	}

	return list.head->data;
}

void* getFromBack(List list){

	if(list.tail == NULL){
		return NULL;
	}

	return list.tail->data;
}

char* toString(List list){

	if(list.head == NULL || list.printData == NULL){
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

	//If malloc fails
	if(str == NULL){
		return NULL;
	}

	//The first string
	strcpy(str, data);
	strcat(str, "\n");
	free(data);

	while(curr->next != NULL){
		char *testStr;

		curr = curr->next;

		//Adjusting the size of the string when adding new data
		data = list.printData(curr->data);
		len  = strlen(data) + len + 2;
		testStr = (char*)realloc(str, sizeof(char)*len +2);

		//If realloc fails
		if(testStr == NULL){
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
	if(iter == NULL || iter->current == NULL){
		return NULL;
	}

	currData      = iter->current->data;
	iter->current = iter->current->next;

	return currData;
}