#include "LinkedListAPI.h"

List initializeList(char* (*printFunction)(void *toBePrinted),void (*deleteFunction)(void *toBeDeleted),int (*compareFunction)(const void *first,const void *second)){
	
	// if(printFunction == NULL || deleteFunction == NULL || compareFunction == NULL){
	// 	printf("A function pointer is NULL\n");
	// 	return NULL;
	// }

	List* list;
	list = malloc(sizeof(List));

	list->head = NULL;
	list->tail = NULL;

	//Function Pointers
	list->deleteData = deleteFunction;
	list->compare = compareFunction;
	list->printData = printFunction;

	return *list;

}

/*
Node *initializeNode(void *data){

}

void insertFront(List *list, void *toBeAdded){

	if(list == NULL){
		list = toBeAdded;
	} else {
		list->prev = toBeAdded;
		toBeAdded->next = list;
		list = toBeAdded;
	}

}

void insertBack(List *list, void *toBeAdded){

	void* temp;
	temp = list;

	if(list == NULL){
		list = toBeAdded;
	} else {
		while(temp->next != NULL){
			temp = temp->next;
		}
		temp->next = toBeAdded;
		toBeAdded->prev = temp;
	}
}

void clearList(List *list){

	void* temp;

	while(list != NULL){
		temp = list;
		list = temp->next;
		deleteFunc(temp);
	}
}

void insertSorted(List *list, void *toBeAdded){

}

void* deleteDataFromList(List *list, void *toBeDeleted){

}

void* getFromFront(List *list){

	
}

void* getFromBack(List *list){

}

char* toString(List list){

}

ListIterator createIterator(List list){

}

void* nextElement(ListIterator* iter){

}*/
