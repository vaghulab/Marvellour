//Main Author : Abhinav Deshmukh (A0074722H)
//This consists of all functions made use of by the ErrorHandling class for processing the date and time. Date and time are received in a raw format
//by the error handling class and they are refined and converted to a pre-defined format by the error handling class using the methods defined 
//in this class. It can handle inputs like "nxt wed", feb 11th, as well as mmddyyyy and ddmmyyyy with preference given to ddmmyyyy.

#include "TimeDates.h"

string const static monthName[] = {"jan", "feb", "mar", "apr", "may", "jun", "jul", "aug", "sep", "oct", "nov", "dec"};
string const static monthNumber[] = {"01","02","03","04","05","06","07","08","09","10","11","12"};
string const static dayName[] = {"sun","mon","tue","wed","thu","fri","sat"};
string const static keyword[] = {"nextday","nextweek","nextwk","next","coming","following","tomorrow", "tmr","tmrw","tml","cmg","cmng","nxtday","nxtwk","nxt","flwg","fllng", "today","tdy","tdd"};
int const static dayNumber[] = {0,1,2,3,4,5,6};
string const static DEFAULT_DATE = "00-00-0000";
string const static DEFAULT_TIME = "25:00";
string static const  YEAR_PREFIX = "20";
char const static DATE_SEPARATOR = '-';
char const static TIME_SEPARATOR = ':';

static  int  DEFAULT_DAY = 00;
static  int  DEFAULT_MONTH = 00;
static int  DEFAULT_YEAR = 0000;
static const int BASE_YEAR = 1900;
static const int DDMM_LENGTH = 4;
static const int DDMMYYYY_LENGTH = 8;
static const int DDMMYY_LENGTH = 6;
static const int ARRAY_SIZE = 12;
static const int ARRAY_SIZE_WEEKDAY = 7;
static const int ARRAY_SIZE_KEYWORD = 20;
static const int MAX_MONTH_DAY = 31;
static const int MIN_MONTH_DAY = 1;
static const int MAX_MONTH = 12;
static const int MIN_MONTH = 1;
static const int INVALID_TIME_2 = 2359;


/*assertions macros. credits: http://www-subatech.in2p3.fr/~photons/subatech/soft/carnac/CPP-DEB-2.shtml */
#define ASSERTMSG(TST,MSG)					\
	( (TST) ? (void)0				\
	: (cerr << __FILE__ "(" << __LINE__	\
	<< "): Assertion failed " #TST	\
	<< MSG << endl,abort()))
#define PRECONDITION(TST,MSG) ASSERTMSG(TST,"Precondition " << MSG)
#ifndef NDEBUG
#  define POSTCONDITION(TST,MSG) ASSERTMSG(TST,"Postcondition " << MSG)
#  define INVARIANT(TST,MSG) ASSERTMSG(TST,"Invariant " << MSG)
#else
#  define POSTCONDITION(TST,MSG) ((void)0)
#  define INVARIANT(TST,MSG) ((void)0)
#endif


int TimeDates::getDate(){
	return day;
}

int TimeDates::getMonth(){
	return month;
}

int TimeDates::getYear(){
	return year;
}

void TimeDates::setDate(int date){
	day=date;    
}

void TimeDates::setMonth(int mth){
	month  = mth;
}

void TimeDates::setYear(int yr){
	year = yr;
}

bool TimeDates::isDateFieldEmpty(string& date){
	if(date == ""){
		//cout << "Date field is empty" <<endl;
		date =  DEFAULT_DATE;
		return true;
	}
	return false;
}

string TimeDates::retainCharOrDigitInput(string input){	
	string newInput = "";
	for(int i = 0; i < (int) input.length(); i++){
		if ( isdigit(input[i]) || isalpha(input[i]))
			newInput += input[i];
	}
	return newInput;
}

//This function will convert 11 Aug to 1108
bool TimeDates::monthNameToNumber(string& input, string& month){
	size_t found;
	bool flag = false;
	std::string lowerCase (input);
	toLowerCase(lowerCase);
	for(int i = 0; i < ARRAY_SIZE; i++){
		found = lowerCase.find(monthName[i]);
		if(found != string::npos){
			flag = true;
			lowerCase.replace(lowerCase.find(monthName[i]),monthName[i].length(),monthNumber[i]);
			input = lowerCase;
			month = monthNumber[i];
			return true;
		}
	}
	return false;
}

string TimeDates :: removeAllAlpha(string& input){
	string newInput = "";
	for(int i = 0 ;i < (int) input.length(); i++){
		if(!isalpha(input[i]))
			newInput += input[i];
	}
	return newInput;
}

string TimeDates :: removeAllSpaces(string& time){
	string newInput = "";
	for(int i = 0 ;i < (int) time.length(); i++){
		if(time[i] != ' ')
			newInput += time[i];
	}
	return newInput;
}


bool TimeDates :: isCorrectDateLength(string date){
	if(date.length() != DDMMYYYY_LENGTH && date.length() != DDMM_LENGTH && date.length() != DDMMYY_LENGTH){
		cout << "Error in format. ddmmyyyy/ddmmyy"<<endl;
		return false;
	}
	else
		return true;
}

/* This function captures the current year from the system clock*/
int extractYearFromSystem()
{
	time_t rawtime;
	struct tm * timeinfo;
	time ( &rawtime );
	timeinfo = localtime ( &rawtime );
	return  timeinfo -> tm_year + BASE_YEAR;
}

int extractMonthFromSystem()
{
	time_t rawtime;
	struct tm * timeinfo;
	time ( &rawtime );
	timeinfo = localtime ( &rawtime );
	return  timeinfo -> tm_mon + 1;
}

int extractDayFromSystem()
{
	time_t rawtime;
	struct tm * timeinfo;
	time ( &rawtime );
	timeinfo = localtime ( &rawtime );
	return  timeinfo->tm_mday;
}

int extractNumberOfDaysFromSunday()
{
	time_t rawtime;
	struct tm * timeinfo;
	time ( &rawtime );
	timeinfo = localtime ( &rawtime );
	return  timeinfo->tm_wday;
}

string TimeDates::convertIntegerToString(int integer){
	std::stringstream ss;
	ss << integer;
	return ss.str();
}

int TimeDates::convertTo4DigitTimeFormat(string& timeDigit)
{

	//PRECONDITION(timeDigit.length() < 5,"Invalid length of time");
	if(timeDigit.length() == 1 || timeDigit.length() == 2)
	{
		timeDigit += "00";
	}
	else if(timeDigit.length() == 3)
		timeDigit = '0' + timeDigit;
	int digittime = atoi (timeDigit.c_str());
	//POSTCONDITION(timeDigit.length() != 4 ,"conversion to 4 digit improper");
	return digittime;
}

//This function determines no. of dys from current date to "next Wednesday"
string TimeDates::convertingNextToDay(string& input, int& dday, int& mday, int& yday, string keyword1)
{
	size_t found;int noOfLoops = 0;int noOfDays = extractNumberOfDaysFromSunday();string date, month, year;
	//INVARIANT(noOfDays >= 0 && noOfDays <= 6,"Exceeding range of number of days when converting");
	bool flag = false;
	std::string lowerCase (input);
	toLowerCase(lowerCase);
	for(int i = 0; i < ARRAY_SIZE_WEEKDAY; i++){
		found = lowerCase.find (dayName[i]);
		if(found != string::npos || keyword1 == "tomorrow" || keyword1 == "day-after"||keyword1 == "tmrw" || keyword1 == "tmw" || keyword1 == "tmr" || keyword1 == "tdy" || keyword1 == "today" || keyword1 == "tdd"|| keyword1 == "nextday"|| keyword1 == "nxtday" || keyword1 == "nextwk" || keyword1 == "nextweek" || keyword1 == "nxtwk" ){
			flag = true;
			if(keyword1 == "today" || keyword1 == "tdd" || keyword1 == "tdy")
				noOfLoops = 0;
			else if(keyword1 == "coming" || keyword1 == "cmg" || keyword1 == "cmng" || keyword1 == "following"||keyword1 == "flwg" || keyword1 == "fllng"|| keyword1 == "next" || keyword1 == "nxt")
				if((i-noOfDays) > 0)
					noOfLoops = i - noOfDays	;
				else
					noOfLoops = i - noOfDays +7;
			else if (keyword1 == "tomorrow" || keyword1 == "tmrw" || keyword1 == "tmr" || keyword1 == "nextday" || keyword1 == "nxtday")
				noOfLoops = 1;
			else if (keyword1 == "nxtwk" || keyword1 == "nextweek" || keyword1 == "nextwk")
				noOfLoops = 7;
			dday = extractDayFromSystem();
			mday = extractMonthFromSystem();
			yday = extractYearFromSystem();
			for( int i = 0; i < noOfLoops; i++)
				generateNextDay(dday, mday, yday);
			date = convertIntegerToString(dday);
			month = convertIntegerToString(mday);
			if(date.length() == 1)
				date = '0'+ date;
			if(month.length() == 1)
				month = '0' + month;

			input = date + month + convertIntegerToString(yday);
			//	POSTCONDITION(input.length() == 8,"Day not successfully converted to date");
			break;
		}
	}
	return input;
}

bool TimeDates::isKeywordThere(string& input, string& keyword1)
{

	size_t found;int i;
	std::string lowerCase (input);
	toLowerCase(lowerCase);
	for( i = 0; i < ARRAY_SIZE_KEYWORD; i++){
		found = lowerCase.find(keyword[i]);
		if(found != string::npos){
			keyword1 = keyword[i];
			convertingNextToDay (input, DEFAULT_DAY, DEFAULT_MONTH, DEFAULT_YEAR, keyword1);
			return true;
		}
	}
}


void TimeDates::generateNextDay(int& today, int& month, int& year)
{

	int tomorrow = today + 1;
	if((today >= 28) && (month == 2))
	{
		if((year % 400 == 0) || ((year % 4 == 0) && (year % 100 != 0)))
		{
			switch(today)
			{
			case 28 : 
				tomorrow = 29;
				break;

			case 29 : 
				tomorrow = 1;
				month++;
				break;
			}
		}
		else
		{
			switch(today)
			{
			case 28 : 
				tomorrow = 1;
				month++;
				break;
			}
		}
	}
	else if((today >= 30) && (month != 12))
	{
		if((month == 1) || (month == 3) || (month == 5) || (month == 7) || (month == 8) || (month == 10))
		{
			switch(today)
			{
			case 30 : 
				tomorrow = 31;
				break;

			case 31 : 
				tomorrow = 1;
				month++;
				break;
			}
		}
		else
		{
			switch(today)
			{
			case 30 : 
				tomorrow = 1;
				month++;
				break;
			}
		}
	}
	else if((today == 31) && (month == 12))
	{
		tomorrow = 1;
		year++;
		month = 1;
	}

	today = tomorrow;
}

//This function inserts a year if not present in date
string TimeDates::insertYear(string &date, string &year){
	//PRECONDITION(date.length() <= 8,"Incorrect length");	
	if (date.length() == DDMM_LENGTH)
	{
		year = convertIntegerToString(extractYearFromSystem());
		date += year;
	}
	else if (date.length() == DDMMYY_LENGTH)
		date = (date.substr(0,4) + YEAR_PREFIX + date.substr(4,5));
	return date;
}

void TimeDates::initialiseValues(int& dd, int& mm, int& yyyy){
	dd = getDate();
	mm = getMonth();
	yyyy = getYear();
}

void TimeDates::extractDate(string date){
	//PRECONDITION(date.length() == 8,"Invalid date length");
	//conver string to long int

	char dateChar[8];
	for(int i = 0;i < DDMMYYYY_LENGTH; i++){
		dateChar[i] = date[i];
	}
	char dateDay[2];
	dateDay[0] = date[0]; dateDay[1] = date[1];

	long int dateint = atol(dateChar);

	//now write to date
	setYear (dateint % 10000);
	setMonth ((dateint % 1000000 - getYear())/10000);
	setDate (atol(dateDay));
}

string TimeDates:: checkForInversion (string date, string month)
{	
	if(!(date == ""))
	{
		string dateFirst = date.substr(0,2);
		if(dateFirst == month)
			invertDateFormat(date);
	}
	return date;
}


bool TimeDates::isLeapYear(int year){
	//PRECONDITION( year >= 1000,"4 digit year input not maintained");
	try{
		if(year % 400 == 0 || (year % 100 != 0 && year % 4 == 0))

			return true;

		else
			return false;
	}
	catch(exception& e){
		cout << "Integer input not received," << e.what() << endl;}
}

bool TimeDates::isLegalDate(int& dd, int& mm, int& yyyy, bool monthName1, int count)
{

	int temp = 0;
	if( count == 0)
		initialiseValues(dd, mm, yyyy);
	else
		initialiseValues(mm, dd, yyyy);
	//PRECONDITION(yyyy >= 1000 , "4 digit year not obtained in isLegalDate");
	bool legal = true;
	try{
		if(dd > MAX_MONTH_DAY || dd < MIN_MONTH_DAY){
			legal = false;
			if(monthName1)
				throw( "Invalid date entry");
		}

		if(mm > MAX_MONTH || mm < MIN_MONTH){
			legal = false;
			if(monthName1)
				throw ("Invalid month entry");

		}
		else if((mm == 1 || mm == 3 || mm == 5 || mm == 7 || mm == 8 || mm == 10 || mm == 12) && dd>31){
			legal = false;
			if(monthName1)
				throw (mm-1);
		}
		//check for 30-dd months
		else if((mm == 4 || mm == 6 || mm == 9 || mm == 11) && dd > 30){
			legal = false;
			if(monthName1)
				throw (mm-1);
		}
		//check for leap year in february
		else if(mm == 2 &&  dd > 29 && isLeapYear(yyyy)){
			legal = false;
			if(monthName1)
				throw( "February in a leap year has maximum 29 days" );
		}
		else if(mm == 2 && dd > 28 && !isLeapYear(yyyy)){
			legal = false;
			if(monthName1)
				throw( "February has 28 days in a non-leap yyyy" );	
		}
	}
	catch(char *str){
		cout << str << endl;
	}
	catch(int e){
		cout << "days exceed maximum number of days in " << monthName[e] << endl;
	}
	return legal;
}

void TimeDates::invertDateFormat(string& dateOriginal){
	//PRECONDITION(dateOriginal.length() == 8,"ddmmyyyy/mmddyyyy is need for successful inversion");
	string dateFinal;
	if(dateOriginal.length() == 3 || dateOriginal.length() == 5 || dateOriginal.length() == 7)
		dateOriginal = dateOriginal.substr(0,2) + '0' + dateOriginal.substr(2);

	dateFinal = dateOriginal;
	dateFinal[3] = dateOriginal[1];
	dateFinal[2] = dateOriginal[0];
	dateFinal[1] = dateOriginal[3];
	dateFinal[0] = dateOriginal[2];
	dateOriginal = dateFinal;
}

void TimeDates::isDateLegalInEitherMonthFirstOrDateFirstFormat (string& date, bool& isValid, bool monthName){
	int temp, count = 0; 
	try{
		if(! isLegalDate (DEFAULT_DAY,DEFAULT_MONTH,DEFAULT_YEAR, monthName, count)){
			count++; isValid = false;
			if(count == 1 && !monthName)
				if(!isLegalDate(DEFAULT_DAY,DEFAULT_MONTH,DEFAULT_YEAR, 1, count)){
					isValid = false;
					throw( "This date does not lie on the calender. Please revise");

				}
				else if(!monthName)
					invertDateFormat(date);
		}
	}
	catch(char *str){
		cout << str << endl;
	}
	if(isValid)
		hasDatePassed (DEFAULT_DAY, DEFAULT_MONTH, DEFAULT_YEAR);
}


//Checks whether date has already occurred
bool TimeDates::hasDatePassed(int dd, int mm, int yyyy){
	initialiseValues (dd,mm,yyyy);
	time_t rawtime;
	struct tm * timeinfo;
	time ( &rawtime );
	timeinfo = localtime ( &rawtime );
	int year = extractYearFromSystem();
	if((yyyy*1000 + mm*10 + dd) < (extractYearFromSystem() * 1000 + extractMonthFromSystem() * 10 + extractDayFromSystem()) && yyyy != 0 ){
		cout << "\nWARNING :The date has already gone by" << endl;
		return true;
	}
	return false;
}

void TimeDates::toLowerCase(std::string& date){
	std::transform (date.begin(), date.end(), date.begin(), std::tolower);
}


void TimeDates::convertDateToOutputFormat( string& date){
	//PRECONDITION(date.length() == 8, "Input format of ddmmyyyy not followed");
	string tempStoreDate = date;
	date = "";

	for(unsigned i = 0; i < tempStoreDate.length(); i++){
		if(i % 2 == 0 && i != 0 && i != 6){
			date += DATE_SEPARATOR;
			date += tempStoreDate[i];
		}
		else
			date += tempStoreDate[i];
	}
	//POSTCONDITION(date.length() == 10, "Final format incorrect");
}


void TimeDates::convertTimeToOutputFormat(string timeword, string timedigit, string& time){
	time  = "";
	for(unsigned i = 0; i < timedigit.length(); i++){
		if( i % 2 == 0 && i != 0){
			time += TIME_SEPARATOR;
			time += timedigit[i];
		}
		else
			time += timedigit[i];
	}
	time += ' '+timeword;
}

/*Function handling empty time field*/
bool TimeDates::isTimeEmpty(string& time){
	if (time == ""){
		time = DEFAULT_TIME;
		return true;
	}
	return false;
}

bool TimeDates::isTimeInDigits (string time){
	for(int i = 0; i < (int) time.length(); i++){
		if (!isdigit (time[i]))
			return false;
	}
	return true;
}

int TimeDates::extractTime (string time){
	char timeChar[4];
	for (int i = 0; i < 4; i++){
		timeChar[i] = time[i];
	}
	int timeint = atol (timeChar);
	return timeint;
}

void TimeDates::separateDigitFromWord (string& timeDigit, string& timeword, string time){
	for(int i = 0; i < time.length(); i++)
	{
		if(isdigit (time[i]))
			timeDigit += time[i];
		else
			timeword += time[i];
	}
}

void TimeDates::convertTo12HrFormat (string& timeword, int& digittime){
	bool check24hrFormat = false;bool flag = true;
	if(digittime > 1259){
		digittime -= 1200;
		check24hrFormat = true;
	}
	if(digittime < 60){
		digittime += 1200; flag= false;}
	if (check24hrFormat && timeword != "am" && timeword != "pm")
		timeword = "pm";
	else if (digittime >= 1200 && digittime <=1259 && flag && timeword != "am" && timeword != "pm")
		timeword = "pm";
	else if(!check24hrFormat && timeword != "am" && timeword != "pm"){
		timeword = "am";
	}
}

bool TimeDates::isTimeValid(string time, int digittime){
	bool isCorrectTime = true;
	if(time[0] < '0' ||time[0] > '2'|| time[1] <'0'  || time[3] < '0' || time[3] > '5' || time[4] < '0' || digittime > INVALID_TIME_2)
		isCorrectTime = false;

	if(time[0] != '0' && time[1] > '2')
		isCorrectTime = false;

	if(!isCorrectTime)
		cout << "invalid entry" << endl;
	return isCorrectTime;
}





