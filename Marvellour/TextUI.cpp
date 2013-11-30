//Main Author : RAVI THEJA REDDY SINGANNAGARI (A0074598L)
#include "TextUI.h"

//Function: Gets input from the user
string TextUI::getInput()
{	
	cout << "Enter command: ";
	string choice;
	getline(cin,choice);

	return choice;
}

//Function: Displays the input string in the specified colour which is indicated by the passed integer value.
void TextUI::colourText(int color,string text)
{
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(handle, color);
	cout<<text;
}

//Function: Opens the files and displays the file contents
void TextUI::displayFileContent(string filename)
{
	ifstream file;
	file.open(filename);
	if(file)
	{
		string text;
		int colour;
		getline(file,text,'\\');
		file >> colour;
		while(file)
		{   
			colourText(colour,text);
			getline(file,text,'\\');
			file >> colour;
		}
	}

	file.close();

}

//Function: Displays the design for showing the top events in the main screen
void TextUI::displayRemindersScreen()
{
	ifstream file;
	file.open("ReminderScreen.txt");
	if(file)
	{
		string text;
		int colour;
		getline(file,text,'\\');
		file >> colour;
		while(file)
		{   
			colourText(colour,text);
			if(text == "\n\nEVENTS:-")
			{
				cout<<endl;
				displayRemindersText();
			}
			getline(file,text,'\\');
			file >> colour;

		}
	}

	file.close();
	cout << "\n";
}

void TextUI::displayRemindersText()
{
	displayFileContent("ReminderStorage.txt");
}

//Function: Displays the design for showing the notification at the bottom of the screen
void TextUI::displayNotificationScreen()
{
	displayFileContent("NotificationScreen.txt");
	displayNotificationText();
}

void TextUI::displayNotificationText()
{
	displayFileContent("NotificationText.txt");

}

void TextUI::displayUserGuide()
{
	int done = 1;
	string choice;

	system("CLS");

	while(done)
	{
		displayFileContent("UserGuide.txt");
		cout << endl << "Enter choice: ";
		getline(cin,choice);

		chooseGuide(choice,done);

		if(done == 1)
			system("CLS");
	}
}

void TextUI::chooseGuide(string choice,int& done)
{
	convertToLower(choice);
	done = 1;

	if(choice == "add" || choice == "a" || choice == "1")
		displayAddGuide();

	else if(choice == "edit" || choice == "e" || choice == "2")
		displayEditGuide();

	else if(choice == "search" || choice == "s" || choice == "3")
		displaySearchGuide();

	else if(choice == "others" || choice == "o" || choice == "other" || choice == "4")
		displayOthersGuide();

	else if(choice == "exit" || choice == "x")
		done = 0;

	else
	{   
		cout << "\nInvalid Command.\n";
		Sleep(700);
	}

}

void TextUI::displayAddGuide()
{
	system("CLS");
	displayFileContent("AddUserGuide.txt");
	system("PAUSE");
}

void TextUI::displayEditGuide()
{
	system("CLS");
	displayFileContent("EditUserGuide.txt");
	system("PAUSE");
}

void TextUI::displaySearchGuide()
{
	system("CLS");
	displayFileContent("SearchUserGuide.txt");
	system("PAUSE");
}

void TextUI::displayOthersGuide()
{
	system("CLS");
	displayFileContent("OthersUserGuide.txt");
	system("PAUSE");
}

void TextUI::convertToLower(string &text)
{
	for(unsigned iterator = 0; iterator < text.size(); iterator++)
		text[iterator] = tolower(text[iterator]);

}