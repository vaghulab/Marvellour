#include "Functionality.h"

#define CCT (+8)

void performLogging(string);

void Functionality::undoTask()
{
	if(undoCount.size() != 0)
	{
		if(undoCount[undoCount.size() - 1] == 0)
		{
			redoHighVector.push_back(undoHighVector[undoHighVector.size() - 1]);
			undoHighVector.pop_back();
			if(undoHighVector.size() != 0)
				highPriority=undoHighVector[undoHighVector.size() - 1];
			else
				highPriority.clear();
			undoCount.pop_back();
			redoCount.push_back(0);
			cout << "\nUndo Successful\n";
			Sleep(700);
		}
		else
			if(undoCount[undoCount.size()-1] == 1)
			{
				redoNormalVector.push_back(undoNormalVector[undoNormalVector.size() - 1]);
				undoNormalVector.pop_back();
				if(undoNormalVector.size() != 0)
					normalPriority=undoNormalVector[undoNormalVector.size() - 1];
				else
					normalPriority.clear();
				undoCount.pop_back();
				redoCount.push_back(1);
				cout << "\nUndo Successful\n";
				Sleep(700);
			}
			else
				if(undoCount[undoCount.size() - 1] == 2)
				{
					redoHighVector.push_back(undoHighVector[undoHighVector.size() - 1]);
					redoNormalVector.push_back(undoNormalVector[undoNormalVector.size() - 1]);
					undoHighVector.pop_back();
					undoNormalVector.pop_back();
					if(undoHighVector.size() != 0)
						highPriority=undoHighVector[undoHighVector.size() - 1];
					else
						highPriority.clear();
					if(undoNormalVector.size() != 0)
						normalPriority=undoNormalVector[undoNormalVector.size() - 1];
					else
						normalPriority.clear();
					undoCount.pop_back();
					redoCount.push_back(2);
					cout << "\nUndo Successful\n";
					Sleep(700);
				}
	}
	else
	{
		cout << "\nUndo Unsuccessful\n";
		Sleep(700);
	}
	callSort();
	updateFile();
	notificationFile();
}

void Functionality::redoTask()
{
	if(redoCount.size() != 0)
	{
		if(redoCount[redoCount.size()-1] == 0)
		{
			highPriority = redoHighVector[redoHighVector.size() - 1];
			undoHighVector.push_back(redoHighVector[redoHighVector.size() - 1]);
			redoHighVector.pop_back();
			redoCount.pop_back();
			undoCount.push_back(0);
			cout<<"\nRedo Successful\n";
			Sleep(700);
		}
		else
			if(redoCount[redoCount.size() - 1] == 1)
			{
				normalPriority = redoNormalVector[redoNormalVector.size() - 1];
				undoNormalVector.push_back(redoNormalVector[redoNormalVector.size() - 1]);
				redoNormalVector.pop_back();
				redoCount.pop_back();
				undoCount.push_back(1);
				cout << "\nRedo Successful\n";
				Sleep(700);
			}
			else
				if(redoCount[redoCount.size() - 1] == 2)
				{
					highPriority = redoHighVector[redoHighVector.size() - 1];
					normalPriority = redoNormalVector[redoNormalVector.size() - 1];
					undoHighVector.push_back(redoHighVector[redoHighVector.size() - 1]);
					undoNormalVector.push_back(redoNormalVector[redoNormalVector.size() - 1]);
					redoHighVector.pop_back();
					redoNormalVector.pop_back();
					redoCount.pop_back();
					undoCount.push_back(2);
					cout << "\nRedo Successful\n";
					Sleep(700);
				}
	}
	else
	{
		cout << "\nRedo Unsuccessful\n";
		Sleep(700);
	}

	callSort();
	updateFile();
	notificationFile();
}

void Functionality::doneTask(int displayFlag)
{
	system("CLS");
	vector<EventStorage> eventVector;
	int notDone = 0;
	int taskHour,taskMinute;

	// get system date
	struct tm *Sys_T = NULL;                     
	time_t Tval = 0;                            
	Tval = time(NULL);                          
	Sys_T = localtime(&Tval);                   
	int day=Sys_T->tm_mday;
	int month=Sys_T->tm_mon+1;
	int year=1900 + Sys_T->tm_year;

	//system time
	time_t rawtime;
	struct tm * ptm;
	time ( &rawtime );
	ptm = gmtime ( &rawtime );

	int hour = ptm->tm_hour+CCT%24; 
	int minute = ptm->tm_min;



	// run through all vector entries
	for(int i = 1; i < 3; i++)
	{
		if(i == 1) eventVector = highPriority;
		else eventVector = normalPriority;



		for (int counter=0; counter < eventVector.size(); counter++)
		{
			string taskTime = eventVector[counter].getTime();
			taskHour=25;
			taskMinute=00;

			if(taskTime != "25:00")
			{
				if ( taskTime[6] == 'p')  
				{

					if(((int(taskTime[0]) - 48) * 10 + (int(taskTime[1]) - 48) ) == 12)
						taskHour = 12;
					else
						taskHour = (int(taskTime[0])-48)*10 + (int(taskTime[1])-48) + 12;
					taskMinute = (int(taskTime[3])-48)*10 + (int(taskTime[4])-48);
				}
			}
			else
			{
				if(((int(taskTime[0]) - 48)*10 + (int(taskTime[1])-48) ) == 12)
					taskHour=0;
				else
					taskHour = (int(taskTime[0]) - 48) * 10 + (int(taskTime[1]) - 48);
				taskMinute = (int(taskTime[3]) - 48) * 10 + (int(taskTime[4]) - 48);
			}

			if((eventVector[counter].getDoneFlag() == 0) && (eventVector[counter].getMonth() == month) && (eventVector[counter].getYear() == year) && (eventVector[counter].getDay() < day))
			{
				notDone++;
				if(displayFlag == 1)
					eventVector[counter].displayEvent();
			}
			else if((eventVector[counter].getDoneFlag() == 0)&&(eventVector[counter].getMonth() < month) && (eventVector[counter].getYear() == year))
			{
				notDone++;
				if(displayFlag == 1)
					eventVector[counter].displayEvent();
			}
			else if((eventVector[counter].getDoneFlag() == 0)&&(eventVector[counter].getYear() < year))
			{
				notDone++;
				if(displayFlag==1)
					eventVector[counter].displayEvent();
			}
			else if((eventVector[counter].getDoneFlag() == 0)&&(eventVector[counter].getMonth()== month) && (eventVector[counter].getYear() == year) && (eventVector[counter].getDay() == day) && (taskHour < hour))
			{
				notDone++;
				if(displayFlag==1)
					eventVector[counter].displayEvent();
			}
			else if((eventVector[counter].getDoneFlag() == 0)&&(eventVector[counter].getMonth()== month) && (eventVector[counter].getYear() == year) && (eventVector[counter].getDay() == day) && (taskHour==hour) && (taskMinute < minute))
			{
				notDone++;
				if(displayFlag==1)
					eventVector[counter].displayEvent();
			}
		}
	}
	if(displayFlag == 1)
		system("Pause");

	if(displayFlag == 0)
	{
		ofstream myFile;
		myFile.open("NotificationText.txt");
		myFile << "\n\nNumber of undone tasks which have missed their deadlines : " << notDone << "\\11\n";
		myFile.close();
	}
}

void Functionality::loadVectorsFromFile()
{
	EventStorage tempEvent;
	ifstream fileRead("EventStorage.txt");
	string eventStore;
	string tempPriority;

	while(getline(fileRead, eventStore))
	{
		if(eventStore.size() > 0)
		{
			if(eventStore[0] == '#')
			{
				loadEvent(tempEvent, eventStore.substr(1, eventStore.size() - 1));
				tempPriority = tempEvent.getPriority();
				if(tempPriority[0] == '1')
					highPriority.push_back(tempEvent);
				else
					if(tempPriority[0] == '2')
						normalPriority.push_back(tempEvent);
			}
		}
	}
	fileRead.close();
	if(highPriority.size() != 0)
		undoHighVector.push_back(highPriority);
	if(normalPriority.size() != 0)
		undoNormalVector.push_back(normalPriority);
}

void Functionality::loadEvent(EventStorage &tempEvent, string tempRecord)
{
	istringstream readRecord(tempRecord);
	string tempString;
	int tempDoneFlag;
	vector<string> eventParameters;

	for(int i = 0; i < 6; i++)
	{
		getline(readRecord, tempString, '#');
		if(i != 5)
			eventParameters.push_back(tempString);
		else
		{
			if(tempString[0] == '0')
				tempDoneFlag = 0;
			else
				tempDoneFlag = 1;
		}
	}

	tempEvent.storeUserInput(eventParameters, tempDoneFlag);
}

void Functionality::addTask(vector<string> eventDetails)
{
	EventStorage tempEvent;
	int tempCode;
	int tempDigit;
	string tempString;
	ifstream eventCodeGenerate("EventCode.txt");
	eventCodeGenerate>>tempCode;
	eventCodeGenerate.close();
	tempCode += 1;
	ofstream writeCode("EventCode.txt");
	writeCode<<tempCode;
	writeCode.close();
	while(tempCode != 0)
	{
		tempDigit = tempCode%10;
		tempString += char(tempDigit+48);
		tempCode /= 10;		
	}
	eventDetails.pop_back();
	eventDetails.push_back(tempString);
	tempEvent.storeUserInput(eventDetails, 0);
	string eventPriority=tempEvent.getPriority();

	if(eventPriority[0] == '1')
	{
		highPriority.push_back(tempEvent);
		undoHighVector.push_back(highPriority);
		undoCount.push_back(0);
	}
	else
		if(eventPriority[0] == '2')
		{
			normalPriority.push_back(tempEvent);
			undoNormalVector.push_back(normalPriority);
			undoCount.push_back(1);
		}
		redoCount.clear();
		redoHighVector.clear();
		redoNormalVector.clear();
		callSort();
		updateFile();
		notificationFile();
}

int Functionality::checkForClash(string checkDate, string checkTime, string tempCode)
{
	int clashFlag = 0;
	unsigned i;
	for(i = 0; i < highPriority.size(); i++)
	{
		if(highPriority[i].getDate() == checkDate && highPriority[i].getTime() == checkTime&&highPriority[i].getCode() != tempCode)
		{
			clashFlag = 1;
			break;
		}
	}
	if(clashFlag != 1)
	{
		for(i = 0; i < normalPriority.size(); i++)
		{
			if(normalPriority[i].getDate() == checkDate && normalPriority[i].getTime() == checkTime&&normalPriority[i].getCode() != tempCode)
			{
				clashFlag = 1;
				break;
			}
		}
	}
	if(checkDate == "00-00-0000" || checkTime == "25:00")
		clashFlag = 0;
	return clashFlag;
}

void Functionality::searchTask(vector<string> userInput)
{
	int searchResult = 0;
	unsigned i;
	vector<EventStorage> outputVector;
	if(userInput[0].size()!=0)
	{
		for(unsigned iterator = 0; iterator < userInput[0].size(); iterator++)
			userInput[0][iterator] = tolower(userInput[0][iterator]);
	}
	searchResult += searchTitle(userInput[0], outputVector);
	if(userInput[1].size() != 0)
		searchResult += searchOtherParameters(userInput[1], outputVector, 1);
	if(userInput[2].size() != 0)
		searchResult += searchOtherParameters(userInput[2], outputVector, 2);
	if(userInput[3].size() != 0)
		searchResult += searchOtherParameters(userInput[3], outputVector, 3);
	if(searchResult > 0)
	{
		removeDuplicates(outputVector);
		for(i=0;i<outputVector.size();i++)
			outputVector[i].displayEvent();
		cout<<endl;
		system("Pause");

	}
	else
	{
		cout<<"\nSearch is Unsuccessful";
		performLogging("Search is Unsuccessful.");
		Sleep(1000);
	}
}

void Functionality::removeDuplicates(vector <EventStorage> &outputVector)
{
	int vectorElements = outputVector.size();
	vector<EventStorage> tempVector;
	unsigned j;
	int tempCount;
	for(int i=0;i<vectorElements;i++)
	{
		tempCount=0;
		for(j=0;j<tempVector.size();j++)
		{
			if(outputVector[i].getCode()==tempVector[j].getCode())
				tempCount++;
		}
		if(tempCount==0)
		{
			tempVector.push_back(outputVector[i]);
		}	
	}
	outputVector=tempVector;
}

int Functionality::searchTitle(string userInput, vector<EventStorage> &outputVector)
{
	int searchResult=0;
	string tempInput=userInput;
	istringstream wordExtract(tempInput);
	int wordCount=0;
	string tempString;
	while(wordExtract>>tempString)
		wordCount++;
	string searchString;
	string tempWord;
	int tempCount;
	while(wordCount!=0)
	{
		tempCount=0;
		searchString="\0";
		istringstream wordExtract(tempInput);
		while(wordExtract>>tempString && tempCount<wordCount)
		{
			if(tempCount==0)
				tempWord=tempString;
			searchString+=tempString;
			searchString+=" ";
			tempCount++;
		}
		searchString = searchString.substr(0, searchString.size()-1);
		searchResult += vectorSearch(searchString, outputVector);
		tempCount=0;
		istringstream tempExtract(tempInput);
		while(tempExtract>>tempString)
			tempCount++;
		if(tempCount==wordCount)
		{
			wordCount--;
			tempInput=userInput; 
			continue;
		}
		tempInput=tempInput.substr(tempWord.size()+1, tempInput.size()-(tempWord.size()+1));
	}
	if(searchResult>0)
		return 1;
	else
		return 0;
}

int Functionality::vectorSearch(string userInput, vector<EventStorage> &tempVector)
{
	int eventCount = 0;
	eventCount += searchVectorForTitle(highPriority, userInput, tempVector);
	eventCount += searchVectorForTitle(normalPriority, userInput, tempVector);
	if(eventCount>0)
		return 1;
	else
		return 0;
}

int Functionality::searchVectorForTitle(vector<EventStorage> searchVector, string userInput, vector<EventStorage> &tempVector)
{
	unsigned i;
	int searchCount=0;
	istringstream wordExtract(userInput);
	int wordCount=0;	
	string tempString;
	while(wordExtract >> tempString)
		wordCount++;
	string searchData;
	string tempTitle;
	int tempCount;
	for(i=0;i<searchVector.size();i++)
	{
		tempTitle=searchVector[i].getTitle();
		while(tempTitle.size()!=0)
		{
			tempCount=0;
			searchData="\0";
			istringstream titleExtract(tempTitle);
			while(titleExtract >> tempString && tempCount<wordCount)
			{
				tempCount++;
				searchData+=tempString;
				searchData+=" ";
			}
			searchData = searchData.substr(0, searchData.size()-1);
			for(unsigned iterator = 0; iterator < searchData.size(); iterator++)
				searchData[iterator] = tolower(searchData[iterator]);
			if(searchData==userInput)
			{
				searchCount++;
				tempVector.push_back(searchVector[i]);
				break;
			}
			istringstream getFirstWord(tempTitle);
			getFirstWord>>searchData;
			istringstream countTitle(tempTitle);
			tempCount=0;
			while(countTitle>>tempString)
				tempCount++;
			if(tempCount==1)
				tempTitle="\0";
			else
				tempTitle=tempTitle.substr(searchData.size()+1, tempTitle.size()-(searchData.size()+1));
		}
	}
	if(searchCount>0)
		return 1;
	else
		return 0;
}

int Functionality::searchOtherParameters(string userInput, vector<EventStorage> &outputVector, int searchType)
{
	vector<EventStorage> tempVector;
	unsigned i;
	unsigned j;
	int searchResult = 0;
	for(i =0; i<3;i++)
	{
		if(i==0)
			tempVector=highPriority;
		else
			if(i==1)
				tempVector=normalPriority;
		for(j=0;j<tempVector.size();j++)
		{
			if(searchType==1)
			{
				if(tempVector[j].getDate()==userInput)
				{					
					searchResult++;
					outputVector.push_back(tempVector[j]);
				}
			}
			else
				if(searchType==2)
				{
					if(tempVector[j].getTime()==userInput)
					{
						searchResult++;
						outputVector.push_back(tempVector[j]);
					}
				}
				else
					if(searchType==3)
					{
						if(tempVector[j].getPriority()==userInput)
						{
							searchResult++;
							outputVector.push_back(tempVector[j]);
						}
					}
		}
	}
	if(searchResult>0)
		return 1;
	else
		return 0;
}

void Functionality::editTask(vector<string> userInput, string eventCode)
{
	EventStorage tempEvent;
	int tempPosition = 0;
	int editCheck = 0;
	int priorityCheck=0;
	int tempCheck = 0;
	int checkCode = searchCode(tempEvent, eventCode, tempPosition);
	if(checkCode==0)
		cout<<"\nThe event code that you have entered is invalid\n";
	else
	{
		if(userInput[0].size()!=0)
			tempEvent.writeTitle(userInput[0]);
		else
			editCheck++;
		if(userInput[1].size()!=0)
			tempEvent.writeDate(userInput[1]);
		else
			editCheck++;
		if(userInput[2].size()!=0)
			tempEvent.writeTime(userInput[2]);
		else
			editCheck++;
		if(userInput[3].size()!=0)
		{
			priorityCheck=1;
			if(tempEvent.getPriority()!=userInput[3])
			{
				tempEvent.writePriority(userInput[3]);
				tempCheck = 1;
			}

			removeTask(tempEvent.getCode());
			if(tempEvent.getPriority()=="1")
			{
				highPriority.push_back(tempEvent);
				if(tempCheck == 1)
				{
					undoNormalVector.pop_back();
					undoCount.pop_back();
				}
				else
				{
					undoHighVector.pop_back();
					undoCount.pop_back();
				}

			}

			else
			{
				normalPriority.push_back(tempEvent);
				if(tempCheck==1)
				{
					undoHighVector.pop_back();
					undoCount.pop_back();
				}
				else
				{
					undoNormalVector.pop_back();
					undoCount.pop_back();
				}
			}
		}
		else
			editCheck++;
		if(priorityCheck == 0)
		{
			removeTask(tempEvent.getCode());
			if(tempEvent.getPriority()=="1")
			{
				undoHighVector.pop_back();
				undoCount.pop_back();
				highPriority.push_back(tempEvent);
				undoHighVector.push_back(highPriority);
				undoCount.push_back(0);
			}

			else
				if(tempEvent.getPriority()=="2")
				{
					undoNormalVector.pop_back();
					undoCount.pop_back();
					normalPriority.push_back(tempEvent);
					undoNormalVector.push_back(normalPriority);
					undoCount.push_back(1);
				}
		}
		else
		{
			undoHighVector.push_back(highPriority);
			undoNormalVector.push_back(normalPriority);
			undoCount.push_back(2);
		}
		if(editCheck==4)
		{
			cout<<"\nInvalid input since no event detail has been mentioned\n";
			Sleep(700);
		}
		else
		{
			cout<<"\nEvent successfully edited\n";
			Sleep(700);
		}
	}
	redoCount.clear();
	redoHighVector.clear();
	redoNormalVector.clear();
	callSort();
	updateFile();
	notificationFile();
}

int Functionality::searchCode(EventStorage &tempEvent, string tempCode, int &tempPosition)
{
	unsigned i;
	for(i=0;i<highPriority.size();i++)
	{
		if(highPriority[i].getCode()==tempCode)
		{
			tempEvent=highPriority[i];
			tempPosition=i;
			return 1;
		}
	}
	for(i=0;i<normalPriority.size();i++)
	{
		if(normalPriority[i].getCode()==tempCode)
		{
			tempEvent=normalPriority[i];
			tempPosition=i;
			return 1;
		}
	}
	return 0;
}

void Functionality::callSort()
{
	if(highPriority.size()>=2)
		sortVector(highPriority);
	if(normalPriority.size()>=2)
		sortVector(normalPriority);
}

void Functionality::sortVector(vector<EventStorage> &tempVector)
{
	unsigned i;
	unsigned j;
	long firstDate;
	long secondDate;
	for(i=0; i<tempVector.size(); i++)
	{
		for(j=0; j<tempVector.size()-i-1; j++)
		{
			firstDate=(tempVector[j].getYear()*100+tempVector[j].getMonth()*10+tempVector[j].getDay());
			secondDate=(tempVector[j+1].getYear() * 100 + tempVector[j+1].getMonth()*10+tempVector[j+1].getDay());
			if(firstDate > secondDate)
			{
				EventStorage tempEvent;
				tempEvent=tempVector[j];
				tempVector[j]=tempVector[j+1];
				tempVector[j+1]=tempEvent;
			}
		}
	}
}

void Functionality::removeTask(string tempCode)
{
	unsigned i;
	int vectorPosition=0;
	EventStorage tempEvent;

	int checkCode=searchCode(tempEvent, tempCode, vectorPosition);
	if(checkCode==1)
	{
		string tempString=tempEvent.getPriority();

		if(tempString[0]=='1')
		{
			for(i=vectorPosition;i<highPriority.size()-1;i++)
			{
				highPriority[i]=highPriority[i+1];
			}
			highPriority.pop_back();
			undoHighVector.push_back(highPriority);
			undoCount.push_back(0);
		}
		else
			if(tempString[0]=='2')
			{
				for(i=vectorPosition;i<normalPriority.size()-1;i++)
				{
					normalPriority[i]=normalPriority[i+1];
				}
				normalPriority.pop_back();
				undoNormalVector.push_back(normalPriority);
				undoCount.push_back(1);
			}
			redoCount.clear();
			redoHighVector.clear();
			redoNormalVector.clear();
			callSort();
			updateFile();
			notificationFile();
	}
}

void Functionality::notificationFile()
{
	int eventCount = 0;
	ofstream fileWrite("ReminderStorage.txt");
	unsigned i;
	unsigned j;
	vector<EventStorage> tempVector;
	for(i=0;i<2;i++)
	{
		if(i==0)
			tempVector=highPriority;
		else
			tempVector=normalPriority;
		for(j=0;j<tempVector.size() && eventCount <10 ;j++)
		{
			if(tempVector[j].getDoneFlag()==0)
			{
				fileWrite<<eventCount+1<<". ";
				if(tempVector[j].getTitle().size()!=0)
					fileWrite<<"<"<<tempVector[j].getTitle()<<">"<<"   ";
				else
					fileWrite<<"< >   ";
				if(tempVector[j].getDate()!="00-00-0000")
					fileWrite<<"<"<<tempVector[j].getDate()<<">"<<"   ";
				else
					fileWrite<<"< >   ";
				if(tempVector[j].getTime()!="25:00")
					fileWrite<<"<"<<tempVector[j].getTime()<<">"<<"   ";
				else
					fileWrite<<"< >   ";
				fileWrite<<"<"<<tempVector[j].getCode()<<">";
				if(i==0)
					fileWrite<<"\\12";
				else
					fileWrite<<"\\10";
				fileWrite<<"\n";
				eventCount++;
			}
		}
	}
	if(eventCount==0)
		fileWrite<<"No Event has been created yet\\15";
	fileWrite.close();
}

void Functionality::updateFile()
{
	unsigned i;

	ofstream fileWrite("EventStorage.txt");

	fileWrite<<"High Priority Event(s) :-\n";	
	for(i = 0; i < highPriority.size(); i++)
		fileWrite << eventConvert(highPriority[i]) << "\n";
	fileWrite << "\n";

	fileWrite << "Normal Priority Event(s) :-\n";
	for(i = 0; i < normalPriority.size(); i++)
		fileWrite << eventConvert(normalPriority[i]) << "\n";

	fileWrite.close();
}

string Functionality::eventConvert(EventStorage tempEvent)
{	
	string tempString;

	tempString += "#";
	tempString += tempEvent.getTitle();

	tempString += "#";
	tempString += tempEvent.getDate();

	tempString += "#";
	tempString += tempEvent.getTime();

	tempString += "#";
	tempString += tempEvent.getPriority();

	tempString += "#";
	tempString += tempEvent.getCode();

	tempString += "#";
	if(tempEvent.getDoneFlag()==0)
		tempString += "0";
	else
		tempString+= "1";
	tempString += "#";

	return tempString;
}

void Functionality::markAsDone(string eventCode)
{
	int doneCheck = 0;
	vector<EventStorage> eventVector;
	string tempPriority;
	for(int i=1;i<3;i++)
	{
		if( i == 1) eventVector = highPriority;
		else eventVector = normalPriority;
		for (int j=0;j<eventVector.size();j++)
		{
			if(eventVector[j].getCode() == eventCode)
			{
				tempPriority = eventVector[j].getPriority();
				eventVector[j].writeDoneFlag();
				doneCheck = 1;
			}
		}
		if(tempPriority.size()!=0)
		{
			if(tempPriority[0]=='1')
			{
				highPriority = eventVector;
				undoHighVector.push_back(highPriority);
				undoCount.push_back(0);
				tempPriority = "\0";
			}

			else
			{
				normalPriority = eventVector;
				undoNormalVector.push_back(normalPriority);
				undoCount.push_back(1);
				tempPriority = "\0";
			}
		}
	}
	if(doneCheck==0)
		cout<<"\nEvent Code not Found\n";
	else
		cout<<"\nEvent has been marked as done \n";
	Sleep(700);
	redoCount.clear();
	redoHighVector.clear();
	redoNormalVector.clear();
	callSort();
	updateFile();
	notificationFile();
}

void Functionality::displayDoneTasks()
{
	vector<EventStorage> tempVector;
	unsigned i;
	unsigned j;
	int doneCheck = 0;
	for(i=0;i<2;i++)
	{
		if(i==0)
			tempVector = highPriority;
		else
			tempVector = normalPriority;
		for(j=0;j<tempVector.size();j++)
		{
			if(tempVector[j].getDoneFlag()==1)
			{
				cout<<"\n";
				tempVector[j].displayEvent();
				doneCheck = 1;
			}				
		}
	}
	if(doneCheck==0)
	{
		cout<<"\nNo Event has been marked as done\n\n";
		Sleep(700);
	}
}

void Functionality :: getTimeOrDate(string tempCode, string &tempString, int getFlag)
{
	int vectorPosition=0;
	EventStorage tempEvent;
	int checkCode=searchCode(tempEvent, tempCode, vectorPosition);
	if(getFlag==0)
		tempString = tempEvent.getDate();
	else
		tempString = tempEvent.getTime();
}

void Functionality::countArchive()
{
	vector<EventStorage> tempVector;
	ofstream fileWrite;
	fileWrite.open("NotificationText.txt",ios::app);
	unsigned i;
	unsigned j;
	int doneCheck = 0;
	int recordCount = 0;
	for(i=0;i<2;i++)
	{
		if(i==0)
			tempVector = highPriority;
		else
			tempVector = normalPriority;
		for(j=0;j<tempVector.size();j++)
		{
			if(tempVector[j].getDoneFlag()==1)
			{
				recordCount++;
				doneCheck = 1;
			}				
		}
	}
	fileWrite<<"Number of archived events : "<<recordCount<<"\\14";
	fileWrite.close();
}

int Functionality::checkTitleClash(string eventTitle)
{
	unsigned i;
	unsigned j;
	unsigned iterator;
	int titleClash = 0;
	string tempString;
	vector<EventStorage> tempVector;
	for(i=0;i<2;i++)
	{
		if(i==0)
			tempVector = highPriority;
		else
			tempVector = normalPriority;
		for(j=0;j<tempVector.size();j++)
		{
			if(tempVector[j].getDate()=="00-00-0000" && tempVector[j].getTime()=="25:00")
			{
				tempString = tempVector[j].getTitle();
				for(iterator = 0; iterator < tempString.size() ; iterator++)
					tempString[iterator] = tolower(tempString[iterator]);
				for(iterator = 0; iterator < eventTitle.size(); iterator++)
					eventTitle[iterator] = tolower(eventTitle[iterator]);
				if(tempString==eventTitle)
					titleClash++;
			}
		}
	}
	if(titleClash>0)
		return 1;
	else
		return 0;
}