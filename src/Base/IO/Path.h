#pragma once
//=========================================================
//include
#include <string>


namespace base {
namespace io {
///////////////////////////////////////////////////////////
///�p�X���
///
///
///////////////////////////////////////////////////////////
struct Path
{
	//========================================================
	//val
	std::wstring full_path;	///< �t���p�X
	std::wstring dir;		///< �f�B���N�g����
	std::wstring file;		///< �t�@�C����
	std::wstring ext;		///< �g���q

	//========================================================
	//func
	Path() { }
	Path(const wchar_t* path) { SetPath(path); }
	void SetPath(const wchar_t* path);	///< �p�X���ݒ�
};
} //namespace io
} //namespace base

