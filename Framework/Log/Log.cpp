#include "stdafx.h"
#include "Log.h"
#include "ILogger.h"
ILogger*   Log::logger;
ofstream   Log::out;
string     Log::fileName;
mutex      Log::logMutex;
bool       Log::bFirstLog = false;

void Log::SetLogger(ILogger * iLogger)
{
	logger = iLogger;
}

void Log::Write(const char * text, const LogType & type)
{
	logger ? LogString(text, type) : LogToFile(text, type);
}

void Log::Write(const string & text, const LogType & type)
{
	Write(text.c_str(), type);
}

void Log::WriteFormatInfo(const char * text, ...)
{
	char buffer[1024];
	va_list args;
	va_start(args, text);//가변인자의 시작주소를 받을놈
	vsnprintf(buffer, sizeof(buffer),text,args);
	va_end(args);

	Write(buffer, LogType::Info);
}

void Log::WriteFormatWarning(const char * text, ...)
{
	char buffer[1024];
	va_list args;
	va_start(args, text);//가변인자의 시작주소를 받을놈
	vsnprintf(buffer, sizeof(buffer), text, args);
	va_end(args);

	Write(buffer, LogType::Warning);
}

void Log::WriteFormatError(const char * text, ...)
{
	char buffer[1024];
	va_list args;
	va_start(args, text);//가변인자의 시작주소를 받을놈
	vsnprintf(buffer, sizeof(buffer), text, args);
	va_end(args);

	Write(buffer, LogType::Error);
}

void Log::Write(const Vector2 & vec, const LogType & type)
{//vector2안에 따로 tostring하는 함수를 만들어야한다.
}

void Log::Write(const Vector3 & vec, const LogType & type)
{
}

void Log::Write(const Vector4 & vec, const LogType & type)
{
}

void Log::Write(const bool & val, const LogType & type)
{
	val ? Write("True", type) : Write("False", type);
}

void Log::Write(const int & val, const LogType & type)
{
	Write(to_string(val), type);
}

void Log::Write(const uint & val, const LogType & type)
{
	Write(to_string(val), type);
}

void Log::Write(const float & val, const LogType & type)
{
	Write(to_string(val), type);
}

void Log::Write(const double & val, const LogType & type)
{
	Write(to_string(val), type);
}

void Log::LogString(const char * text, const LogType & type)
{
	lock_guard<mutex> guard(logMutex); //하나의 프로세서에 한개의 쓰래드가 있다.=>mutex 멀티쓰레드
	//쓰레드 하나의 프로세스 여러개의 쓰레드 프로세스의 자원들을 쓰레드가 공유해서 충돌가능성이있다. 그래서 mutex로 충돌을 막는다.
	//하나의 쓰레드가 작업한다면 다른쓰레드가 작업못하게 막는다. 
	//그런 락과 언락을 손쉽게해주는게 lock_guard
	logger->Log(string(text), static_cast<int>(type));
}

void Log::LogToFile(const char * text, const LogType & type)
{
	lock_guard<mutex> guard(logMutex);

	string prefix = (type == LogType::Info) ? "Info:" : (type == LogType::Warning) ? "Warning:" : "Error:";
	string finalText = prefix + " " + text;

	out.open("log.txt",ios::out | ios::app); //app->먼가를 치면 새로운 것을 갱신한다.
	out << finalText << endl;
	out.close();
}
