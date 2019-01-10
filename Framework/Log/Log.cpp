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
	va_start(args, text);//���������� �����ּҸ� ������
	vsnprintf(buffer, sizeof(buffer),text,args);
	va_end(args);

	Write(buffer, LogType::Info);
}

void Log::WriteFormatWarning(const char * text, ...)
{
	char buffer[1024];
	va_list args;
	va_start(args, text);//���������� �����ּҸ� ������
	vsnprintf(buffer, sizeof(buffer), text, args);
	va_end(args);

	Write(buffer, LogType::Warning);
}

void Log::WriteFormatError(const char * text, ...)
{
	char buffer[1024];
	va_list args;
	va_start(args, text);//���������� �����ּҸ� ������
	vsnprintf(buffer, sizeof(buffer), text, args);
	va_end(args);

	Write(buffer, LogType::Error);
}

void Log::Write(const Vector2 & vec, const LogType & type)
{//vector2�ȿ� ���� tostring�ϴ� �Լ��� �������Ѵ�.
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
	lock_guard<mutex> guard(logMutex); //�ϳ��� ���μ����� �Ѱ��� �����尡 �ִ�.=>mutex ��Ƽ������
	//������ �ϳ��� ���μ��� �������� ������ ���μ����� �ڿ����� �����尡 �����ؼ� �浹���ɼ����ִ�. �׷��� mutex�� �浹�� ���´�.
	//�ϳ��� �����尡 �۾��Ѵٸ� �ٸ������尡 �۾����ϰ� ���´�. 
	//�׷� ���� ����� �ս������ִ°� lock_guard
	logger->Log(string(text), static_cast<int>(type));
}

void Log::LogToFile(const char * text, const LogType & type)
{
	lock_guard<mutex> guard(logMutex);

	string prefix = (type == LogType::Info) ? "Info:" : (type == LogType::Warning) ? "Warning:" : "Error:";
	string finalText = prefix + " " + text;

	out.open("log.txt",ios::out | ios::app); //app->�հ��� ġ�� ���ο� ���� �����Ѵ�.
	out << finalText << endl;
	out.close();
}
