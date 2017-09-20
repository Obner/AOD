/*
 * CIS2750 F2017
 * Assignment 1
 * Obner Usi 0912370
 */

#include "CalendarParser.h"

ErrorCode createCalendar(char* fileName, Calendar** obj){

	FILE* inputFile;
	char* inputLine;

	inputFile = fopen(fileName, "r");

	//Checks to see if the file is invalid
	if(inputFile == NULL){
		fclose(inputFile);
		return INV_FILE;

	} else {
		//Checks to see if the file is empty
		if(fseek(inputFile, 0, SEEK_END) == 0){
			fclose(inputFile);
			return INV_FILE;
		}
	}

	//size undetermined
	inputLine = malloc(sizeof(char)*76);

	while(fgets(inputLine, 76, inputFile) != NULL){
		
		if(!inputLine[0] == ';'){

			if(strstr(inputLine, "VERSION:")){

				if(strstr(inputLine, "VERSION:2.0") == NULL){
					return INV_VER;
				}
			}
		}
	}


	free(inputLine);
	fclose(inputFile);
	return OK;
}

// void deleteCalendar(Calendar* obj){}

// char* printCalendar(const Calendar* obj){}

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

	strcpy(str, printError(OK));
	printf("%s", str);

	free(str);
	return 0;
}

