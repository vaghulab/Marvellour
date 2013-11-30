//Main Author :  ABHINAV DESHMUKH (A0074722H) and RAVI THEJA REDDY SINGANNAGARI (A0074598L)
#include "ErrorHandling.h"

static int  DEFAULT_DAY = 00;
static int  DEFAULT_MONTH = 00;
static int  DEFAULT_YEAR = 0000;
static int INVALID_TIME_1 = 0000;
static int INVALID_TIME_2 = 2359;
static string DEFAULT_DATE = "00-00-0000";

void performLogging(string);

int ErrorHandling::checkInt(string input)
{
	int number = atoi(input.c_str());
	return number;
}

bool ErrorHandling::checkAddInput(vector<string>& input)
{	
	bool value = true;
	
	int inputNotGiven = 0;
	for(int counter = 0; counter < input.size() - 1; counter++)
	{
		if(input[counter] == "")
				++inputNotGiven;
	}
			
	if(inputNotGiven == 3)
	{
		cout << "\nInvalid input as no event detail has been mentioned.\n"; 
		performLogging("Invalid input as no event detail has been mentioned.");
		value = false;
	}

	if(value)
	{
		if(!checkDate(input[1]))
			value = false;

		if(!checkTime(input[2]))
			value = false;
	}
	return value;
}

bool ErrorHandling::checkSearchInput(vector<string> input)
{
	bool value = true;

	if(input[1] != "")
	{
		if(!checkDate(input[1]))
		value = false;
	}
 
	if(input[2] != "")
	{
		if(!checkTime(input[2]))
		value = false;
	}

	return value;
}

bool ErrorHandling::checkEditInput(string input)
{
	bool value = true;
	string error = "Error!!! Input is not an integer\n";
	try
	{
		int iterator = 0;
		if(input.size() == 0)
			throw error;
		for( ;iterator< input.size(); iterator++)
			if(!isdigit(input[iterator]))
				throw error;
	}

	catch(string wrong)
	{
		cout << wrong;
		performLogging("String consists of non-integer value");
		value = false;
	}
	Sleep(700);
	return value;
}

bool ErrorHandling::checkDate(string& date){
	string year, dd, month = "";int temp = 0;int count = 0;
	bool correctDate,  monthName1 = false;string keyword; 

	TimeDates *userDate = new TimeDates ();

	userDate -> toLowerCase (date);
	if(userDate -> isDateFieldEmpty (date))
		return true;
	date = userDate -> retainCharOrDigitInput (date);
	userDate -> isKeywordThere (date, keyword);
    monthName1 = userDate -> monthNameToNumber (date, month);
	date = userDate -> removeAllAlpha (date);
	/*Case when Feb 11 is entered instead of 11 Feb*/
	date = userDate -> checkForInversion (date,month);
	
	
	if(date.length() == 3 || date.length() == 5 ||date.length() == 7)
		date = '0' + date;
	if(userDate -> isDateFieldEmpty (date))
		return false;
	userDate -> insertYear (date,year);
	if(date.length() == 8)
		userDate -> extractDate (date);
	else{
		date = DEFAULT_DATE;
		cout << "Invalid date " <<endl;
		return false;
		}
	userDate -> isDateLegalInEitherMonthFirstOrDateFirstFormat (date, correctDate, monthName1);
	if(!correctDate)
		return false;
	userDate -> convertDateToOutputFormat(date);	
	return true;	
}

bool ErrorHandling::checkTime(string& time){
	bool check24hrFormat = false; std::string timedigit = ""; int digittime = 0;
	string timeword = ""; std::string timeDigit = "";

	TimeDates *userTime = new TimeDates(); 

	userTime -> toLowerCase(time);
	time = userTime -> retainCharOrDigitInput (time);
	userTime -> separateDigitFromWord (timeDigit, timeword, time);
	
		if(userTime -> isTimeEmpty (timeDigit))
		{
			time = timeDigit;
			return true;
		}
		if(timeDigit.length() > 4)
			timeDigit = timeDigit.substr(0,4);

	digittime = userTime -> convertTo4DigitTimeFormat (timeDigit);
	userTime -> convertTo12HrFormat (timeword, digittime);
	timedigit = userTime -> convertIntegerToString (digittime);
	userTime -> convertTo4DigitTimeFormat (timedigit);
	userTime -> convertTimeToOutputFormat (timeword, timedigit, time);
	return userTime -> isTimeValid (time, digittime);
}

void changeToLower(string &input)
{
	for(int i = 0; i < input.size(); i++)
		input[i] = tolower(input[i]);
}