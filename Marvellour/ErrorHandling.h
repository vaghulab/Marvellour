//Main Author :  ABHINAV DESHMUKH (A0074722H) and RAVI THEJA REDDY SINGANNAGARI (A0074598L)
#ifndef ERROR_HANDLING_H
#define ERROR_HANDLING_H

#include "HeaderFiles.h"
#include "TimeDates.h"

class ErrorHandling
{
public:	
	int checkInt(string);
	bool checkAddInput(vector<string>&);
	bool checkSearchInput(vector<string>);
	bool checkEditInput(string);
	bool checkDate(string&);
	bool checkTime(string&);
	void changeToLower(string&);
};
#endif