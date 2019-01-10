#pragma once
//xml: ��������
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
	static const bool Copy_File(const string& src, const string& dst); //src->����, dst->���纻
	static const bool IsDirectory(const string& path);//���� �佺�� ��������ΰ� �ƴѰ�
	static const bool ExistDirectory(const string& directory);//���� ���� ��ο� ������ �����ϳ� ���ϳ�.
	static const bool ExistFile(const string& path);//������ �����ϳ� ���ϳ� 




	static const string GetFrileNameFromPath(const string& path);//���� path�� �޾Ƽ� Ǯ���ӻ��°�
	static const string GetIntactFileNameFromPath(const string& path);//���� Path�� �޾Ƽ� �̸����°�
	static const string GetDirectoryFromPath(const string& path);
	static const string GetExtensionFromPath(const string& path);
	static const string GetRelativeFilePath(const string& absolutePath); //�����θ� ����η�
	static const string GetWorkingDirectory(); //���� �۾����� ���
	static const string GetParentDirectory(const string& directory); //������ ���丮�� �θ���丮�� ����
	static const vector<string> GetDirectoriesInDirectory(const string& directory);//�ش� �����ȿ��ִ� �����̸����� ����
	static const vector<string>	GetFilesInDirectory(const string& directory); //�����ȿ��ִ� ��� ����

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