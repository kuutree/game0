#pragma once
//=================================================
//include
#include "../util/Singleton.h"
#include <string>


namespace base {
namespace io {
///////////////////////////////////////////////////////////
///IOシステム
///
///
///////////////////////////////////////////////////////////
class IOSystem : public base::util::Singleton<IOSystem>
{
public:
	//========================================================
	//ファイル
	bool IsExist(const wchar_t* path);						///< ファイルの存在を確認
	//=========================================================
	//ディレクトリ操作
	bool		 SetCurrentDir(const wchar_t* dir);			///< カレントディレクトリを変更
	std::wstring GetCurrentDir();							///< カレントディレクトリを設定
	bool		 DirectoryIsExist(const wchar_t* dir);		///< 指定したディレクトリが存在するか調べる
	bool		 DirectoryCreate(const wchar_t* dir);		///< ディレクトリを作成する
};
} //namespace io
} //namespace base

