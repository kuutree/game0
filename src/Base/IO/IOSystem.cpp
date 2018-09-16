//=========================================================
//include
#include "IOSystem.h"
#include "IO.h"
#include <Windows.h>


namespace base {
namespace io {
//=========================================================
//ファイルの存在を確認
bool IOSystem::IsExist(const wchar_t* path)
{
	IO  io;
	bool result = io.Open(path, IO::OPEN_READ);
	io.Close();

	return result;
}


//=========================================================
//カレントディレクトリを変更
bool IOSystem::SetCurrentDir(const wchar_t* dir)
{
	bool result = SetCurrentDirectory(dir) != 0;

	return result;
}


//=========================================================
//カレントディレクトリを設定
std::wstring IOSystem::GetCurrentDir()
{
	wchar_t		 tmp[MAX_PATH];
	DWORD		 len = GetCurrentDirectory(MAX_PATH, tmp);
	std::wstring dir = (len != 0) ? tmp : L"";
	return dir; 
}


//=========================================================
//指定したディレクトリが存在するか調べる
bool IOSystem::DirectoryIsExist(const wchar_t* dir)
{
	DWORD attr = GetFileAttributes(dir);
	return attr != -1 && BIT_AND(attr, FILE_ATTRIBUTE_DIRECTORY) != 0;
}


//=========================================================
//ディレクトリを作成する
bool IOSystem::DirectoryCreate(const wchar_t* dir)
{
	return CreateDirectory(dir, nullptr) == TRUE;
}
} //namespace io
} //namespace base

