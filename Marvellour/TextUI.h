//Main Author : RAVI THEJA REDDY SINGANNAGARI (A0074598L)
#ifndef TEXTUI_H_
#define TEXTUI_H_

#include "HeaderFiles.h"

class TextUI
{
private:
	string userInput;

public:
	string getInput();
	void colourText(int,string);
	void displayRemindersScreen();
	void displayRemindersText();
	void displayNotificationScreen();
	void displayNotificationText();
	void displayFileContent(string);
	void displayUserGuide();
	void chooseGuide(string,int&);
	void displayAddGuide();
	void displayEditGuide();
	void displaySearchGuide();
	void displayOthersGuide();
	void convertToLower(string&);
};

#endif