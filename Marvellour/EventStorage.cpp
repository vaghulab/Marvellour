//Class : EventStorage
//This is the class which stores the data entered by the user
//The data is stored in the appropriate variables after it is checked for errors

#include "EventStorage.h"

void EventStorage::storeUserInput(vector<string> userInput, int doneFlag)
{
	storeTitle(userInput[0]);
	storeDate(userInput[1]);
	storeTime(userInput[2]);
	storePriority(userInput[3]);
	storeCode(userInput[4]);
	storeDoneFlag(doneFlag);
}

void EventStorage::storeTitle(string userInput)
{
	eventTitle = userInput;
}

void EventStorage::storeDate(string userInput)
{
	eventDate = userInput;
}

void EventStorage::storeTime(string userInput)
{
	eventTime = userInput;
}

void EventStorage::storePriority(string userInput)
{
	eventPriority = userInput;
}

void EventStorage::storeCode(string userInput)
{
	eventCode = userInput;
}

void EventStorage::storeDoneFlag(int tempDoneFlag)
{
	eventDoneFlag = tempDoneFlag;
}

string EventStorage::getTitle()
{
	return eventTitle;
}

string EventStorage::getDate()
{
	return eventDate;
}

int EventStorage::getDay()
{ 
	return((eventDate[1] - 48) + (eventDate[0] - 48) * 10);
}

int EventStorage::getMonth()
{ 
	return((eventDate[4] - 48) + (eventDate[3] - 48) * 10);
}

int EventStorage::getYear()
{ 
	return((eventDate[9] - 48) + (eventDate[8] - 48) * 10 + (eventDate[7] - 48) * 100 + (eventDate[6] - 48) * 1000);
}

string EventStorage::getTime()
{
	return eventTime;
}

string EventStorage::getPriority()
{
	return eventPriority;
}

string EventStorage::getCode()
{
	return eventCode;
}

int EventStorage::getDoneFlag()
{
	return eventDoneFlag;
}

void EventStorage::writeTitle(string tempTitle)
{
	eventTitle = tempTitle;
}

void EventStorage::writeDate(string tempDate)
{
	eventDate = tempDate;
}

void EventStorage::writeTime(string tempTime)
{
	eventTime = tempTime;
}

void EventStorage::writePriority(string tempPriority)
{
	eventPriority = tempPriority;
}

void EventStorage::writeDoneFlag()
{
	eventDoneFlag = 1;
}

void EventStorage::displayEvent()
{
	if(eventTitle.size()!=0)
		cout << "\nTitle : " << eventTitle << "\n";
	if(eventDate!="00-00-0000")
	cout << "Date : " << eventDate << "\n";
	if(eventTime!="25:00")
	cout << "Time : " << eventTime << "\n";
	cout << "Priority : ";
	if(eventPriority[0] == '1')
		cout << "High\n";
	else
		if(eventPriority[0] == '2')
			cout << "Normal\n";
	cout << "Event Code : " << eventCode << "\n";
}