//Main Author : RAVI THEJA REDDY SINGANNAGARI (A0074598L)
#ifndef CLEAN_UP_H
#define CLEAN_UP_H

#include "HeaderFiles.h"

class CleanUp
{
public:
	vector<string> cleanUserInput(string,int&);
	void splitFunction(string,vector<string>&,string);
	void splitFunctionFurther(vector<string>&,string);
	void toLower(string&);
	void removeSpaces(string& );
	void removeIrrelevantSpaces(string&);
	bool priorityTerms(string);
	bool userGuideTerms(string);
};

#endif