//Main Authors : Vaghul Aditya Balaji (A0074270L) & Madhu Maithri Parvataneni (A0074807Y)

#ifndef FUNCTIONALITY_H
#define FUNCTIONALITY_H

#include "HeaderFiles.h"
#include "TimeDates.h"
#include "EventStorage.h"

class Functionality
{	
private:
    vector <EventStorage> highPriority;
	vector <EventStorage> normalPriority;
	vector<vector<EventStorage>> undoHighVector;
	vector<vector<EventStorage>> undoNormalVector;
	vector<vector<EventStorage>> redoHighVector;
	vector<vector<EventStorage>> redoNormalVector;	
	vector<int> undoCount;
	vector<int> redoCount;

public:
		
	void loadVectorsFromFile();
	void loadEvent(EventStorage &, string);

	void addTask(vector<string>);

	int checkForClash(string, string, string);

	void searchTask(vector<string>);	
	int searchTitle(string, vector<EventStorage> &);
	int vectorSearch(string, vector<EventStorage> &);
	int searchVectorForTitle(vector<EventStorage>, string, vector<EventStorage> &);
	int searchOtherParameters(string, vector<EventStorage> &, int);
	int searchCode(EventStorage &, string, int &);

	void editTask(vector<string>, string);

	void doneTask(int);

	void callSort();
	void sortVector(vector<EventStorage> &);

	int codeCheck(string);
		
	void removeTask(string);
	void removeDuplicates(vector <EventStorage> &);

	void notificationFile();
	void updateFile();
	string eventConvert(EventStorage);

	void undoTask();
	void redoTask();

	void displayDoneTasks();

	void countArchive();

	void markAsDone(string);

	void getTimeOrDate(string, string &, int);

	int checkTitleClash(string);

};

#endif