#pragma once
//xml: 정보저장
class FileSystem
{
public:
	static const char* EveryFilter;
	static const char* TextureFilter;
	static const char* ShaderFilter;
	static const char* XmlFilter;
public:
	static void OpenFileDialog(function<void(string)>func,const char* filter =EveryFilter,const char* directory="");
	static void SaveFileDialog(function<void(string)>func, const char* filter = EveryFilter, const char* directory = "");
public:
	static const bool Create_Directory(const string& path);
	static const bool Delete_Directory(const string& directory);
	static const bool Delete_File(const string& path);
	static const bool Copy_File(const string& src, const string& dst); //src->원본, dst->복사본
	static const bool IsDirectory(const string& path);//들어온 페스가 폴더경로인가 아닌가
	static const bool ExistDirectory(const string& directory);//지금 들어온 경로에 폴더가 존재하나 안하나.
	static const bool ExistFile(const string& path);//파일이 존재하나 안하나 




	static const string GetFrileNameFromPath(const string& path);//파일 path를 받아서 풀네임빼는거
	static const string GetIntactFileNameFromPath(const string& path);//파일 Path를 받아서 이름빼는거
	static const string GetDirectoryFromPath(const string& path);
	static const string GetExtensionFromPath(const string& path);
	static const string GetRelativeFilePath(const string& absolutePath); //절대경로를 상대경로로
	static const string GetWorkingDirectory(); //현재 작업중인 경로
	static const string GetParentDirectory(const string& directory); //들어오는 디렉토리의 부모디렉토리를 얻음
	static const vector<string> GetDirectoriesInDirectory(const string& directory);//해당 폴더안에있는 폴더이름들을 얻어옴
	static const vector<string>	GetFilesInDirectory(const string& directory); //폴더안에있는 모든 파일

	static const vector<string>& GetSupportImageFormats() {	return supportImageFormats;	}
	static const vector<string>& GetSupportAudioFormats() {	return supportAudioFormats;	}
	static const vector<string>& GetSupportShaderFormats() {return supportShaderFormats;}
	static const vector<string>& GetSupportBinaryFormats() {return supportBinaryFormats;}

	static const bool IsSupportImageFile(const string& path);
	static const bool IsSupportAudioFile(const string& path);
	static const bool IsSupportShaderFile(const string& path);
	static const bool IsSupportBinaryFile(const string& path);


	static void ReplaceAll(string& str,const string& from,const string& to);
	static const string ToUpper(const string& lower	);
	static const string ToLower(const string& upper);
	static const wstring ToWstring(const string& value);
	static const string ToString(const wstring& value);

private:
	static vector<string> supportImageFormats;
	static vector<string> supportAudioFormats;
	static vector<string> supportShaderFormats;
	static vector<string> supportBinaryFormats;
};