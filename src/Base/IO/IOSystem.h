#pragma once
//=================================================
//include
#include "../util/Singleton.h"
#include <string>


namespace base {
namespace io {
///////////////////////////////////////////////////////////
///IO�V�X�e��
///
///
///////////////////////////////////////////////////////////
class IOSystem : public base::util::Singleton<IOSystem>
{
public:
	//========================================================
	//�t�@�C��
	bool IsExist(const wchar_t* path);						///< �t�@�C���̑��݂��m�F
	//=========================================================
	//�f�B���N�g������
	bool		 SetCurrentDir(const wchar_t* dir);			///< �J�����g�f�B���N�g����ύX
	std::wstring GetCurrentDir();							///< �J�����g�f�B���N�g����ݒ�
	bool		 DirectoryIsExist(const wchar_t* dir);		///< �w�肵���f�B���N�g�������݂��邩���ׂ�
	bool		 DirectoryCreate(const wchar_t* dir);		///< �f�B���N�g�����쐬����
};
} //namespace io
} //namespace base

