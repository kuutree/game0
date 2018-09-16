#pragma once
//=========================================================
//include
#include <string>


namespace base {
namespace io {
///////////////////////////////////////////////////////////
///パス情報
///
///
///////////////////////////////////////////////////////////
struct Path
{
	//========================================================
	//val
	std::wstring full_path;	///< フルパス
	std::wstring dir;		///< ディレクトリ名
	std::wstring file;		///< ファイル名
	std::wstring ext;		///< 拡張子

	//========================================================
	//func
	Path() { }
	Path(const wchar_t* path) { SetPath(path); }
	void SetPath(const wchar_t* path);	///< パス情報設定
};
} //namespace io
} //namespace base

