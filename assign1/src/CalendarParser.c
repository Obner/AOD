/*
 * CIS2750 F2017
 * Assignment 1
 * Obner Usi 0912370
 */

#include <ctype.h>
#include <strings.h>
#include "CalendarParser.h"
#include "LinkedListAPI.h"

char* propPrintFunc(void *toBePrinted);
int propCompareFunc(const void *first, const void *second);
void propDeleteFunc(void *toBeDeleted);
char* alarmPrintFunc(void *toBePrinted);


int alarmCompareFunc(const void *first, const void *second);

/*
 * The delete function for the alarm list
 * @param void* toBeDeleted: the data to be deleted
 * @post the data on the alarm list is freed
 */
void alarmDeleteFunc(void *toBeDeleted);

/*
 * Function to check if the flags were malloced correctly (no NULL flags)
 * @param int* evtNum:     Flag for the number of events
 		  int* strtFlag:   Flag for the BEGIN:VCALENDAR property
 *        int* verFlag:    Flag for ther VERSION property
 *        int* prodFlag:   Flag for the product ID property
 *        int* evtFlag:    Flag for the VEVENT property
 *        int* UIDFlag:    Flag for the UID property
 *        int* clasFlag:   Flag for the CLASS property
 *        int* createdFlag:Flag for the CREATED property
 *        int* decrFlag:   Flag for the DESCRIPTION property
 *        int* dtStrFlag:  Flag for the DTSTART property
 *        int* geoFlag:    Flag for the GEO property
 *        int* lstModFlag: Flag for the LAST-MOD property
 *        int* locFlag:    Flag for the LOCATION property
 *        int* orgFlag:    Flag for the ORGANIZER property
 *        int* prioFlag:   Flag for the PRIORITY property
 *        int* dtStmpFlag: Flag for the DTSTAMP property
 *        int* seqFlag:    Flag for the SEQ property
 *        int* statFlag:   Flag for the STATUS property
 *        int* sumFlag:    Flag for the SUMMARY property
 *        int* transFlag:  Flag for the TRANSP property
 *        int* URLFlag:    Flag for the URL property
 *        int* recIDFlag:  Flag for the RECURID property
 *        int* dtendFlag:  Flag for the DTEND property
 *        int* durFlag:    Flag for the DURATION property
 *        int* calSclFlag: Flag for the CALSCALE property
 *        int* methFlag:   Flag for the METHOD property
 *		  int* repFlag:    Flag for the REPEAT property
 *		  int* attFlag:    Flag for the ATTACH property
 *		  int* almFlag:    Flag for the BEGIN:VALARM property
 *        int* almActFlag: Flag for the ACTION alarm property
 *        int* almTrigFlag:Flag for the TRIGGER alarm property
 *        int* sumAlmFlag: Flag for the SUMMARY alarm property
 *        int* decrAlmFlag:Flag for the DESCRIPTION alarm property
 *        int* durAlmFlag: Flag for the DURATION alarm property
 * @return ErrorCode: OTHER_ERROR if malloc fails
 *                    OK if sucess
 */
ErrorCode checkFlags(int* evtNum, int* strtFlag, int* verFlag, int* prodFlag, int* evtFlag, int* UIDFlag, int* clasFlag, int* createdFlag, int* decrFlag, int* dtStrFlag, int* geoFlag, int* lstModFlag, int* locFlag, int* orgFlag, int* prioFlag, int* dtStmpFlag, int* seqFlag, int* statFlag, int* sumFlag, int* transFlag, int* URLFlag, int* recIDFlag, int* dtendFlag, int* durFlag, int* calSclFlag, int* methFlag, int* repFlag, int* attFlag, int* almFlag, int* almActFlag, int* almTrigFlag, int* sumAlmFlag, int* decrAlmFlag, int* durAlmFlag);

/*
 * Frees the all the flags
 * @param int* evtNum:     Flag for the number of events
 		  int* strtFlag:   Flag for the BEGIN:VCALENDAR property
 *        int* verFlag:    Flag for ther VERSION property
 *        int* prodFlag:   Flag for the product ID property
 *        int* evtFlag:    Flag for the VEVENT property
 *        int* UIDFlag:    Flag for the UID property
 *        int* clasFlag:   Flag for the CLASS property
 *        int* createdFlag:Flag for the CREATED property
 *        int* decrFlag:   Flag for the DESCRIPTION property
 *        int* dtStrFlag:  Flag for the DTSTART property
 *        int* geoFlag:    Flag for the GEO property
 *        int* lstModFlag: Flag for the LAST-MOD property
 *        int* locFlag:    Flag for the LOCATION property
 *        int* orgFlag:    Flag for the ORGANIZER property
 *        int* prioFlag:   Flag for the PRIORITY property
 *        int* dtStmpFlag: Flag for the DTSTAMP property
 *        int* seqFlag:    Flag for the SEQ property
 *        int* statFlag:   Flag for the STATUS property
 *        int* sumFlag:    Flag for the SUMMARY property
 *        int* transFlag:  Flag for the TRANSP property
 *        int* URLFlag:    Flag for the URL property
 *        int* recIDFlag:  Flag for the RECURID property
 *        int* dtendFlag:  Flag for the DTEND property
 *        int* durFlag:    Flag for the DURATION property
 *        int* calSclFlag: Flag for the CALSCALE property
 *        int* methFlag:   Flag for the METHOD property
 *		  int* repFlag:    Flag for the REPEAT property
 *		  int* attFlag:    Flag for the ATTACH property
 *		  int* almFlag:    Flag for the BEGIN:VALARM property
 *        int* almActFlag: Flag for the ACTION alarm property
 *        int* almTrigFlag:Flag for the TRIGGER alarm property
 *        int* sumAlmFlag: Flag for the SUMMARY alarm property
 *        int* decrAlmFlag:Flag for the DESCRIPTION alarm property
 *        int* durAlmFlag: Flag for the DURATION alarm property
 * @post Frees all the flags
 */
void freeFlags(int* evtNum, int* strtFlag, int* verFlag, int* prodFlag, int* evtFlag, int* UIDFlag, int* clasFlag, int* createdFlag, int* decrFlag, int* dtStrFlag, int* geoFlag, int* lstModFlag, int* locFlag, int* orgFlag, int* prioFlag, int* dtStmpFlag, int* seqFlag, int* statFlag, int* sumFlag, int* transFlag, int* URLFlag, int* recIDFlag, int* dtendFlag, int* durFlag, int* calSclFlag, int* methFlag, int* repFlag, int* attFlag, int* almFlag, int* almActFlag, int* almTrigFlag, int* sumAlmFlag, int* decrAlmFlag, int* durAlmFlag);

/*
 * Frees memory for the input line from the file, and fcloses the file
 * @param FILE* inputFile: the iCalendar file
 *        char* inputLine: the string representation of the file line
 * @post: Frees memory for the file and string represntation of the file
 */

void freeFile(FILE* inputFile, char* inputLine);

/*
 * Sees if a string starts with another string
 * @return bool: true on success
 *               false on failure
 * @param char* str: the string of the file line
 *        char* compare: the string being compared
 */
bool startWith(char* str, char* compare);

/*
 * Compares a string with all the content after a colon
 * @return bool: true on success
 *               false on failure
 * @param char* str: the string of the file line
 *        char* compare: the string being compared
 */
bool endsWith(char* str, char* compare);

/*
 * Function to parse the file and check validity
 * Checks if the file is empty, NULL, and for the .ics extension
 * @return ErrorCode: INV_FILE if failed
 *					  OK if the parse was good
 * @param: char*: The name of the file
 */
ErrorCode parseFile(char* fileName);

/*
 * Function to parse the VERSION: line
 * @return ErrorCode: INV_VER if the version is invalid
 *                    DUP_VER VERSION line decalred twice in file
 *                    OK if parse sucessful
 * @param: char* inputLine: The string line from the file 
 *         int* verFlag: to indicate the VERSION: line has been parsed
 *         int* strtFlag: to see if BEGIN:VCALENDAR has been parsed
 *         Calendar* cal: Calendar struct
 * @post verFlag is set to 1 if the parse was sucessful
 *        Calendar version is updated
 */
ErrorCode parseVersion(char* inputLine, int* evtFlag, int* verFlag, int* strtFlag, Calendar* cal);

/*
 * Function to parse the PRODID: line
 * @return ErrorCode: INV_CAL if PRODID is declared too early
 *                    OK if parse sucessful
 * @param: int* verFlag: to see if VERSION was parsed
 *         int* prodFlag: to see if PRODID was parsed
 *         char* inputLine: The string line from the file
 *         Calendar* cal: Calendar struct
 * @post prodFlag set to 1 on successful parse
 *      Calendar prodID is updated on sucess
 */
ErrorCode parseProdID(int* verFlag, int* prodFlag, char* inputLine, Calendar* cal);

/*
 * Function to parse UID: line
 * @return ErrorCode: INV_CAL if parse unsucessful
 *                    OK if parse sucessful
 * @param int* evtFlag: sees if event was parsed
 *        char* inputLine: The string line from the file
 *        Calendar* cal: Calendar struct
 * @post Calendar->event->UID is updated if parse is sucessful
 */
ErrorCode parseUID(int* evtFlag, int* UIDFlag, char* inputLine, Calendar* cal);

/*
 * Function to parse DTSTAMP: property
 * Calls parseUTC
 * @return ErrorCode: INV_CAL if parse unsucessful
 *                    INV_CREATEDT if spcifically the DTStamp string is invalid, parse unsucessful
 *                    OK if parse sucessful
 * @param int* evtFlag: sees if event was parsed
 *        int len: length of inputLine
 *        char* inputLine: the string line from the file
 *        Calendar* cal: Calendar struct
 */
ErrorCode parseDTStamp(int* evtFlag, int* dtStmpFlag, int len, char* inputLine, Calendar* cal);

/*
 * Funtion to help parse DTSTAMP: line
 * This function is called by parseDTStanmp
 * The function is used to get check certain dates in the DT string, for example,
 * it will check if the days are above 31 days; if it is, it will return an error
 * if not, it will return OK
 * @return ErrorCode: INV_CREATDT if parse was unsucessful
 *                    OK if parese sucessful
 * @param int offset: Where in the string the parser will check
 *        char* cmpVal: the value being compared, ie: 31 days, 12 months etc.
 *        int dateLen: The length of what is being checked, ie: 2 for months
 *        char* DTStr: The string of the date and time
 */
ErrorCode parseUTC(int offset, char* cmpVal, int dateLen, char* DTSstr);

/*
 * Funtion used to parse properties
 */
void* parseProp(char* inputLine);

ErrorCode parseClass(int* evtFlag, int* clasFlag, Calendar* cal, char* inputLine);

ErrorCode parseCreated(int* evtFlag, int* createdFlag, Calendar* cal, char* inputLine);

ErrorCode parseDecr(int* evtFlag, int* almFlag, int* decrFlag, int* decrAlmFlag, Calendar* cal, char* inputLine, Alarm* tempAlarm);

ErrorCode parseGeo(int* evtFlag, int* geoFlag, Calendar* cal, char* inputLine);

ErrorCode parseLstMod(int* evtFlag, int* lstModFlag, Calendar* cal, char* inputLine);

ErrorCode parseLoc(int* evtFlag, int* locFlag, Calendar* cal, char* inputLine);

ErrorCode parseOrg(int* evtFlag, int* orgFlag, Calendar* cal, char* inputLine);

ErrorCode parsePrio(int* evtFlag, int* prioFlag, Calendar* cal, char* inputLine);

ErrorCode parseSeq(int* evtFlag, int* seqFlag, Calendar* cal, char* inputLine);

ErrorCode parseStat(int* evtFlag, int* statFlag, Calendar* cal, char* inputLine);

ErrorCode parseSum(int* evtFlag, int* almFlag, int* sumFlag, int* sumAlmFlag, Calendar* cal, char* inputLine, Alarm* tempAlarm);

ErrorCode parseURL(int* evtFlag, int* URLFlag, Calendar* cal, char* inputLine);

ErrorCode parseRecID(int* evtFlag, int* recIDFlag, Calendar* cal, char* inputLine);

ErrorCode parseAtt(int* evtFlag, int* almFlag, int* attFlag, Calendar* cal, char* inputLine, Alarm* tempAlarm);

ErrorCode parseCat(int* evtFlag, int* almFlag, Calendar* cal, char* inputLine);

ErrorCode parseCom(int* evtFlag, int* almFlag, Calendar* cal, char* inputLine);

ErrorCode parseCon(int* evtFlag, int* almFlag, Calendar* cal, char* inputLine);

ErrorCode parseExDt(int* evtFlag, int* almFlag, Calendar* cal, char* inputLine);

ErrorCode parseRstat(int* evtFlag, int* almFlag, Calendar* cal, char* inputLine);

ErrorCode parseRelt(int* evtFlag, int* almFlag, Calendar* cal, char* inputLine);

ErrorCode parseReso(int* evtFlag, int* almFlag, Calendar* cal, char* inputLine);

ErrorCode parseRdate(int* evtFlag, int* almFlag, Calendar* cal, char* inputLine);

ErrorCode parseTrans(int* evtFlag, int* almFlag, int* transFlag, Calendar* cal, char* inputLine);

ErrorCode parseDTStr(int* evtFlag, int* dtStrFlag, int* dtendFlag, int* durFlag,  Calendar* cal, char* inputLine);

ErrorCode parseDTend(int* evtFlag, int* dtStrFlag, int* dtendFlag, int* durFlag, Calendar* cal, char* inputLine);

ErrorCode parseDur(int* evtFlag, int* almFlag, int* durFlag, int* durAlmFlag, int* dtStrFlag, int* dtendFlag, char* inputLine, Alarm* tempAlarm, Calendar* cal);

ErrorCode parseRep(int* almFlag, int* repFlag, char* inputLine, Alarm* tempAlarm);

ErrorCode parseRule(int* evtFlag, int* almFlag, Calendar* cal, char* inputLine);

ErrorCode parseAtd(int* evtFlag, int* almFlag, Calendar* cal, char* inputLine, Alarm* tempAlarm);

ErrorCode parseCalScl(int* strtFlag, int* calSclFlag, int* evtFlag, Calendar* cal, char* inputLine);

ErrorCode parseMeth(int* strtFlag, int* methFlag, int* evtFlag, Calendar* cal, char* inputLine);

ErrorCode parseBegin(int* strtFlag, int* evtFlag, int* almFlag, char* inputLine);

ErrorCode parseActAlm(int* almFlag, int* almActFlag, char* inputLine, Alarm* tempAlarm);

ErrorCode parseTrigAlm(int* almFlag, int* almTrigFlag, char* inputLine, Alarm* tempAlarm);

ErrorCode parseEnd(char* inputLine, int* strtFlag, int* prodFlag, int* verFlag, int*evtNum, int* methFlag, int* evtFlag, int* UIDFlag, int* clasFlag, int* createdFlag, int* decrFlag, int* dtStrFlag, int* geoFlag, int* lstModFlag, int* locFlag, int* orgFlag, int* prioFlag, int* dtStmpFlag, int* seqFlag, int* statFlag, int* sumFlag, int* transFlag, int* URLFlag, int* recIDFlag, int* dtendFlag, int* attFlag, int* almFlag, int* almActFlag, int* almTrigFlag, int* repFlag, int* durFlag, int* durAlmFlag, int* decrAlmFlag, int* sumAlmFlag, Calendar* cal, Alarm* tempAlarm);

ErrorCode createCalendar(char* fileName, Calendar** obj){

	if(fileName == NULL || obj == NULL){
		return OTHER_ERROR;
	}

	ErrorCode check;
	Calendar* cal;
	FILE* inputFile;
	Alarm* tempAlarm = NULL;
	char* inputLine;
	int* strtFlag    = 0;
	int* verFlag     = 0;
	int* prodFlag    = 0;
	int* evtFlag     = 0;
	int* UIDFlag     = 0;
	int* clasFlag    = 0;
	int* createdFlag = 0;
	int* decrFlag    = 0;
	int* dtStrFlag   = 0;
	int* geoFlag     = 0;
	int* lstModFlag  = 0;
	int* locFlag     = 0;
	int* orgFlag     = 0;
	int* prioFlag    = 0;
	int* dtStmpFlag  = 0;
	int* seqFlag     = 0;
	int* statFlag    = 0;
	int* sumFlag     = 0;
	int* transFlag   = 0;
	int* URLFlag     = 0;
	int* recIDFlag   = 0;
	int* dtendFlag   = 0;
	int* durFlag     = 0;
	int* calSclFlag  = 0;
	int* methFlag    = 0;
	int* repFlag     = 0;
	int* attFlag     = 0;
	int* almFlag     = 0;
	int* almActFlag  = 0;
	int* almTrigFlag = 0;
	int* decrAlmFlag = 0;
	int* sumAlmFlag  = 0;
	int* durAlmFlag  = 0;
	int* evtNum      = 0;

	//Calendar mallocs
	cal = malloc(sizeof(Calendar));
	cal->event = malloc(sizeof(Event));

	//Checks if malloc fails
	if(cal == NULL || cal->event == NULL){
		deleteCalendar(cal);
		return OTHER_ERROR;
	}
	
	//Allocates memory for flags
	strtFlag    = malloc(sizeof(int));
	verFlag     = malloc(sizeof(int));
	prodFlag    = malloc(sizeof(int));
	evtFlag     = malloc(sizeof(int));
	UIDFlag     = malloc(sizeof(int));
	clasFlag    = malloc(sizeof(int));
	createdFlag = malloc(sizeof(int));
	decrFlag    = malloc(sizeof(int));
	dtStrFlag   = malloc(sizeof(int));
	geoFlag     = malloc(sizeof(int));
	lstModFlag  = malloc(sizeof(int));
	locFlag     = malloc(sizeof(int));
	orgFlag     = malloc(sizeof(int));
	prioFlag    = malloc(sizeof(int));
	dtStmpFlag  = malloc(sizeof(int));
	seqFlag     = malloc(sizeof(int));
	statFlag    = malloc(sizeof(int));
	sumFlag     = malloc(sizeof(int));
	transFlag   = malloc(sizeof(int));
	URLFlag     = malloc(sizeof(int));
	recIDFlag   = malloc(sizeof(int));
	dtendFlag   = malloc(sizeof(int));
	durFlag     = malloc(sizeof(int));
	calSclFlag  = malloc(sizeof(int));
	methFlag    = malloc(sizeof(int));
	repFlag     = malloc(sizeof(int));
	attFlag     = malloc(sizeof(int));
	almFlag     = malloc(sizeof(int));
	almActFlag  = malloc(sizeof(int));
	almTrigFlag = malloc(sizeof(int));
	sumAlmFlag  = malloc(sizeof(int));
	decrAlmFlag = malloc(sizeof(int));
	durAlmFlag  = malloc(sizeof(int));
	evtNum      = malloc(sizeof(int));

	//Checks to see if the flags were parsed correctly
	check = checkFlags(evtNum, strtFlag, verFlag, prodFlag, evtFlag, UIDFlag, clasFlag, createdFlag, decrFlag, dtStrFlag, geoFlag, lstModFlag, locFlag, orgFlag, prioFlag, dtStmpFlag, seqFlag, statFlag, sumFlag, transFlag, URLFlag, recIDFlag, dtendFlag, durFlag, calSclFlag, methFlag, repFlag, attFlag, almFlag, almActFlag, almTrigFlag, sumAlmFlag, decrAlmFlag, durAlmFlag);
	if(check != OK){
		freeFlags(evtNum, strtFlag, verFlag, prodFlag, evtFlag, UIDFlag, clasFlag, createdFlag, decrFlag, dtStrFlag, geoFlag, lstModFlag, locFlag, orgFlag, prioFlag, dtStmpFlag, seqFlag, statFlag, sumFlag, transFlag, URLFlag, recIDFlag, dtendFlag, durFlag, calSclFlag, methFlag, repFlag, attFlag, almFlag, almActFlag, almTrigFlag, sumAlmFlag, decrAlmFlag, durAlmFlag);
		deleteCalendar(cal);
		return OTHER_ERROR;
	}

	//Checks to see if the file is invalid
	check = parseFile(fileName);
	if(check != OK){
		freeFlags(evtNum, strtFlag, verFlag, prodFlag, evtFlag, UIDFlag, clasFlag, createdFlag, decrFlag, dtStrFlag, geoFlag, lstModFlag, locFlag, orgFlag, prioFlag, dtStmpFlag, seqFlag, statFlag, sumFlag, transFlag, URLFlag, recIDFlag, dtendFlag, durFlag, calSclFlag, methFlag, repFlag, attFlag, almFlag, almActFlag, almTrigFlag, sumAlmFlag, decrAlmFlag, durAlmFlag);
		deleteCalendar(cal);
		return check;
	}

	//List initializers
	cal->event->properties = initializeList(&propPrintFunc, &propDeleteFunc, &propCompareFunc);
	cal->event->alarms = initializeList(&alarmPrintFunc, &alarmDeleteFunc, &alarmCompareFunc);

	inputFile = fopen(fileName, "r");
	inputLine = malloc(sizeof(char)*76);

	while(fgets(inputLine, 76, inputFile) != NULL){

		if(inputLine[0] != ';' && inputLine[0] != '\n'){
			int len = strlen(inputLine);

			//Erase the newline
			if (inputLine[len - 1] == '\n'){
				inputLine[len - 1] = '\0';
			}

			//Update length
			len = strlen(inputLine);

			printf("%s\n", inputLine);

			//Parses through all the iCalendar components/properties
			if(startWith(inputLine, "BEGIN")){
				//Parse the start of Calendar, ALARM, or EVENT
				check = parseBegin(strtFlag, evtFlag, almFlag, inputLine);

				if(*almFlag > 0 && check == OK){
					tempAlarm = malloc(sizeof(Alarm));
					tempAlarm->properties = initializeList(&propPrintFunc, &propDeleteFunc, &propCompareFunc);
				}
			} else if(startWith(inputLine, "VERSION")){
				//Parses VERSION
				check = parseVersion(inputLine, evtFlag, verFlag, strtFlag, cal);
			} else if (startWith(inputLine, "PRODID")){
				//Parses PRODID
				check = parseProdID(verFlag, prodFlag, inputLine, cal);
			} else if(startWith(inputLine, "UID")){
				//Parses UID
				check = parseUID(evtFlag, UIDFlag, inputLine, cal);
			} else if(startWith(inputLine, "DTSTAMP")){
				//Parses DTStamp
				check = parseDTStamp(evtFlag, dtStmpFlag, len, inputLine, cal);
			} else if(startWith(inputLine, "CLASS")){
				//Parses CLASS
				check = parseClass(evtFlag, clasFlag, cal, inputLine);
			} else if(startWith(inputLine, "CREATED")){
				//Parse CREATED
				check = parseCreated(evtFlag, createdFlag, cal, inputLine);
			} else if(startWith(inputLine, "DESCRIPTION")){
				//Parse DESCRIPTION
				check = parseDecr(evtFlag, almFlag, decrFlag, decrAlmFlag, cal, inputLine, tempAlarm);
			} else if(startWith(inputLine, "GEO")){
				//Parse Geo
				check = parseGeo(evtFlag, geoFlag, cal, inputLine);
			} else if(startWith(inputLine, "LAST-MODIFIED")){
				//Parse LAST-MOD
				check = parseLstMod(evtFlag, lstModFlag, cal, inputLine);
			} else if(startWith(inputLine, "LOCATION")){
				//Parse LOCATION
				check = parseLstMod(evtFlag, locFlag, cal, inputLine);
			} else if(startWith(inputLine, "ORGANIZER")){
				//Parse Orgainzer
				check = parseOrg(evtFlag, orgFlag, cal, inputLine);
			} else if(startWith(inputLine, "PRIORITY")){
				//Parse PRIORITY
				check = parsePrio(evtFlag, prioFlag, cal, inputLine);
			} else if(startWith(inputLine, "SEQUENCE")){
				//Parse SEQ
				check = parseSeq(evtFlag, seqFlag, cal, inputLine);
			} else if(startWith(inputLine, "STATUS")){
				//Parse STATUS
				check = parseStat(evtFlag, statFlag, cal, inputLine);
			} else if(startWith(inputLine, "SUMMARY")){
				//Parse SUMMARY
				check = parseSum(evtFlag, almFlag, sumFlag, sumAlmFlag, cal, inputLine, tempAlarm);
			} else if(startWith(inputLine, "TRANSP")){
				//Parse TRANSP
				check = parseTrans(evtFlag, almFlag, transFlag, cal, inputLine);
			} else if(startWith(inputLine, "URL")){
				//Parse URL
				check = parseURL(evtFlag, URLFlag, cal, inputLine);
			} else if(startWith(inputLine, "RECURRENCE-ID")){
				//Parse RECURID
				check = parseRecID(evtFlag, recIDFlag, cal, inputLine);
			} else if(startWith(inputLine, "ATTACH")){
				//Parse ATTACH
				check = parseAtt(evtFlag, almFlag, attFlag, cal, inputLine, tempAlarm);
			} else if(startWith(inputLine, "CATEGORIES")){
				//Parse CATEGORIES
				check = parseCat(evtFlag, almFlag, cal, inputLine);
			} else if(startWith(inputLine, "COMMENT")){
				//Parse COMMENT
				check = parseCom(evtFlag, almFlag, cal, inputLine);
			} else if(startWith(inputLine, "CONTACT")){
				//Parse EXDATE
				check = parseCon(evtFlag, almFlag, cal, inputLine);
			} else if(startWith(inputLine, "EXDATE")){
				//Parse CONTACT
			} else if(startWith(inputLine, "REQUEST-STATUS")){
				//Parse REQUEST-STATUS
				check = parseRstat(evtFlag, almFlag, cal, inputLine);
			} else if(startWith(inputLine, "RELATED-TO")){
				//Parse RELATE-TO
				check = parseRelt(evtFlag, almFlag, cal, inputLine);
			} else if(startWith(inputLine, "RESOURCES")){
				//Parse RESOURCES
				check = parseReso(evtFlag, almFlag, cal, inputLine);
			} else if(startWith(inputLine, "RDATE")){
				//Parse RDATE
				check = parseRdate(evtFlag, almFlag, cal, inputLine);
			} else if(startWith(inputLine, "RRULE")) {
				//Parse RRULE
				check = parseRule(evtFlag, almFlag, cal, inputLine);
			} else if(startWith(inputLine, "REPEAT")){
				//Parse REPEAT
				check = parseRep(almFlag, repFlag, inputLine, tempAlarm);
			} else if(startWith(inputLine, "DURATION")){
				//Parse DURATION
				check = parseDur(evtFlag, almFlag, durFlag, durAlmFlag, dtStrFlag, dtendFlag, inputLine, tempAlarm, cal);
			} else if(startWith(inputLine, "ATTENDEE")){
				//Parse ATTENDEE
				check = parseAtd(evtFlag, almFlag, cal, inputLine, tempAlarm);
			} else if(startWith(inputLine, "DTSTART")){
				//Parse DTSTART
				check = parseDTStr(evtFlag, dtStrFlag, dtendFlag, durFlag,  cal, inputLine);
			} else if(startWith(inputLine, "DTEND")){
				//Parse DTEDND
				check = parseDTend(evtFlag, dtStrFlag, dtendFlag, durFlag, cal, inputLine);
			} else if(startWith(inputLine, "CALSCALE")){
				//Parse CALSCALE
				check = parseCalScl(strtFlag, calSclFlag, evtFlag, cal, inputLine);
			} else if(startWith(inputLine, "METHOD")){
				//Parse METHOD
				check = parseMeth(strtFlag, methFlag, evtFlag, cal, inputLine);
			} else if(startWith(inputLine, "ACTION")){
				//Parse ACTION
				check = parseActAlm(almFlag, almActFlag, inputLine, tempAlarm);
			} else if(startWith(inputLine, "TRIGGER")){
				//Parse TRIGGER
				check = parseTrigAlm(almFlag, almTrigFlag, inputLine, tempAlarm);
			} else if(startWith(inputLine, "END")){
				//Parse END:VCALENDAR, END:EVENT, END:VALARM 
				check = parseEnd(inputLine, strtFlag, prodFlag, verFlag,evtNum, methFlag, evtFlag, UIDFlag, clasFlag, createdFlag, decrFlag, dtStrFlag, geoFlag, lstModFlag, locFlag, orgFlag, prioFlag, dtStmpFlag, seqFlag, statFlag, sumFlag, transFlag, URLFlag, recIDFlag, dtendFlag, attFlag, almFlag, almActFlag, almTrigFlag, repFlag, durFlag, durAlmFlag, decrAlmFlag, sumAlmFlag, cal, tempAlarm);
			} else {
				freeFlags(evtNum, strtFlag, verFlag, prodFlag, evtFlag, UIDFlag, clasFlag, createdFlag, decrFlag, dtStrFlag, geoFlag, lstModFlag, locFlag, orgFlag, prioFlag, dtStmpFlag, seqFlag, statFlag, sumFlag, transFlag, URLFlag, recIDFlag, dtendFlag, durFlag, calSclFlag, methFlag, repFlag, attFlag, almFlag, almActFlag, almTrigFlag, sumAlmFlag, decrAlmFlag, durAlmFlag);
				freeFile(inputFile, inputLine);
				deleteCalendar(cal);
				return INV_CAL;
			}

			if(check != OK){
				if(tempAlarm != NULL){
					free(tempAlarm);
				}
				freeFlags(evtNum, strtFlag, verFlag, prodFlag, evtFlag, UIDFlag, clasFlag, createdFlag, decrFlag, dtStrFlag, geoFlag, lstModFlag, locFlag, orgFlag, prioFlag, dtStmpFlag, seqFlag, statFlag, sumFlag, transFlag, URLFlag, recIDFlag, dtendFlag, durFlag, calSclFlag, methFlag, repFlag, attFlag, almFlag, almActFlag, almTrigFlag, sumAlmFlag, decrAlmFlag, durAlmFlag);
				freeFile(inputFile, inputLine);
				deleteCalendar(cal);
				return check;
			}

		}
		inputLine[0] = '\0';
	}

	if(*evtNum != 1){
		freeFlags(evtNum, strtFlag, verFlag, prodFlag, evtFlag, UIDFlag, clasFlag, createdFlag, decrFlag, dtStrFlag, geoFlag, lstModFlag, locFlag, orgFlag, prioFlag, dtStmpFlag, seqFlag, statFlag, sumFlag, transFlag, URLFlag, recIDFlag, dtendFlag, durFlag, calSclFlag, methFlag, repFlag, attFlag, almFlag, almActFlag, almTrigFlag, sumAlmFlag, decrAlmFlag, durAlmFlag);
		freeFile(inputFile, inputLine);
		deleteCalendar(cal);
		return INV_CAL;
	}
	
	freeFlags(evtNum, strtFlag, verFlag, prodFlag, evtFlag, UIDFlag, clasFlag, createdFlag, decrFlag, dtStrFlag, geoFlag, lstModFlag, locFlag, orgFlag, prioFlag, dtStmpFlag, seqFlag, statFlag, sumFlag, transFlag, URLFlag, recIDFlag, dtendFlag, durFlag, calSclFlag, methFlag, repFlag, attFlag, almFlag, almActFlag, almTrigFlag, sumAlmFlag, decrAlmFlag, durAlmFlag);
	freeFile(inputFile, inputLine);

	(*obj) = cal;
	return OK;
}

char* propPrintFunc(void *toBePrinted){
	
	char* tmpStr;
	Property* tmpProp;
	int len;
	
	if (toBePrinted == NULL){
		return NULL;
	}
	
	tmpProp = (Property*)toBePrinted;
	
	len = strlen(tmpProp->propName) + strlen(tmpProp->propDescr) + 37;
	tmpStr = (char*)malloc(sizeof(char)*len);

	if(tmpStr == NULL){
		return NULL;
	}
	
	sprintf(tmpStr, "Property Name:%s\nProperty Description:%s", tmpProp->propName, tmpProp->propDescr);	

	return tmpStr;
}

int propCompareFunc(const void *first, const void *second){

	Property* tmpProp1;
	Property* tmpProp2;
	
	if (first == NULL || second == NULL){
		return 0;
	}
	
	tmpProp1 = (Property*)first;
	tmpProp2 = (Property*)second;

	return strcmp(tmpProp1->propName, tmpProp2->propName);
}

void propDeleteFunc(void *toBeDeleted){
	
	free(toBeDeleted);
}

char* alarmPrintFunc(void *toBePrinted){
	
	char* tmpAlmStr;
	char* listStr;
	Alarm* tempAlarm;
	int len;
	int listLen;
	
	if (toBePrinted == NULL){
		return NULL;
	}
	
	tempAlarm = (Alarm*)toBePrinted;
	listStr = toString(tempAlarm->properties);
	

	if(listStr == NULL){
		return NULL;
	}

	len = strlen(tempAlarm->action) + strlen(tempAlarm->trigger) + 30;
	listLen = strlen(listStr);

	len = len + listLen;
	tmpAlmStr = (char*)malloc(sizeof(char)*len);
	
	if(tmpAlmStr == NULL){
		return NULL;
	}

	sprintf(tmpAlmStr, "ALARM:\nAction: %s\nTrigger: %s\n%s", tempAlarm->action, tempAlarm->trigger, listStr);

	free(listStr);

	return tmpAlmStr;
}

int alarmCompareFunc(const void *first, const void *second){
	Alarm* tmpAlarm1;
	Alarm* tmpAlarm2;
	
	if (first == NULL || second == NULL){
		return 0;
	}
	
	tmpAlarm1 = (Alarm*)first;
	tmpAlarm2 = (Alarm*)second;

	return strcmp(tmpAlarm1->action, tmpAlarm2->action);
}

void alarmDeleteFunc(void *toBeDeleted){
	
	Alarm* tempAlarm;
	tempAlarm = (Alarm*)toBeDeleted;

	free(tempAlarm->trigger);
	clearList(&tempAlarm->properties);
}

ErrorCode checkFlags(int* evtNum, int* strtFlag, int* verFlag, int* prodFlag, int* evtFlag, int* UIDFlag, int* clasFlag, int* createdFlag, int* decrFlag, int* dtStrFlag, int* geoFlag, int* lstModFlag, int* locFlag, int* orgFlag, int* prioFlag, int* dtStmpFlag, int* seqFlag, int* statFlag, int* sumFlag, int* transFlag, int* URLFlag, int* recIDFlag, int* dtendFlag, int* durFlag, int* calSclFlag, int* methFlag, int* repFlag, int* attFlag, int* almFlag, int* almActFlag, int* almTrigFlag, int* sumAlmFlag, int* decrAlmFlag, int* durAlmFlag){

	//Checks if malloc failed for the flags
	if(evtNum == NULL || strtFlag == NULL || verFlag == NULL || prodFlag == NULL || evtFlag == NULL || UIDFlag == NULL ||clasFlag == NULL || createdFlag == NULL || decrFlag == NULL || dtStrFlag == NULL || geoFlag == NULL || lstModFlag == NULL || locFlag == NULL || orgFlag == NULL || prioFlag == NULL || dtStmpFlag == NULL || seqFlag == NULL || statFlag == NULL || sumFlag == NULL || transFlag == NULL || URLFlag == NULL || recIDFlag == NULL || dtendFlag == NULL || durFlag == NULL || calSclFlag == NULL || methFlag == NULL || repFlag == NULL || attFlag == NULL || almActFlag == NULL || almTrigFlag == NULL || sumAlmFlag == NULL || decrAlmFlag == NULL || durAlmFlag == NULL){
		return OTHER_ERROR;
	} else {
		return OK;
	}
}

void freeFlags(int* evtNum, int* strtFlag, int* verFlag, int* prodFlag, int* evtFlag, int* UIDFlag, int* clasFlag, int* createdFlag, int* decrFlag, int* dtStrFlag, int* geoFlag, int* lstModFlag, int* locFlag, int* orgFlag, int* prioFlag, int* dtStmpFlag, int* seqFlag, int* statFlag, int* sumFlag, int* transFlag, int* URLFlag, int* recIDFlag, int* dtendFlag, int* durFlag, int* calSclFlag, int* methFlag, int* repFlag, int* attFlag, int* almFlag, int* almActFlag, int* almTrigFlag, int* sumAlmFlag, int* decrAlmFlag, int* durAlmFlag){
	free(strtFlag);
	free(verFlag);
	free(prodFlag);
	free(evtFlag);
	free(UIDFlag);
	free(clasFlag);
	free(createdFlag);
	free(decrFlag);
	free(dtStrFlag);
	free(geoFlag);
	free(lstModFlag);
	free(locFlag);
	free(orgFlag);
	free(prioFlag);
	free(dtStmpFlag);
	free(seqFlag);
	free(statFlag);
	free(sumFlag);
	free(transFlag);
	free(URLFlag);
	free(recIDFlag);
	free(dtendFlag);
	free(durFlag);
	free(calSclFlag);
	free(methFlag);
	free(repFlag);
	free(attFlag);
	free(almFlag);
	free(almActFlag);
	free(almTrigFlag);
	free(sumAlmFlag);
	free(decrAlmFlag);
	free(durAlmFlag);
	free(evtNum);
}

void freeFile(FILE* inputFile, char* inputLine){
	fclose(inputFile);
	free(inputLine);
}

bool startWith(char* str, char* compare){
	int lenOfCmp = strlen(compare);
	int lenOfStr = strlen(str);

	//General check
	if((lenOfCmp > lenOfStr) || str == NULL || compare == NULL){
		return false;
	} else if(strncasecmp(str, compare, lenOfCmp) == 0){ //Checks to see if the the str at length of the compare is equal to the compare
		
		//Checks to see if there is a colon or semi colon after propName
		if(str[lenOfCmp] != ':' && str[lenOfCmp] != ';'){
			return false;
		} 

		return true;
	} else {
		return false;
	}
}

ErrorCode parseFile(char* fileName){

	if(fileName == NULL){
		return INV_FILE;
	}

	FILE* inputFile = fopen(fileName, "r");
	char* ext = strchr(fileName,'.');
	int fileSize;

	fseek(inputFile, 0, SEEK_END);
	fileSize = ftell(inputFile);

	/*
	 * File is NULL or
	 * .ics is not the extension
	 * File is empty
	 */
	if(inputFile == NULL || (strcmp(ext, ".ics") != 0) || fileSize == 0){
		fclose(inputFile);
		return INV_FILE;
	}

	//The input file is malformed after fseek and ftell and must be closed
	fclose(inputFile);
	return OK;
}

ErrorCode parseVersion(char* inputLine, int* evtFlag, int* verFlag, int* strtFlag, Calendar* cal){

	if(*strtFlag != 1 || *evtFlag != 0){ //BEGIN:VCALENDAR has not yet been declared
		return INV_CAL;
	} else if (*verFlag != 0){ //Duplicate
		return DUP_VER;
	} else if (inputLine[7] != ':'){
		return INV_VER;
	}
	char* spareStr;
	float checkVal;

	spareStr = malloc(sizeof(char)*strlen(inputLine) + 1);
	strcpy(spareStr, strchr(inputLine, ':') + 1);

	for(int i=0; i<strlen(spareStr); i++){
		checkVal = isdigit(spareStr[i]);

		//Checks that the version is a number or deimal
		if(checkVal == 0 && spareStr[i] != '.'){
			free(spareStr);
			return INV_VER;
		}
	}

	if(spareStr[0] == '\0'){
		return INV_VER;
	}

	checkVal = atof(spareStr);
	free(spareStr);

	if(checkVal < 0){
		return INV_VER;
	}

	*verFlag = 1;
	cal->version = checkVal;
	return OK;
}

ErrorCode parseProdID(int* strtFlag, int* prodFlag, char* inputLine, Calendar* cal){
	if((*strtFlag != 1) ||(*prodFlag != 0)){ //PRODID already declared
		return INV_CAL;
	}

	char* spareColon;
	char* spareSemi;
	char* tokenColon;
	char* tokenSemi;

	spareColon = malloc(sizeof(char)*strlen(inputLine) + 1);
	spareSemi = malloc(sizeof(char)*strlen(inputLine) + 1);

	strcpy(spareColon, inputLine);
	strcpy(spareSemi, inputLine);

	tokenColon = strtok(spareColon, ":");
	tokenSemi = strtok(spareSemi, ";");

	//To see if the propName has param values seperated from a semicolon or a colon
	if(strlen(tokenColon) < strlen(tokenSemi)){
		strcpy(cal->prodID, strchr(inputLine, ':') + 1);
	} else if (strlen(tokenColon) > strlen(tokenSemi)){
		strcpy(cal->prodID, strchr(inputLine, ';') + 1);
	}

	free(spareColon);
	free(spareSemi);

	if(cal->prodID[0] == '\0'){
		return INV_CAL;
	}

	*prodFlag = 1;
	return OK;	
}

ErrorCode parseUID(int* evtFlag, int* UIDFlag, char* inputLine, Calendar* cal){
	if(*evtFlag != 1 || *UIDFlag != 0){ //BEGIN:VEVENT has not been delclared
		return INV_CAL;
	} 

	char* spareColon;
	char* spareSemi;
	char* tokenColon;
	char* tokenSemi;

	spareColon = malloc(sizeof(char)*strlen(inputLine) + 1);
	spareSemi = malloc(sizeof(char)*strlen(inputLine) + 1);

	strcpy(spareColon, inputLine);
	strcpy(spareSemi, inputLine);

	tokenColon = strtok(spareColon, ":");
	tokenSemi = strtok(spareSemi, ";");

	//To see if the propName has param values seperated from a semicolon or a colon
	if(strlen(tokenColon) < strlen(tokenSemi)){
		strcpy(cal->event->UID, strchr(inputLine, ':') + 1);
	} else if (strlen(tokenColon) > strlen(tokenSemi)){
		strcpy(cal->event->UID, strchr(inputLine, ';') + 1);
	}

	free(spareColon);
	free(spareSemi);

	if(cal->event->UID[0] == '\0'){
		return INV_CAL;
	}

	*UIDFlag = 1;

	return OK;
	
}

ErrorCode parseDTStamp(int* evtFlag, int* dtStmpFlag, int len, char* inputLine, Calendar* cal){
	ErrorCode monthCheck;
	ErrorCode dayCheck;
	ErrorCode hourCheck;
	ErrorCode minCheck;
	ErrorCode secCheck;

	if(len != 24){
		return INV_CREATEDT;
	} else if(*evtFlag != 1){
		return INV_CAL;
	}

	for(int i=8; i<24; i++){
		if(i == 16){
			if(inputLine[i] != 'T'){
				return INV_CREATEDT; //Checks to see if T is in the right spot
			}
		} else if (i == 23){
			if(inputLine[i] != 'Z'){ //Checks to see is the last digit is Z
				return INV_CREATEDT;
			}
		} else if(!(isdigit(inputLine[i]))){ //Makes sure all number are digits
			return INV_CREATEDT;
		}
	}

	//Makes sure all the digits are correctly placed; refer to parseUTC
	monthCheck = parseUTC(12, "12", 2, inputLine);
	dayCheck   = parseUTC(14, "31", 2, inputLine);
	hourCheck  = parseUTC(17, "24", 2, inputLine);
	minCheck   = parseUTC(19, "60", 2, inputLine);
	secCheck   = parseUTC(21, "61", 2, inputLine);

	if(monthCheck != OK || dayCheck != OK || hourCheck != OK || minCheck != OK || secCheck != OK){
		cal->event->creationDateTime.UTC = false;
		return INV_CREATEDT;
	}

	strncpy(cal->event->creationDateTime.date, inputLine+8, 8);
	strncpy(cal->event->creationDateTime.time, inputLine+17, 6);
	cal->event->creationDateTime.UTC = true;

	*dtStmpFlag = 1;

	return OK;
}

ErrorCode parseUTC(int offset, char* cmpVal, int dateLen, char* DTSstr){
	char* dateCheck;
	dateCheck = malloc(sizeof(char)*dateLen);

	strncpy(dateCheck, DTSstr + offset, dateLen);

	if(strcmp(dateCheck, cmpVal) > 0){
		free(dateCheck);
		return INV_CREATEDT;
	} else {
		free(dateCheck);
		return OK;
	}
}

void* parseProp(char* inputLine){

	char* spareColon;
	char* spareSemi;
	char* tokenColon;
	char* tokenSemi;
	int len;
	Property* newProp;

	spareColon = malloc(sizeof(char)*strlen(inputLine) + 1);
	spareSemi = malloc(sizeof(char)*strlen(inputLine) + 1);

	strcpy(spareColon, inputLine);
	strcpy(spareSemi, inputLine);

	tokenColon = strtok(spareColon, ":");
	tokenSemi = strtok(spareSemi, ";");

	//To see if the propName has param values seperated from a semicolon or a colon
	if(strlen(tokenColon) < strlen(tokenSemi)){
		len = strlen(strchr(inputLine, ':'));
		newProp = malloc(sizeof(Property) + sizeof(char) * len);
		strcpy(newProp->propName, tokenColon);
		strcpy(newProp->propDescr, strchr(inputLine, ':') + 1);

	} else if (strlen(tokenColon) > strlen(tokenSemi)){
		len = strlen(strchr(inputLine, ';'));
		newProp = malloc(sizeof(Property) + sizeof(char) * len);
		strcpy(newProp->propName, tokenSemi);
		strcpy(newProp->propDescr, strchr(inputLine, ';') + 1);
	}

	free(spareColon);
	free(spareSemi);
	return newProp;
}

/*
 * Function to parse CLASS property
 * 
 */
ErrorCode parseClass(int* evtFlag, int* clasFlag, Calendar* cal, char* inputLine){

	if(evtFlag == NULL || clasFlag == NULL || cal == NULL || inputLine == NULL){
		return OTHER_ERROR;
	}

	if(*evtFlag != 1 || *clasFlag != 0){
		return INV_EVENT;
	}

	insertSorted(&cal->event->properties, parseProp(inputLine));

	*clasFlag = 1;
	return OK;
}

ErrorCode parseCreated(int* evtFlag, int* createdFlag, Calendar* cal, char* inputLine){
	if(*evtFlag != 1 || *createdFlag != 0){
		return INV_EVENT;
	}

	//Check for UTC
	insertSorted(&cal->event->properties, parseProp(inputLine));

	*createdFlag = 1;
	return OK;
}

ErrorCode parseDecr(int* evtFlag, int* almFlag, int* decrFlag, int* decrAlmFlag, Calendar* cal, char* inputLine, Alarm* tempAlarm){
	if(*evtFlag != 1 || *decrFlag != 0 || *decrAlmFlag != 0){
		return INV_EVENT;
	}

	if(*almFlag < 1){ //In event
		insertSorted(&cal->event->properties, parseProp(inputLine));
		*decrFlag = 1;
	} else if (*almFlag == 2 || *almFlag == 3){//In Alarm: EMAIL and DISPLAY only
		insertSorted(&tempAlarm->properties, parseProp(inputLine));
		*decrAlmFlag = 1;
	} else {
		return INV_EVENT;
	}

	return OK;
}

ErrorCode parseGeo(int* evtFlag, int* geoFlag, Calendar* cal, char* inputLine){
	if(*evtFlag != 1 || *geoFlag != 0){
		return INV_EVENT;
	}

	insertSorted(&cal->event->properties, parseProp(inputLine));

	*geoFlag = 1;
	return OK;
}

ErrorCode parseLstMod(int* evtFlag, int* lstModFlag, Calendar* cal, char* inputLine){
	if(*evtFlag != 1 || *lstModFlag != 0){
		return INV_EVENT;
	}

	//Check utc
	insertSorted(&cal->event->properties, parseProp(inputLine));

	*lstModFlag = 1;
	return OK;
}

ErrorCode  parseLoc(int* evtFlag, int* locFlag, Calendar* cal, char* inputLine){
	if(*evtFlag != 1 || *locFlag != 0){
		return INV_EVENT;
	}

	insertSorted(&cal->event->properties, parseProp(inputLine));	

	*locFlag = 1;
	return OK;
}

ErrorCode parseOrg(int* evtFlag, int* orgFlag, Calendar* cal, char* inputLine){
	if(*evtFlag != 1 || *orgFlag != 0){
		return INV_EVENT;
	}

	insertSorted(&cal->event->properties, parseProp(inputLine));

	*orgFlag = 1;
	return OK;
}

ErrorCode parsePrio(int* evtFlag, int* prioFlag, Calendar* cal, char* inputLine){
	if(*evtFlag != 1 || *prioFlag != 0){
		return INV_EVENT;
	}

	//Integer 0-9
	insertSorted(&cal->event->properties, parseProp(inputLine));

	*prioFlag = 1;
	return OK;
}

ErrorCode parseSeq(int* evtFlag, int* seqFlag, Calendar* cal, char* inputLine){
	if(*evtFlag != 1 || *seqFlag != 0){
		return INV_EVENT;
	}

	Property* tempProp = parseProp(inputLine);

	//Checks if the description is empty
	if(tempProp->propDescr[0] == '\0'){
		free(tempProp);
		return INV_EVENT;
	}

	insertSorted(&cal->event->properties, tempProp);

	*seqFlag = 1;
	return OK;
}

ErrorCode parseStat(int* evtFlag, int* statFlag, Calendar* cal, char* inputLine){
	if(*evtFlag != 1 || *statFlag != 0){
		return INV_EVENT;
	}

	Property* tempProp = parseProp(inputLine);

	//Checks if the description is empty
	if(tempProp->propDescr[0] == '\0'){
		free(tempProp);
		return INV_EVENT;
	}

	insertSorted(&cal->event->properties, tempProp);

	*statFlag = 1;
	return OK;
}

ErrorCode parseSum(int* evtFlag, int* almFlag, int* sumFlag, int* sumAlmFlag, Calendar* cal, char* inputLine, Alarm* tempAlarm){
	if(*evtFlag != 1){
		return INV_EVENT;
	}

	Property* tempProp = parseProp(inputLine);

	//Checks if the description is empty
	if(tempProp->propDescr[0] == '\0'){
		free(tempProp);
		return INV_EVENT;
	}

	if(*almFlag < 1 && *sumFlag == 0){ //In event
		insertSorted(&cal->event->properties, tempProp);
		*sumFlag = 1;
	} else if (*almFlag == 3 && *sumAlmFlag == 0){//In Alarm: EMAIL
		insertSorted(&tempAlarm->properties, tempProp);
		*sumAlmFlag = 1;
	} else {
		return INV_EVENT;
	}

	return OK;
}

ErrorCode parseURL(int* evtFlag, int* URLFlag, Calendar* cal, char* inputLine){
	if(*evtFlag != 1 || *URLFlag != 0){
		return INV_EVENT;
	}

	Property* tempProp = parseProp(inputLine);

	//Checks if the description is empty
	if(tempProp->propDescr[0] == '\0'){
		free(tempProp);
		return INV_EVENT;
	}

	insertSorted(&cal->event->properties, tempProp);

	*URLFlag = 1;
	return OK;
}

ErrorCode parseRecID(int* evtFlag, int* recIDFlag, Calendar* cal, char* inputLine){
	if(*evtFlag != 1 || *recIDFlag != 0){
		return INV_EVENT;
	}

	Property* tempProp = parseProp(inputLine);

	//Checks if the description is empty
	if(tempProp->propDescr[0] == '\0'){
		free(tempProp);
		return INV_EVENT;
	}

	insertSorted(&cal->event->properties, tempProp);

	*recIDFlag = 1;
	return OK;
}

ErrorCode parseAtt(int* evtFlag, int* almFlag, int* attFlag, Calendar* cal, char* inputLine, Alarm* tempAlarm){
	if(*evtFlag != 1){
		return INV_EVENT;
	}

	Property* tempProp = parseProp(inputLine);

	//Checks if the description is empty
	if(tempProp->propDescr[0] == '\0'){
		free(tempProp);
		return INV_EVENT;
	}

	if(*almFlag < 1){
		insertSorted(&cal->event->properties, tempProp);

	} else if(*almFlag == 1){ //If Audio ALARM
		if(*attFlag != 0){ //Audio can only have 1 attach
			return INV_EVENT;
		} else {
			insertSorted(&tempAlarm->properties, tempProp);
			*attFlag = 1;
		}
	} else if (*almFlag == 3){ //If Email ALARM
		insertSorted(&tempAlarm->properties, tempProp);	
	} else {
		return INV_EVENT;
	}

	return OK;
}

ErrorCode parseRule(int* evtFlag, int* almFlag, Calendar* cal, char* inputLine){
	if(*evtFlag != 1 || *almFlag != 0){
		return INV_EVENT;
	}

	Property* tempProp = parseProp(inputLine);

	//Checks if the description is empty
	if(tempProp->propDescr[0] == '\0'){
		free(tempProp);
		return INV_EVENT;
	}

	insertSorted(&cal->event->properties, tempProp);

	return OK;
}

ErrorCode parseCat(int* evtFlag, int* almFlag, Calendar* cal, char* inputLine){
	if(*evtFlag != 1 || *almFlag != 0){
		return INV_EVENT;
	}

	Property* tempProp = parseProp(inputLine);

	//Checks if the description is empty
	if(tempProp->propDescr[0] == '\0'){
		free(tempProp);
		return INV_EVENT;
	}

	insertSorted(&cal->event->properties, tempProp);

	return OK;
}

ErrorCode parseCom(int* evtFlag, int* almFlag, Calendar* cal, char* inputLine){
	if(*evtFlag != 1 || *almFlag != 0){
		return INV_EVENT;
	}

	Property* tempProp = parseProp(inputLine);

	//Checks if the description is empty
	if(tempProp->propDescr[0] == '\0'){
		free(tempProp);
		return INV_EVENT;
	}

	insertSorted(&cal->event->properties, tempProp);

	return OK;
}

ErrorCode parseCon(int* evtFlag, int* almFlag, Calendar* cal, char* inputLine){
	if(*evtFlag != 1 || *almFlag != 0){
		return INV_EVENT;
	}

	Property* tempProp = parseProp(inputLine);

	//Checks if the description is empty
	if(tempProp->propDescr[0] == '\0'){
		free(tempProp);
		return INV_EVENT;
	}

	insertSorted(&cal->event->properties, tempProp);

	return OK;
}

ErrorCode parseExDt(int* evtFlag, int* almFlag, Calendar* cal, char* inputLine){
	if(*evtFlag != 1 || *almFlag != 0){
		return INV_EVENT;
	}

	Property* tempProp = parseProp(inputLine);

	//Checks if the description is empty
	if(tempProp->propDescr[0] == '\0'){
		free(tempProp);
		return INV_EVENT;
	}

	insertSorted(&cal->event->properties, tempProp);

	return OK;
}

ErrorCode parseRstat(int* evtFlag, int* almFlag, Calendar* cal, char* inputLine){
	if(*evtFlag != 1 || *almFlag != 0){
		return INV_EVENT;
	}

	Property* tempProp = parseProp(inputLine);

	//Checks if the description is empty
	if(tempProp->propDescr[0] == '\0'){
		free(tempProp);
		return INV_EVENT;
	}

	insertSorted(&cal->event->properties, tempProp);

	return OK;
}

ErrorCode parseRelt(int* evtFlag, int* almFlag, Calendar* cal, char* inputLine){
	if(*evtFlag != 1 || *almFlag != 0){
		return INV_EVENT;
	}

	Property* tempProp = parseProp(inputLine);

	//Checks if the description is empty
	if(tempProp->propDescr[0] == '\0'){
		free(tempProp);
		return INV_EVENT;
	}

	insertSorted(&cal->event->properties, tempProp);

	return OK;
}

ErrorCode parseReso(int* evtFlag, int* almFlag, Calendar* cal, char* inputLine){
	if(*evtFlag != 1 || *almFlag != 0){
		return INV_EVENT;
	}

	Property* tempProp = parseProp(inputLine);

	//Checks if the description is empty
	if(tempProp->propDescr[0] == '\0'){
		free(tempProp);
		return INV_EVENT;
	}

	insertSorted(&cal->event->properties, tempProp);

	return OK;
}

ErrorCode parseRdate(int* evtFlag, int* almFlag, Calendar* cal, char* inputLine){
	if(*evtFlag != 1 || *almFlag != 0){
		return INV_EVENT;
	}

	Property* tempProp = parseProp(inputLine);

	//Checks if the description is empty
	if(tempProp->propDescr[0] == '\0'){
		free(tempProp);
		return INV_EVENT;
	}

	insertSorted(&cal->event->properties, tempProp);

	return OK;
}

ErrorCode parseTrans(int* evtFlag, int* almFlag, int* transFlag, Calendar* cal, char* inputLine){
	if(*evtFlag != 1 || *almFlag != 0){
		return INV_EVENT;
	}

	Property* tempProp = parseProp(inputLine);

	//Checks if the description is empty
	if(tempProp->propDescr[0] == '\0'){
		free(tempProp);
		return INV_EVENT;
	}

	insertSorted(&cal->event->properties, tempProp);

	*transFlag = 1;
	return OK;
}

ErrorCode parseDTStr(int* evtFlag, int* dtStrFlag, int* dtendFlag, int* durFlag, Calendar* cal, char* inputLine){

	if(*evtFlag != 1 || *dtStrFlag != 0 || *dtendFlag != 0 || *durFlag != 0){
		return INV_EVENT;
	}

	Property* tempProp = parseProp(inputLine);

	//Checks if the description is empty
	if(tempProp->propDescr[0] == '\0'){
		free(tempProp);
		return INV_EVENT;
	}

	insertSorted(&cal->event->properties, tempProp);
	*dtStrFlag = 1;

	return OK;
}

ErrorCode parseDTend(int* evtFlag, int* dtStrFlag, int* dtendFlag, int* durFlag, Calendar* cal, char* inputLine){

	if(*evtFlag != 1 || *dtStrFlag != 1 || *dtendFlag != 0 || *durFlag != 0){
		return INV_EVENT;
	}

	Property* tempProp = parseProp(inputLine);

	//Checks if the description is empty
	if(tempProp->propDescr[0] == '\0'){
		free(tempProp);
		return INV_EVENT;
	}

	insertSorted(&cal->event->properties, tempProp);
	*dtendFlag = 1;

	return OK;
}

ErrorCode parseCalScl(int* strtFlag, int* calSclFlag, int* evtFlag, Calendar* cal, char* inputLine){
	if(*strtFlag != 1 || *calSclFlag != 0 || *evtFlag != 0){
		return INV_CAL;
	}

	Property* tempProp = parseProp(inputLine);

	//Checks if the description is empty
	if(tempProp->propDescr[0] == '\0'){
		free(tempProp);
		return INV_EVENT;
	}

	insertSorted(&cal->event->properties, tempProp);
	*calSclFlag = 1;

	return OK;
}

ErrorCode parseMeth(int* strtFlag, int* methFlag, int* evtFlag, Calendar* cal, char* inputLine){
	if(*strtFlag != 1 || *methFlag != 0 || *evtFlag != 0){
		return INV_CAL;
	}

	Property* tempProp = parseProp(inputLine);

	//Checks if the description is empty
	if(tempProp->propDescr[0] == '\0'){
		free(tempProp);
		return INV_EVENT;
	}

	insertSorted(&cal->event->properties, tempProp);
	*methFlag = 1;
	return OK;
}

ErrorCode parseRep(int* almFlag, int* repFlag, char* inputLine, Alarm* tempAlarm){
	if(*repFlag != 0 || *almFlag  < 1){
		return INV_EVENT;
	} 

	Property* tempProp = parseProp(inputLine);

	//Checks if the description is empty
	if(tempProp->propDescr[0] == '\0'){
		free(tempProp);
		return INV_EVENT;
	}

	insertSorted(&tempAlarm->properties, tempProp);
	return OK;
}

ErrorCode parseDur(int* evtFlag, int* almFlag, int* durFlag, int* durAlmFlag, int* dtStrFlag, int* dtendFlag, char* inputLine, Alarm* tempAlarm, Calendar* cal){
	if(*evtFlag != 1){
		return INV_EVENT;
	}

	Property* tempProp = parseProp(inputLine);

	//Checks if the description is empty
	if(tempProp->propDescr[0] == '\0'){
		free(tempProp);
		return INV_EVENT;
	}

	//DT START ASSUMPTION
	if (*almFlag == 0 && *durFlag != 1 && dtStrFlag != 0 && *dtendFlag != 1){
		//In event, tied to DTSTART
		insertSorted(&cal->event->properties, tempProp);
		*durFlag = 1;
	} else if(*almFlag != 0 && *durAlmFlag != 1){
		//In alarm
		insertSorted(&tempAlarm->properties, tempProp);
		*durAlmFlag = 1;
	} else {
		return INV_EVENT;
	}

	return OK;
}

ErrorCode parseAtd(int* evtFlag, int* almFlag, Calendar* cal, char* inputLine, Alarm* tempAlarm){
	if(*evtFlag != 1){
		return INV_EVENT;
	}

	Property* tempProp = parseProp(inputLine);

	//Checks if the description is empty
	if(tempProp->propDescr[0] == '\0'){
		free(tempProp);
		return INV_EVENT;
	}

	if(*almFlag < 1){
		insertSorted(&cal->event->properties, tempProp);

	} else if (*almFlag == 3){ //If Email ALARM
		insertSorted(&tempAlarm->properties, tempProp);	
	} else {
		return INV_EVENT;
	}

	return OK;
}

ErrorCode parseBegin(int* strtFlag, int* evtFlag, int* almFlag, char* inputLine){
	char* afterBegin;

	if(strtFlag == NULL || evtFlag == NULL || almFlag == NULL || inputLine == NULL){
		return INV_CAL;
	}

	if(inputLine[5] != ':'){
		return INV_CAL;
	}

	afterBegin = malloc(sizeof(char)*strlen(inputLine) + 1);

	strcpy(afterBegin, strchr(inputLine, ':') + 1);

	if(strcmp(afterBegin, "VCALENDAR") == 0){//Parses BEGIN:VALARM
		free(afterBegin);

		if(*strtFlag != 0){ //Repeated BEGIN:VCALENDAR
			return INV_CAL; 
		} else {
			*strtFlag = 1;
			return OK;
		}
	} else if(strcmp(afterBegin, "VEVENT") == 0){//Parses BEGIN:VEVENT
		free(afterBegin);

		if(*strtFlag != 1 || *evtFlag != 0){ //iCal havent been declared or BEGIN:EVENT already delcared
			return INV_CAL;
		} else {
			
			*evtFlag = 1;
			return OK;
		}
	} else if(strcmp(afterBegin, "VALARM") == 0){//Parses BEGIN:VALARM
		free(afterBegin);

		if(*evtFlag != 1 || *almFlag != 0){
			return INV_EVENT;
		} else {
			*almFlag = 1;
			return OK;	
		}
	} else {
		free(afterBegin);
		return INV_CAL;
	}
}

ErrorCode parseActAlm(int* almFlag, int* almActFlag, char* inputLine, Alarm* tempAlarm){
	if(*almFlag != 1 || *almActFlag != 0){
		return INV_EVENT;
	}

	char* spareColon;
	char* spareSemi;
	char* tokenColon;
	char* tokenSemi;

	spareColon = malloc(sizeof(char)*strlen(inputLine) + 1);
	spareSemi = malloc(sizeof(char)*strlen(inputLine) + 1);

	strcpy(spareColon, inputLine);
	strcpy(spareSemi, inputLine);

	tokenColon = strtok(spareColon, ":");
	tokenSemi = strtok(spareSemi, ";");

	//To see if the ACTION has param values seperated from a semicolon or a colon
	if(strlen(tokenColon) < strlen(tokenSemi)){
		strcpy(tempAlarm->action, strchr(inputLine, ':') + 1);

	} else if (strlen(tokenColon) > strlen(tokenSemi)){
		strcpy(tempAlarm->action, strchr(inputLine, ';') + 1);
	}

	free(spareColon);
	free(spareSemi);

	//Changes almFlag so other functions know which action it corsponds to
	if(strcmp(tempAlarm->action, "AUDIO") == 0){
		*almFlag = 1;
	} else if (strcmp(tempAlarm->action ,"DISPLAY") == 0){
		*almFlag = 2;
	} else if (strcmp(tempAlarm->action, "EMAIL") == 0){
		*almFlag = 3;
	} else {
		return INV_EVENT;
	}

	*almActFlag = 1;
	return OK;
}

ErrorCode parseTrigAlm(int* almFlag, int* almTrigFlag, char* inputLine, Alarm* tempAlarm){
	if(*almFlag != 1 || *almTrigFlag != 0){
		return INV_EVENT;
	}

	char* spareColon;
	char* spareSemi;
	char* tokenColon;
	char* tokenSemi;
	int len;

	spareColon = malloc(sizeof(char)*strlen(inputLine) + 1);
	spareSemi = malloc(sizeof(char)*strlen(inputLine) + 1);

	strcpy(spareColon, inputLine);
	strcpy(spareSemi, inputLine);

	tokenColon = strtok(spareColon, ":");
	tokenSemi = strtok(spareSemi, ";");

	//To see if the TRIG has param values seperated from a semicolon or a colon
	if(strlen(tokenColon) < strlen(tokenSemi)){
		//Allocating memory for tempTrig since it is a pointer
		len = strlen(strchr(inputLine, ':'));
		tempAlarm->trigger = malloc(sizeof(char) * len);

		strcpy(tempAlarm->trigger, strchr(inputLine, ':') + 1);

	} else if (strlen(tokenColon) > strlen(tokenSemi)){
		len = strlen(strchr(inputLine, ';'));
		tempAlarm->trigger = malloc(sizeof(char) * len);

		strcpy(tempAlarm->trigger, strchr(inputLine, ';') + 1);
	}

	free(spareColon);
	free(spareSemi);

	*almTrigFlag = 1;
	return OK;
}

ErrorCode parseEnd(char* inputLine, int* strtFlag, int* prodFlag, int* verFlag, int*evtNum, int* methFlag, int* evtFlag, int* UIDFlag, int* clasFlag, int* createdFlag, int* decrFlag, int* dtStrFlag, int* geoFlag, int* lstModFlag, int* locFlag, int* orgFlag, int* prioFlag, int* dtStmpFlag, int* seqFlag, int* statFlag, int* sumFlag, int* transFlag, int* URLFlag, int* recIDFlag, int* dtendFlag, int* attFlag, int* almFlag, int* almActFlag, int* almTrigFlag, int* repFlag, int* durFlag, int* durAlmFlag, int* decrAlmFlag, int* sumAlmFlag, Calendar* cal, Alarm* tempAlarm){

	char* afterEnd;

	if(inputLine[3] != ':'){
		return INV_CAL;
	}
	afterEnd = malloc(sizeof(char)*strlen(inputLine) + 1);
	strcpy(afterEnd, strchr(inputLine, ':') + 1);

	//CAL

	if(strcmp(afterEnd,"VCALENDAR") == 0){ //END:VCALENDAR
		free(afterEnd);

		if(*strtFlag != 1 || *prodFlag != 1 || *verFlag != 1 || *evtNum != 1){
			return INV_CAL;
		}
		*strtFlag = 0;
		*prodFlag = 0;
		*verFlag  = 0;
		return OK;

	} else if(strcmp(afterEnd,"VEVENT") == 0){ //END:VEVENT
		free(afterEnd);

		if(*evtFlag != 1 || *almFlag != 0 || *dtStmpFlag != 1 || *UIDFlag != 1){
			return INV_EVENT;
		}

		//If method is not in iCal, check for DTSTART, if that isnt declared, invalid cal
		if(*methFlag != 1){
			if(*dtStrFlag != 1){
				return INV_EVENT;
			}
		}

		//If DTEND and DURATION declared in the same event
		if(*dtendFlag != 0 && *durFlag != 0){
			return INV_EVENT;
		}

		//All event flags set to 0 for possible next event
		*evtFlag     = 0;
		*UIDFlag     = 0;
		*clasFlag    = 0;
		*createdFlag = 0;
		*decrFlag    = 0;
		*dtStrFlag   = 0;
		*dtStmpFlag  = 0;
		*geoFlag     = 0;
		*lstModFlag  = 0;
		*locFlag     = 0;
		*orgFlag     = 0;
		*prioFlag    = 0;
		*seqFlag     = 0;
		*statFlag    = 0;
		*sumFlag     = 0;
		*transFlag   = 0;
		*URLFlag     = 0;
		*recIDFlag   = 0;
		*dtendFlag   = 0;
		*durFlag     = 0;
		*repFlag     = 0;
		*attFlag     = 0;

		//Increase the number of events
		*evtNum += 1;

	} else if(strcmp(afterEnd,"VALARM") == 0){ //END:VALARM
		free(afterEnd);

		if(*almFlag < 1 || *almActFlag != 1 || *almTrigFlag != 1){
			return INV_EVENT;
		}

		//Checks to see that both REPEAT and DURATION have been delcared
		if((*repFlag == 1 && *durFlag != 1) || (*repFlag != 1 && *durFlag == 1)){
			return INV_EVENT;
		}

		insertSorted(&cal->event->alarms, tempAlarm);

		//Resets flags for next alarm
		*almFlag     = 0;
		*almActFlag  = 0;
		*almTrigFlag = 0;
		*durAlmFlag  = 0;
		*repFlag     = 0;
		*decrAlmFlag = 0;
		*sumAlmFlag  = 0;
		return OK;

	} else{
		free(afterEnd);
		return INV_CAL;
	}

	return OK;
}

void deleteCalendar(Calendar* obj){

	if(obj == NULL){
		return;
	}

	clearList(&obj->event->alarms);
	clearList(&obj->event->properties);
	free(obj->event);
	free(obj);
}

char* printCalendar(const Calendar* obj){

	char* tempStr;
	char* propListStr;
	char* almListStr;
	char* utcStr;
	int len;
	
	if (obj == NULL){
		return NULL;
	}

	propListStr = toString(obj->event->properties);
	almListStr = toString(obj->event->alarms);


	if(propListStr == NULL || almListStr == NULL){
		return NULL;
	}

	//The length of all the components of the Calendar object
	len = 100+ strlen(obj->prodID) + strlen(obj->event->UID) + strlen(obj->event->creationDateTime.date) + strlen(obj->event->creationDateTime.time) + strlen(propListStr) + strlen(almListStr);


	tempStr = (char*)malloc(sizeof(char)*len);
	
	if(tempStr == NULL){
		return NULL;
	}

	if(obj->event->creationDateTime.UTC == true){
		utcStr = malloc(sizeof(char)* 5);
		strcpy(utcStr, "true");
	} else {
		utcStr = malloc(sizeof(char)* 6);
		strcpy(utcStr, "false");
	}

	sprintf(tempStr, "iCalendar\nVerion: %f\nProdID: %s\n\nEVENT:\nUID: %s\nDate:%s\nTime:%s\nUTC:%s\n%s\n\n%s", obj->version, obj->prodID, obj->event->UID, obj->event->creationDateTime.date, obj->event->creationDateTime.time, utcStr, propListStr, almListStr);

	free(utcStr);

	return tempStr;
}

char* printError(ErrorCode err){

	char* retStr;

	switch(err){
		case INV_FILE:
		retStr = malloc(sizeof(char)* 161);
		strcpy(retStr, "There was a problem with the file argument - its null, it;’s a empty string, file doesn't exist or cannot be opened, file doesn't have the .ics extension, etc.\n");
		break;

		case INV_CAL:
		retStr = malloc(sizeof(char)* 113);
		strcpy(retStr, "The calendar itself is invalid (missing required properties or components, invalid opening/closing tags, etc.).\n");
		break;

		case INV_VER:
		retStr = malloc(sizeof(char)* 57);
		strcpy(retStr, "The calendar version property is present but malformed.\n");
		break;

		case DUP_VER:
		retStr = malloc(sizeof(char)* 55);
		strcpy(retStr, "The calendar version property appears more than once.\n");
		break;

		case INV_PRODID:
		retStr = malloc(sizeof(char)* 51);
		strcpy(retStr, "The product ID property is present but malformed.\n");
		break;

		case DUP_PRODID:
		retStr = malloc(sizeof(char)* 58);
		strcpy(retStr, "The calendar product ID property appears more than once.\n");
		break;

		case INV_EVENT:
		retStr = malloc(sizeof(char)* 47);
		strcpy(retStr, "The event component is malformed in some way.\n");
		break;

		case INV_CREATEDT:
		retStr = malloc(sizeof(char)* 65);
		strcpy(retStr, "The event creation date-time property is malformed in some way.\n");
		break;

		case OK:
		retStr = malloc(sizeof(char)* 12);
		strcpy(retStr, "No errors.\n");
		break;

		case OTHER_ERROR:
		retStr = malloc(sizeof(char)* 33);
		strcpy(retStr, "Something went wrong in memory.\n");
		break;

		default:
		retStr = malloc(sizeof(char)* 26);
		strcpy(retStr, "Invalid ErrorCode passed\n");
	}
	return retStr;
}

int main(){

	char* str;
	Calendar** cal;

	cal = malloc(sizeof(Calendar));

	str = printError(createCalendar("test.ics", cal));
	printf("%s", str);

	//deleteCalendar(*cal);
	//printf("%s", printCalendar(*cal));
	deleteCalendar(*cal);	

	
	free((cal));
	free(str);
	return 0;
}