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

int main(){
	printf("Hello World");
	return 0;
}


Node *initializeNode(void *data){
	Node* newNode;

	newNode = malloc(sizeof(Node));

	newNode->data = data;
	newNode->previous = NULL;
	newNode->next = NULL;

	return newNode;
}

void insertFront(List *list, void *toBeAdded){

	Node *insertNode;

	insertNode = initializeNode(toBeAdded);

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

	if(list->tail == NULL){
		list->head = insertNode;
		list->tail = insertNode;
	} else {
		insertNode->previous = list->tail;
		list->tail->next = insertNode;
		list->tail = insertNodel;
	}
}

void clearList(List *list){

	while(list->head != NULL){
		Node* temp;
		temp = list->head;
		list->deleteData(list->head->data);
		list->head->next->previous = NULL;
		list->head = list->head->next;

		free(temp);
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
*/
ListIterator createIterator(List list){
	ListIterator* it;
	it = malloc(sizeof(ListIterator));

	it->current = list.head;

	return *it;
}

void* nextElement(ListIterator* iter){
	void* temp;
	temp = iter->current->data;

	iter->current = iter->current->next;

	return temp;
}
