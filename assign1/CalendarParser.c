/*
 * CIS2750 F2017
 * Assignment 1
 * Obner Usi 0912370
 */

#include <ctype.h>
#include "CalendarParser.h"

void freeFile(FILE* inputFile, char* inputLine);
bool startWith(char* str, char* compare);
ErrorCode parseFile(char* fileName);
ErrorCode parseVersion(char* inputLine, int verFlag);

ErrorCode createCalendar(char* fileName, Calendar** obj){

	FILE* inputFile;
	char* inputLine;
	int strtFlag = 0;
	int verFlag  = 0;
	// int prodFlag = 0;
	// int evtFlag  = 0;
	ErrorCode check;
	Calendar* cal;
	cal = malloc(sizeof(Calendar));

	//Checks to see if the file is invalid
	check = parseFile(fileName);
	if(check != OK){
		deleteCalendar(cal);
		return check;
	}

	inputFile = fopen(fileName, "r");
	inputLine = malloc(sizeof(char)*76);

	while(fgets(inputLine, 76, inputFile) != NULL){

		//printf("%s\n", inputLine);

		if(inputLine[0] != ';'){
			int len = strlen(inputLine);

			//Erase the newline
			if (inputLine[len - 1] == '\n'){
				inputLine[len - 2] = '\0';
			}

			//Update length
			len = strlen(inputLine);

			printf("%s\n", inputLine);


			if(startWith(inputLine, "BEGIN:VCALENDAR")){
				if(strtFlag == 1){ //Repeated BEGIN:VCALENDAR
					deleteCalendar(cal);
					freeFile(inputFile, inputLine);
					return INV_CAL; 
				} else {
					strtFlag = 1;
				}
			}

			if(startWith(inputLine, "VERSION:")){
				if(strtFlag != 1){ //BEGIN:VCALENDAR has not yet been declared
					freeFile(inputFile, inputLine);
					deleteCalendar(cal);
					return INV_CAL;
				}

				check = parseVersion(inputLine, verFlag);

				if(check != OK){
					freeFile(inputFile, inputLine);
					deleteCalendar(cal);
					return check;
				} else {
					verFlag = 1;
					cal->version = 2.0;
				}
				
			}
			/*if (startWith(inputLine, "PRODID:")){
				if(prodFlag != 0){ //BEGIN:VCALENDAR has not been declared or PRODID decalred twice
					freeFile(inputFile, inputLine);
					return INV_CAL;
				} else {
					//Gets the product ID and stores it in obj
					char* prodID = strchr(inputLine,':');
					memmove(prodID, prodID + 1, strlen(prodID));
					strcpy((*obj)->prodID, prodID);
					prodFlag = 1;
				}
			}

			if(strcmp(inputLine, "BEGIN:VEVENT") == 0){
				if((prodFlag != 1) || (verFlag != 1)){ //PRODID and VERSION not declared
					freeFile(inputFile, inputLine);
					return INV_CAL;
				} else {
					evtFlag = 1;
				}
			}

			if(strstr(inputLine, "UID:") != NULL){
				if(evtFlag != 1){ //BEGIN:VEVENT has not been delclared
					freeFile(inputFile, inputLine);
					return INV_CAL;
				} else {
					char* tempEvent = strchr(inputLine, ':');
					memmove(tempEvent, tempEvent + 1, strlen(tempEvent));
					(*obj)->event = malloc(sizeof(Event));
					strcpy((*obj)->event->UID, tempEvent); 
				}
			}*/

			/*if(strstr(inputLine, "DTSTAMP:") != NULL){

				if(len != 24){
					freeFile(inputFile, inputLine);
					return INV_CREATEDT;
				}

				for(int i=8; i<24; i++){

					if(i == 16){
						if(inputLine[16] != 'T'){
							printf("T error\n");
							freeFile(inputFile, inputLine);
							return INV_CREATEDT;
						}
					} else if (i == 23){
						if(inputLine[23] != 'Z'){
							printf("Z error\n");
							freeFile(inputFile, inputLine);
							return INV_CREATEDT;
						}
					} else if(!(isdigit(inputLine[i]))){
						printf("%d\n", i);
						freeFile(inputFile, inputLine);
						return INV_CREATEDT; //check if this is correct
					}
				}*/








				//(*obj)->event->creationDateTime.date;
				//(*obj)->event->creationDateTime.time;
			//}

		}
		inputLine[0] = '\0';
	}

	deleteCalendar(cal);
	freeFile(inputFile, inputLine);
	return OK;
}
void freeFile(FILE* inputFile, char* inputLine){
	fclose(inputFile);
	free(inputLine);
}

bool startWith(char* str, char* compare){
	int endOfCmp = strlen(compare);
	int lenOfStr = strlen(str);

	if(endOfCmp > lenOfStr){
		return false;
	} else if(strncmp(str, compare, endOfCmp) == 0){
		return true;
	}
	return false;
}

bool endsWith(char* str, char* compare){
	if(strcmp(compare, strchr(str, ':')) == 0){
		return true;
	} else {
		return false;
	}
}

ErrorCode parseFile(char* fileName){

	FILE* inputFile = fopen(fileName, "r");
	char* ext = strchr(fileName,'.');
	int fileSize;

	fseek(inputFile, 0, SEEK_END);
	fileSize = ftell(inputFile);

	if(inputFile == NULL){ //File does not exist
		fclose(inputFile);
		return INV_FILE;
	} else if(strcmp(ext, ".ics") != 0){ //.ics is not the extension
		fclose(inputFile);
		return INV_FILE;
	} else if (fileSize == 0){ //File is empty
		fclose(inputFile);
		return INV_FILE;
	}

	fclose(inputFile);
	return OK;
}

ErrorCode parseVersion(char* inputLine, int verFlag){

	if((endsWith(inputLine, ":2.0")) == false){
		return INV_VER;
	} else if (verFlag == 1){
		return DUP_VER;
	} else {
		return OK;
	}
}

void deleteCalendar(Calendar* obj){
	free(obj);
}

/*char* printCalendar(const Calendar* obj){
	printf("%f\n", obj->version);
	printf("%s\n", obj->prodID);
	printf("%s\n", obj->event->UID);
}*/

const char* printError(ErrorCode err){

	char* retStr;

	if(err == INV_FILE){
		retStr = "There was a problem with the file argument - its null, it;’s a empty string, file doesn't exist or cannot be opened, file doesn't have the .ics extension, etc.\n";
	
	} else if (err == INV_CAL){
		retStr = "The calendar itself is invalid (missing required properties or components, invalid opening/closing tags, etc.).\n";
	
	} else if (err == INV_VER){
		retStr = "The calendar version property is present but malformed.\n";
	
	} else if (err == DUP_VER){
		retStr = "The calendar version property appears more than once.\n";
	
	} else if (err == INV_PRODID){
		retStr = "The product ID property is present but malformed.\n";
	
	} else if (err == INV_EVENT){
		retStr = "The event component is malformed in some way.\n";
	
	} else if (err == INV_CREATEDT){
		retStr = "The event creation date-time property is malformed in some way.\n";
	
	} else if (err == OK){
		retStr = "No errors.\n";
	
	} else {
		retStr = "Error code enum not found.\n";
	
	}
	return retStr;
}

int main(){

	char* str;
	str = malloc(sizeof(char)*200);
	Calendar** cal;

	cal = malloc(sizeof(Calendar*));

	strcpy(str, printError(createCalendar("test.ics", cal)));
	printf("%s", str);

	//free((*cal)->event);
	free((cal));
	free(str);
	return 0;
}