//Main Author : RAVI THEJA REDDY SINGANNAGARI (A0074598L)
#include "Driver.h"

void performLogging(string);

//Function: Loads events in vectors by invoking function in functionality class
void Driver::loadScreenVectors()
{
	system("CLS");
	textuiObject.displayFileContent("MarvellourDesign.txt");
	functionalityObject.loadVectorsFromFile();
	functionalityObject.notificationFile();
	//Pauses for 1 second
	Sleep(1000);
	system("CLS");
}

//Function: Gets the user input. Parses input by passing input to CleanUp class. Then calls appropriate function based on user input.
void Driver::initiate()
{
	while(1)	
	{   	
		system("CLS");

		functionalityObject.doneTask(0);
		functionalityObject.countArchive();
		callReminders();
		bottomScreen();
		HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(handle, 15);

		string input = textuiObject.getInput();
		int choice;
		vector<string> details = cleanupObject.cleanUserInput(input,choice);

		switch(choice)
		{
		case 1:
			callAdd(details);
			break;

		case 2:
			callEdit(details);
			break;

		case 3:
			callSearch(details);
			break;

		case 4:
			functionalityObject.undoTask();
			break;

		case 5:
			functionalityObject.redoTask();
			break;

		case 6:
			callUserGuide(details[0]);
			break;

		case 7:
			functionalityObject.doneTask(1);
			break;

		case 8:
			if(errorhandlingObject.checkEditInput(details[4]))
			{
				functionalityObject.markAsDone(details[4]);
			}
			break;

		case 9:
			system("CLS");
			textuiObject.displayFileContent("ArchiveScreen.txt");
			functionalityObject.displayDoneTasks();
			system("Pause");
			break;

		case 10:
			if(errorhandlingObject.checkEditInput(details[4]))
			{
				functionalityObject.removeTask(details[4]);
				cout << "Event has been successfully deleted.\n";
			}
			Sleep(700);
			break;

		case 11:
			callExit();
			break;

		default:
			cout << "\nInvalid input. Re-enter your command.\n";
			performLogging("Invalid user input for main menu.");
			Sleep(700);
		}
	}

}

//Function: Checks the validity of add input by invoking methods of class Errorhandling
void Driver::callAdd(vector<string> details)
{
	int clash = 0;

	if(details[1] == "" && details[2] == "")
		clash = functionalityObject.checkTitleClash(details[0]);

	if(clash)
		cout << "\nEvent already exists\n";

	else
	{
		if(errorhandlingObject.checkAddInput(details))
		{
			if(!functionalityObject.checkForClash(details[1], details[2], ""))
			{
				functionalityObject.addTask(details);
				cout << "\nUser input was successfully added.\n";
			}

			else
			{
				int choice;
				string input;
				string input2;

				resolveAddClash(choice,input,input2);

				if(choice == 1)
				{
					functionalityObject.addTask(details);
					cout << "User input was successfully added.\n";

				}

				else if(choice == 2)
				{
					if(input != "")
						details[1] = input;
					if(input2 != "")
						details[2] =input2;
					functionalityObject.addTask(details);
					cout << "\nEdited input was successfully added.\n";

				}

				else
				{
					cout << "The event was not added.\n";
                   
				}

			}
		}
	}
	Sleep(1000);
}

//Function: Displays possible actions the user can follow in the event of a clash while adding a task.
void Driver::resolveAddClash(int& action, string& newInput, string& newInput2)
{
	bool enterLoop = true;
	string input;
	string choice;
	string newEntry;

	while(enterLoop)
	{
		system("CLS");
		textuiObject.displayFileContent("ClashScreen.txt");
		newEntry = "";

		cout << "\nAction:\n";
		cout << "1. Ignore warning and Add event (Enter a)\n";
		cout << "2. Edit event details (Enter e;<d/[date]>;<t/[time]>)\n";
		cout << "3. Do not add the event. (Enter x)\n\n";
		cout << "Enter Command : ";

		getline(cin,input);
		istringstream split(input);
		getline(split,choice,';');
		cleanupObject.toLower(choice);
		cleanupObject.removeSpaces(choice);

		if(choice == "a" || choice == "add")
		{
			enterLoop = false;
			action = 1;
		}
		else if(choice == "x" || choice == "ignore"  || choice == "exit")
		{
			enterLoop = false;
			action = 3;
		}
		else if(choice == "e" || choice == "edit")
		{

			int check = 0; 
			string newDate = "";
			string newTime = "";
			vector<string> temp;

			for(int counter = 0; counter < 5; counter++)
				temp.push_back("");

			getline(split,newEntry,';');
			cleanupObject.splitFunction(newEntry,temp,"edit");

			if(temp[1] != "")
			{
				if(errorhandlingObject.checkDate(temp[1]))
				{
					++check;
					newDate = temp[1];
				}
				else
					--check;
			}

			if(temp[2] != "")
			{
				if(errorhandlingObject.checkTime(temp[2]))
				{
					++check;
					newTime = temp[2];
				}
				else
					--check;
			}

			if(check >= 1)
			{
				newInput = newDate;
				newInput2 = newTime;
				enterLoop = false;
				action = 2;
			}
		}

	}
}

//Function: Checks the validity of edit input by invoking methods of class Errorhandling
void Driver::callEdit(vector<string> details)
{
	if(errorhandlingObject.checkSearchInput(details))
	{
		bool store = true;

		if(details[1] != "")
			store = errorhandlingObject.checkDate(details[1]);
		else
			functionalityObject.getTimeOrDate(details[4],details[1],0);

		if(details[2] != "") 
			store = errorhandlingObject.checkTime(details[2]);
		else
			functionalityObject.getTimeOrDate(details[4],details[2],1);

		if(!functionalityObject.checkForClash(details[1], details[2], details[4]))
		{
			//checks for validity of the code of event
			if(errorhandlingObject.checkEditInput(details[4]))
			{			
				functionalityObject.editTask(details, details[4]);
			}
		}
		else
		{
			cout << "Edited input clashes with an existing event\n";
			performLogging("Edited input clashes with an existing event.");
		}
	}
	Sleep(700);
}

//Function: Checks the validity of Search input by invoking methods of class Errorhandling
void Driver::callSearch(vector<string> details)
{
	//checks validity of date and time 
	if(errorhandlingObject.checkSearchInput(details))
	{
		bool store = true;

		if(details[1] != "")
			store = errorhandlingObject.checkDate(details[1]);

		if(details[2] != "") 
			store = errorhandlingObject.checkTime(details[2]);

		system("CLS");
		textuiObject.displayFileContent("SearchScreen.txt");
		cout << endl;
		functionalityObject.searchTask(details);
	}

	else
	{
		cout << "Invalid search input.\n";
		performLogging("Invalid search input.");
	}

}

//Function: Displays reminders by invoking functions in TextUI class.
void Driver::callReminders()
{
	textuiObject.displayRemindersScreen();
}

//Function: Displays User Guides by invoking functions in TextUI class.
void Driver::callUserGuide(string guide)
{
	if(guide == "add" || guide == "a" || guide == "1")
		textuiObject.displayAddGuide();
	else if(guide == "edit" || guide == "e" || guide == "2")
		textuiObject.displayEditGuide();
	else if(guide == "search" || guide == "s" || guide == "3")
		textuiObject.displaySearchGuide();
	else if(guide == "others" || guide == "o" || guide == "other" || guide == "4")
		textuiObject.displayOthersGuide();
	else 
		textuiObject.displayUserGuide();
}

//Function: Invokes function to save existing data in files before exiting the program
void Driver::callExit()
{
	functionalityObject.updateFile();
	exit(1);
}

//Function: Sets cursor positon
void Driver::bottomScreen()
{
	HANDLE hConsoleOutput;
	COORD dwCursorPosition;
	CONSOLE_SCREEN_BUFFER_INFO csbiInfo;

	cout.flush();

	hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	GetConsoleScreenBufferInfo(hConsoleOutput,&csbiInfo);

	int posX;
	int posY;

	posX = csbiInfo.dwCursorPosition.X;
	posY = csbiInfo.dwCursorPosition.Y;

	dwCursorPosition.X = 0;
	dwCursorPosition.Y = 45;
	SetConsoleCursorPosition(hConsoleOutput,dwCursorPosition);
	textuiObject.displayNotificationScreen();


	dwCursorPosition.X = posX;
	dwCursorPosition.Y = posY;

	hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hConsoleOutput,dwCursorPosition);
}