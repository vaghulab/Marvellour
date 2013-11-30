//Main Author : RAVI THEJA REDDY SINGANNAGARI (A0074598L)
#ifndef DRIVER_H_
#define DRIVER_H_

#include "TextUI.h"
#include "CleanUp.h"
#include "Errorhandling.h"
#include "Functionality.h"

//Class : Driver
//This is the central class of this application.
//It helps call function from one class based on the result of a function call to another class.
//In short it links all classes together indirectly

class Driver
{
private:
	TextUI textuiObject;
	CleanUp cleanupObject;
    ErrorHandling errorhandlingObject;
	Functionality functionalityObject;

public:
	void loadScreenVectors();
	void initiate();
	void callAdd(vector<string>);
	void resolveAddClash(int&, string&, string&);
	void callEdit(vector<string>);
	void callSearch(vector<string>);
	void callReminders();
	void callUserGuide(string);
	void callExit();
	void bottomScreen();
};

#endif