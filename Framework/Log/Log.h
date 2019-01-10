#pragma once
enum class LogType :uint
{
	Info,Warning,Error,
};
class Log
{
public:
	static void SetLogger(class ILogger* iLogger);

	//Text
	static void Write(const char* text, const LogType& type);
	static void Write(const string& text, const LogType& type);
	
	static void WriteFormatInfo(const char* text, ...);
	static void WriteFormatWarning(const char* text, ...);
	static void WriteFormatError(const char* text, ...);
	//가변인자 조사

	//Math
	static void Write(const Vector2& vec, const LogType& type);
	static void Write(const Vector3& vec, const LogType& type);
	static void Write(const Vector4& vec, const LogType& type);

	//Primitive
	static void Write(const bool& val, const LogType& type);
	static void Write(const int& val, const LogType& type);
	static void Write(const uint& val, const LogType& type);
	static void Write(const float& val, const LogType& type);
	static void Write(const double& val, const LogType& type);

	static void LogString(const char* text, const LogType& type);
	static void LogToFile(const char* text, const LogType& type);
private:
	static class ILogger* logger;
	static ofstream out;
	static string fileName;
	static bool bFirstLog;
	static mutex logMutex;

};

