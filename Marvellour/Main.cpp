#include "Driver.h"

extern void performLogging(string input)
{
	time_t rawtime;
	struct tm * timeinfo;

	ofstream file;
	file.open("log.txt",ios::app);
	
	time(&rawtime);
	timeinfo = localtime(&rawtime);
	
	file << input << " " << asctime(timeinfo);
	file.close();

	time(&rawtime);
}

//Main Function
int main()
{
	Driver driverObject;
	driverObject.loadScreenVectors();
	driverObject.initiate();
	return 0;
}
