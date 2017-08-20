#pragma once

#include <fstream>
#include <string>

using namespace std;

enum LOG_TYPE
{
	ERROR = 0,
	WARNING = 1,
	MESSAGE = 2
};
//simple logger for putting messages in a debug txt file
class Log
{
public:
	//opens the file
	static void Init();
	//adds text to file
	static void SendMessage(string message, LOG_TYPE level);
	//closes file
	static void Close();

private:

protected:
};
