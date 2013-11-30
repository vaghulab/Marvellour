//Main Author : RAVI THEJA REDDY SINGANNAGARI (A0074598L)
#include "CleanUp.h"

//Function: Comprehends what the user wishes to do and calls function to split the user commands.
vector<string> CleanUp::cleanUserInput(string input,int & category)
{
	vector<string> splitInputs;
	istringstream split(input);
	string choice = "";
	string details = "";
	string code = "";
	
	getline(split,choice,';');
	toLower(choice);
	removeSpaces(choice);

	if(choice == "add" || choice == "a")
	{
		getline(split,details);
		splitFunction(details,splitInputs,"add");
		category = 1;
	}

	else if(choice == "edit" || choice == "e")
	{
		getline(split,code,';');
		removeSpaces(code);
		getline(split,details);
		splitFunction(details,splitInputs,"edit");
		splitInputs[4] = code;
		category = 2;
	}

	else if(choice == "search" || choice == "s")
	{
		getline(split,details);
		splitFunction(details,splitInputs,"search");
		category = 3;
	}

	// for undo
	else if(choice == "z" || choice == "undo" || choice == "u")
	{
		category = 4;
	}
	//for redo
	else if(choice == "r" || choice == "redo" || choice == "y")
	{
		category = 5;
	}

	else if(userGuideTerms(choice))
	{
		getline(split,details);
		toLower(details);
		removeSpaces(details);
		splitInputs.push_back(details);
		category = 6;
	}
	
	else if(choice == "notification" || choice == "notifications" || choice == "n" || choice == "ntf" || choice == "ntfs")
	{
		category = 7;
	}

	else if(choice == "done" || choice == "md" || choice == "mark done" || choice == "markdone")
	{
		getline(split,code,';');
		removeSpaces(code);
		splitFunction("",splitInputs,"");
		splitInputs[4] = code;
		category = 8;
	}

	else if(choice == "arch" || choice == "archive")
	{
		category = 9;
	}
    
	else if(choice == "remove" || choice == "rmv" || choice == "del" || choice == "delete" || choice == "mdd")
	{
       	getline(split,code,';');
		removeSpaces(code);
		splitFunction("",splitInputs,"");
		splitInputs[4] = code;
		category = 10;
	}

	else if(choice == "exit" || choice == "x" || choice == "terminate")
	{
		getline(split,details);
		category = 11;
	}
	
	else
		category = -1;
	
	return splitInputs;
}

//Function: Splits each part of the user command seperated by ; and stores it in the vector
void CleanUp::splitFunction(string userInput, vector<string> &storeDetails, string choice)
{
	string temp;
	istringstream split(userInput);

	while(getline(split,temp,';'))
		storeDetails.push_back(temp);	
	
	int iterator;

	for(iterator = storeDetails.size(); iterator < 5; iterator++)
			storeDetails.push_back("");
		
		splitFunctionFurther(storeDetails,choice);

		for(iterator = storeDetails.size() - 1; iterator > 4; iterator--)
			storeDetails.pop_back();

}

//Function: Stores event title at postion 0, date at position 1, time at position 2,
//          priority at location 3 and eventcode(only incases of edit, delete, postpone)
//          at position 4 of the vector
void CleanUp::splitFunctionFurther(vector<string> &input, string choice)
{
	string label;
	string detail;
	string extraEventDesc;
	string temp[4] = {"","","",""};
	

	int flag = -1;
	
	if(choice == "add" || choice == "edit")
		flag = 0;
	else if(choice == "search")
		flag = 1;

	for( int i = 0; i < input.size(); i++)
	{
		istringstream split(input[i]);
		getline(split,label,'/');
		
		extraEventDesc = label;
		toLower(label);
		removeSpaces(label);
      
		if((flag == 0 || flag == 1) && (label == "event" || label == "l" || label == "label" || label == "description" || label == "title"))
		{
			getline(split,detail);			
			temp[0] = temp[0] + " " + detail;
			removeIrrelevantSpaces(temp[0]);
		}

		else if(label == "d" || label == "date")
		{
			getline(split,detail);
			temp[1] = detail;
		}

		else if(label == "time" || label == "t")
		{
			getline(split,detail);
			temp[2] = detail;
		}

		else if(label == "p" || label == "priority")
		{
			getline(split,detail);
			temp[3] = detail;
		}

		else
		{
			if( flag == 1)
			{
				temp[0] = temp[0] + " " + extraEventDesc;
				removeIrrelevantSpaces(temp[0]);
				
   			}
		}
	}

	for(int i = 0; i < 4; i++)
		input[i] = temp[i];

	string temp2 = input[3];
	toLower(temp2);
	removeSpaces(temp2);

	if(choice == "add")
	{
	
	if(priorityTerms(temp2))
		input[3] = "1";
	else
		input[3] = "2";
	}

	else if(choice == "edit" || choice == "search")
	{
		if(temp2 != "")
		{
			if(priorityTerms(temp2))
				input[3] = "1";
			else 
				input[3] = "2";
		}
	}

}

//Function: Converts all characters in a string to their respective lower cases.
void CleanUp::toLower(string& input)
{
	for(int iterator = 0; iterator < input.size(); iterator++)
		input[iterator] = tolower(input[iterator]);
}

//Function: Remove all the spaces in a string
void CleanUp::removeSpaces(string& input)
{
	for(int counter = 0; counter < input.size(); counter++)
		if(input[counter] == ' ')
		{
			input.erase(input.begin() + counter);
			--counter;
		}
}

//Function: Removes double spaces and unnecessary spaces at the beginning and end of a string
void CleanUp::removeIrrelevantSpaces(string& input)
{
	bool previousSpace = true;
	bool currentSpace = true;
	
	int iterator = 0;
	
	//Loop helps remove double spaces and spaces at the beginning of the string
	for( int counter = 0; counter < input.size(); counter++)
	{
		if(input[counter] == ' ')
		{
			currentSpace = true;
			if(previousSpace && currentSpace)
			{
				input.erase(input.begin() + counter);
				--counter;
				currentSpace = true;
			}
		}
		else
			currentSpace = false;

		previousSpace = currentSpace;
	}

	//Removes unnecessary spaces at the end of the string
	if(input.size() != 0)
	if(input[input.size() - 1] == ' ')
		input.erase(input.end() - 1);    
}

//Function: Matches a list of commonly used user commands for high priority. Returns a truth value based on the match.
bool CleanUp::priorityTerms(string input)
{
	string terms[] = { "h", "high", "top", "imp", "important", "critical", "crit", "fav", "favourite", "1"};
	
	for(int counter = 0; counter < 10; counter++)
		if(input == terms[counter])
			return true;
	return false;
}

//Function: Matches a list of commonly used user commands for displaying help menu. Returns a truth value based on the match.
bool CleanUp::userGuideTerms(string input)
{
	string terms[] = { "help", "h","userguide", "guide", "g", "helpmenu"};
	for(int counter = 0; counter < 6; counter++)
		if(input == terms[counter])
			return true;
	return false;
}
