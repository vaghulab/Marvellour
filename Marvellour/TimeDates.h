//Main Author : Abhinav Deshmukh (A0074722H)
//This is the header file for the TimeDates class. It contains the declarations of all functions used for manipulating the time or date input.

#ifndef TIMEDATES_H
#define TIMEDATES_H

#include "HeaderFiles.h"

class TimeDates
{
private:
	int day;
	int month;
	int year;
   

public:
	int getDate();
	int getMonth();
	int getYear();

	void setDate(int date);
	void setMonth(int mth);
	void setYear(int yr);

	/*Date function*/
	bool isDateFieldEmpty(string&);
	string retainCharOrDigitInput(string date);
	bool monthNameToNumber(string& input, string &month);
	string removeAllAlpha(string &date);
	string removeAllSpaces(string &time);
	bool isCorrectDateLength(string date);
	string convertIntegerToString(int integer);
	int convertTo4DigitTimeFormat(string& timeinput);
	string convertingNextToDay(string& input,int& dday, int& mday, int& yday, string keyword);
	bool isKeywordThere(string& input, string& keyword);
	void generateNextDay(int& day, int& month, int& year);
	string insertYear (string& date, string& year);
	void initialiseValues(int& dd, int& mm, int& yyyy);
	void extractDate(string);
	string checkForInversion (string, string);
	bool isLeapYear (int year);
	bool isLegalDate (int& dd, int& mm, int& yyyy, bool, int);
	void invertDateFormat (string& dateOriginal);
	void isDateLegalInEitherMonthFirstOrDateFirstFormat (string&, bool&, bool);
	bool hasDatePassed (int dd, int mm, int yyyy);
	void toLowerCase (std::string&);
	void convertDateToOutputFormat (string& date);
	
	/*Time function*/
	void convertTimeToOutputFormat (string timeword, string timedigit, string& time);
	bool isTimeEmpty (string&);
	bool isTimeInDigits (string date);
	int extractTime (string input);
	void separateDigitFromWord (string&, string&, string);
	void convertTo12HrFormat (string&, int&);
	bool isTimeValid (string, int);
};


#endif