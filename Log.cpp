#include "Log.h"

fstream debugLog;

void Log::Init()
{
	debugLog.open("Debug.txt");
}

void Log::SendMessage(string message, LOG_TYPE level)
{

	switch (level)
	{
	case ERROR:
		debugLog << "ERROR: " << message << endl;
		break;
	case WARNING:
		debugLog << "WARNING: " << message << endl;
		break;
	case MESSAGE:
		debugLog << "MESSAGE: " << message << endl;
		break;
	}

}

void Log::Close()
{
	debugLog.close();
}