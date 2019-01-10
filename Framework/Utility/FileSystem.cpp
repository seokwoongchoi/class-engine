#include "stdafx.h"
#include "FileSystem.h"
#include <experimental\filesystem>

using namespace std::experimental::filesystem;//api�Լ��� �Ƚᵵ�ȴ�.

//find() =�־��� ���ڿ��� �����ϴ� ��ġ ->ó�����Ͱ˻�
//rfind() = �־��� ���ڿ��� �����ϴ� ��ġ->�ڿ������� �˻�
//find_first_of() -�־��� �����߿� �ϳ��� �ɸ��� ù��° ��ġ
//find_last_of() -�־��� �����߿� �ϳ��� �ɸ��� ������ ��ġ
//find_first_not_of() -�־��� ���ڵ��� �ƴ� ���ڰ� �ɸ��� ù��° ��ġ
//find_last_not_of()- �־��� ���ڵ��� �ƴ� ���ڰ� �ɸ��� ������ ��ġ
 const char* FileSystem::EveryFilter="Every File(*.*)\0*.*";
 const char* FileSystem::TextureFilter="Texture File(*.png,*.jpg,*.bmp)\0.png;*.jpg;*.bmp;\0";
 const char* FileSystem::ShaderFilter="Shader File(*.hlsl)\0*.hlsl;\0";
 const char* FileSystem::XmlFilter ="Xml File(*.xml)\0*.xml;\0";

 vector<string>FileSystem::supportImageFormats = {".png",".jpg",".bmp"};
 vector<string>FileSystem::supportAudioFormats = {".wav",".mp3",".mp4"};
 vector<string>FileSystem::supportShaderFormats = {".hlsl"};
 vector<string>FileSystem::supportBinaryFormats = {""};
void FileSystem::OpenFileDialog(function<void(string)> func, const char * filter, const char * directory)
{
	char fileName[255];
	ZeroMemory(fileName, 255);

	OPENFILENAMEA ofn;
	ZeroMemory(&ofn, sizeof(OPENFILENAMEA));
	ofn.lStructSize = sizeof(OPENFILENAMEA);

	ofn.hwndOwner = Settings::Get()->GetWindowHandle();
	ofn.lpstrFilter = filter;
	ofn.lpstrFile = fileName;
	ofn.nMaxFile = 255;
	ofn.lpstrInitialDir = directory;
	ofn.Flags = OFN_NOCHANGEDIR;//�ѹ��� ��δ� �״�� �����ȴ�.

	if (GetOpenFileNameA(&ofn) == TRUE)//TRUE�� ����â�� �������̴�.
	{
		string file = GetFrileNameFromPath(fileName);
		
		if (func != nullptr)
			func(file);
	}
}

void FileSystem::SaveFileDialog(function<void(string)> func, const char * filter, const char * directory)
{
	char fileName[255];
	ZeroMemory(fileName, 255);

	OPENFILENAMEA ofn;
	ZeroMemory(&ofn, sizeof(OPENFILENAMEA));
	ofn.lStructSize = sizeof(OPENFILENAMEA);

	ofn.hwndOwner = Settings::Get()->GetWindowHandle();
	ofn.lpstrFilter = filter;
	ofn.lpstrFile = fileName;
	ofn.nMaxFile = 255;
	ofn.lpstrInitialDir = directory;
	ofn.Flags = OFN_NOCHANGEDIR;//�ѹ��� ��δ� �״�� �����ȴ�.

	if (GetSaveFileNameA(&ofn) == TRUE)//TRUE�� ����â�� �������̴�.
	{
		string file = GetFrileNameFromPath(fileName);
		if (func != nullptr)
			func(file);
	}
}

const bool FileSystem::Create_Directory(const string & path)
{
	bool result = false;

	try
	{
		result = create_directories(path);//�� ��ο��ٰ� ������ ������ش�. 
	}
	catch (filesystem_error error)
	{
		MessageBoxA(nullptr,error.what(),"ERROR!",MB_OK);
	}

	return result;
}

const bool FileSystem::Delete_Directory(const string & directory)
{
	bool result = false;

	try
	{
		result = remove_all(directory)>0; //��ȯ������ ������ ������� ���´�. 
	}
	catch (filesystem_error error)
	{
		MessageBoxA(nullptr, error.what(), "ERROR!", MB_OK);
	}

	return result;
}

const bool FileSystem::Delete_File(const string & path)
{
	bool result = false;

	try
	{
		result = remove(path); //��ȯ������ ������ ������� ���´�. 
	}
	catch (filesystem_error error)
	{
		MessageBoxA(nullptr, error.what(), "ERROR!", MB_OK);
	}

	return result;
}

const bool FileSystem::Copy_File(const string & src, const string & dst)
{
	if (src == dst) return false;
	if (!ExistDirectory(GetDirectoryFromPath(dst)))//�ش� ��ΰ� �������� �ʴ´ٸ�
		Create_Directory(GetDirectoryFromPath(dst));
		

	bool result = false;

	try
	{
		result = copy_file(src,dst,copy_options::overwrite_existing); //������ ������ 
	}
	catch (filesystem_error error)
	{
		MessageBoxA(nullptr, error.what(), "ERROR!", MB_OK);
	}

	return result;
}

const bool FileSystem::IsDirectory(const string & path) //���°� ������ �����̳� �Ǵ�
{
	bool result = false;

	try
	{
		result = is_directory(path); //��ȯ������ ������ ������� ���´�. 
	}
	catch (filesystem_error error)
	{
		MessageBoxA(nullptr, error.what(), "ERROR!", MB_OK);
	}

	return result;
}

const bool FileSystem::ExistDirectory(const string & directory)
{
	bool result = false;

	try
	{
		result = exists(directory); //��ȯ������ ������ ������� ���´�. 
	}
	catch (filesystem_error error)
	{
		MessageBoxA(nullptr, error.what(), "ERROR!", MB_OK);
	}

	return result;
}

const bool FileSystem::ExistFile(const string & path)
{
	bool result = false;

	try
	{
		result = exists(path); //��ȯ������ ������ ������� ���´�. 
	}
	catch (filesystem_error error)
	{
		MessageBoxA(nullptr, error.what(), "ERROR!", MB_OK);
	}

	return result;
}

const string FileSystem::GetFrileNameFromPath(const string & path)
{
	//C:\\SGA\\2D\\Tree.png--------->Tree.png
	auto lastIndex = path.find_last_of("\\/");
	auto fileName = path.substr(lastIndex + 1, path.length());//�и���Ű��.
	return fileName;
}

const string FileSystem::GetIntactFileNameFromPath(const string & path)
{
	//Tree�� �̴´�.
	auto fileName = GetFrileNameFromPath(path);
	auto lastIndex = fileName.find_last_of('.');
	auto intactFileName = fileName.substr(0, lastIndex);
	return intactFileName;
}

const string FileSystem::GetDirectoryFromPath(const string & path)
{
	//C:\\SGA\\2D\\Tree.png--------->\\SGA\\2D\\====
	auto lastIndex = path.find_last_of("\\/");
	auto directory = path.substr(0, lastIndex + 1);
	return directory;
}

const string FileSystem::GetExtensionFromPath(const string & path)//Ȯ����
{//C:\\SGA\\2D\\Tree.png--------->.png
	auto lastIndex = path.find_last_of('.');
	if (lastIndex != string::npos)
	{
		return path.substr(lastIndex, path.length());
	}
	return "";
}

const string FileSystem::GetRelativeFilePath(const string & absolutePath)
{
	//���� ��θ� ����
	path p = absolute(absolutePath);
	path r = absolute(GetWorkingDirectory());

	//��Ʈ ��ΰ� �ٸ���� ������ ��ȯ
	if (p.root_path() != r.root_path())
		return p.generic_string();

	path result;

	//�� ��ΰ� �������� ������ üũ
	path::const_iterator iter_path = p.begin();
	path::const_iterator iter_relative = r.begin();

	while (
		*iter_path == *iter_relative &&
		iter_path != p.end() &&
		iter_relative != r.end())
	{
		iter_path++;
		iter_relative++;
	}

	//relative�� ���� �� ��ū������ ..�� �߰�
	if (iter_relative != r.end())
	{
		iter_relative++;
		while (iter_relative != r.end())
		{
			result /= "..";
			iter_relative++;
		}
	}
	path tempa = "leehyung";
	path tempb = "hyungsung";

	tempa += tempb;

	//���� ��� �߰�
	while (iter_path != p.end())
	{
		result /= *iter_path;
		iter_path++;
	}

	return result.generic_string(); //�м� �ָ�����
}

const string FileSystem::GetWorkingDirectory()
{
	//../Root/
	return current_path().generic_string() + "/";
}

const string FileSystem::GetParentDirectory(const string & directory)
{
	//Hello//Hi//J//
	auto lastIndex = directory.find_last_of("\\/");
	auto result = directory;

	if (lastIndex == string::npos)//��ã����
		return result;
	if (lastIndex == directory.length() - 1)
	{
		result = result.substr(0, lastIndex - 1);
		return GetParentDirectory(result);
	}
	return result.substr(0,lastIndex)+"/";
}

const vector<string> FileSystem::GetDirectoriesInDirectory(const string & directory)
{
	vector<string> subDirectories;

	directory_iterator iter(directory);

	for (auto p : iter )
	{
		if (!is_directory(p.status()))
			continue;//directory�� ���¸� �޾Ƽ� �������� ������� �ľ��Ѵ�. ��ΰ��ƴϸ� �׳� �Ѿ��
		subDirectories.emplace_back(p.path().generic_string()); //����̸� ������ �߰��Ѵ�. 
	}
	return subDirectories;
}

const vector<string> FileSystem::GetFilesInDirectory(const string & directory)
{
	vector<string> files;

	directory_iterator iter(directory);

	for (auto p : iter )
	{
		if (!is_regular_file(p.status()))
			continue;//directory�� ���¸� �޾Ƽ� �������� ������� �ľ��Ѵ�. ��ΰ��ƴϸ� �׳� �Ѿ��
		files.emplace_back(p.path().generic_string()); //����̸� ������ �߰��Ѵ�. 
	}
	return files;
}

const bool FileSystem::IsSupportImageFile(const string & path)
{
	string fileExtension = GetExtensionFromPath(path);

	auto supportFormats = GetSupportImageFormats();
	for (const auto& format : supportFormats)
	{
		if (fileExtension == format || fileExtension ==ToUpper(format))//tree.png,tree.PNG����
			return true;
	}
	return false;
}

const bool FileSystem::IsSupportAudioFile(const string & path)
{
	string fileExtension = GetExtensionFromPath(path);

	auto supportFormats = GetSupportAudioFormats();
	for (const auto& format : supportFormats)
	{
		if (fileExtension == format || fileExtension == ToUpper(format))//tree.png,tree.PNG����
			return true;
	}
	return false;
}

const bool FileSystem::IsSupportShaderFile(const string & path)
{
	string fileExtension = GetExtensionFromPath(path);

	auto supportFormats = GetSupportShaderFormats();
	for (const auto& format : supportFormats)
	{
		if (fileExtension == format || fileExtension == ToUpper(format))//tree.png,tree.PNG����
			return true;
	}
	return false;
}

const bool FileSystem::IsSupportBinaryFile(const string & path)
{
	string fileExtension = GetExtensionFromPath(path);

	auto supportFormats = GetSupportBinaryFormats();
	for (const auto& format : supportFormats)
	{
		if (fileExtension == format || fileExtension == ToUpper(format))//tree.png,tree.PNG����
			return true;
	}
	return false;
}

void FileSystem::ReplaceAll(string & str, const string & from, const string & to)
{
	size_t startPos = 0;
	while ((startPos=str.find(from,startPos))!=string::npos)
	{
		str.replace(startPos,from.length(),to);
		startPos += to.length();//�ٲۺκ� �ٽ� �˻���ϰ� �����ش�.
	}
}

const string FileSystem::ToUpper(const string & lower)
{
	string upper;
	for (const auto& chracter : lower)
		upper += toupper(chracter);
	return upper;
}

const string FileSystem::ToLower(const string & upper)
{
	string lower;
	for (const auto& chracter : upper)
		lower += tolower(chracter);
	return lower;
}

const wstring FileSystem::ToWstring(const string & value)
{
	wstring result = L"";
	result.assign(value.begin(), value.end());

	return result;

	
}

const string FileSystem::ToString(const wstring & value)
{
	string result = "";
	result.assign(value.begin(), value.end());

	return result;
}
