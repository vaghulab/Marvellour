//Main Authors : Vaghul Aditya Balaji (A0074270L) & Madhu Maithri Parvataneni (A0074807Y)
//This is the header file for the EventStorage class. It contains the declarations of all functions used for accessing the data stored 
//in the event variables.

#ifndef EVENTSTORAGE_H
#define EVENTSTORAGE_H

#include "HeaderFiles.h"
#include "TimeDates.h"

class EventStorage
{	
private:
	string eventTitle;
	string eventDate;
	string eventTime;
	string eventPriority;
	string eventCode;
	int eventDoneFlag;

public:    
	void storeUserInput(vector<string>, int);
	void storeTitle(string);	
	void storeDate(string);
	void storeTime(string);   
    void storePriority(string);
	void storeCode(string);
	void storeDoneFlag(int);

	string getTitle();
	string getDate();
	int getDay();
	int getMonth();
	int getYear();
	string getTime();
	string getPriority();
	string getCode();
	int getDoneFlag();

	void writeTitle(string);
	void writeDate(string);
	void writeTime(string);
	void writePriority(string);
	void writeDoneFlag();

	void displayEvent();	
};

#endif