#pragma once
//=================================================
//include
#include "../Util/Bit.h"
#include <stdio.h>


namespace base {
namespace io {
///////////////////////////////////////////////////////////
///�t�@�C�����o��
///
///
///////////////////////////////////////////////////////////
class IO
{
public:
	//////////////////////////////////////////////////////////
	///�t�@�C���I�[�v�����[�h
	///
	///
	//////////////////////////////////////////////////////////
	enum OpenMode
	{
		OPEN_READ	= 1,		///< �ǂݍ��ݗp�ɊJ��
		OPEN_WRITE	= 1 << 1,	///< �������ݗp�ɊJ��
		OPEN_BINARY = 1 << 2,   ///< �o�C�i���t�@�C���Ƃ��ĊJ��
		OPEN_ALL	= OPEN_READ | OPEN_WRITE | OPEN_BINARY,
	};
	//////////////////////////////////////////////////////////
	///�V�[�N�ʒu
	///
	///�ǂݍ��݂Ə������݂̗������w�肷�邱�Ƃ͏o���Ȃ�
	//////////////////////////////////////////////////////////
	enum SeekPos
	{
		SEEK_POS_TOP	 = SEEK_SET, ///< �t�@�C���̐擪�ʒu
		SEEK_POS_CURRENT = SEEK_CUR, ///< �t�@�C���̃J�����g�ʒu
		SEEK_POS_END	 = SEEK_END, ///< �t�@�C���̏I�[�ʒu
	};
	//========================================================
	//using
	using FileHandle = int;
	using OpenBitSet = base::util::Bit<OpenMode, OPEN_ALL>;
	//========================================================
	//const
	static const FileHandle INVALID_HANDLE = -1;
private:
	//========================================================
	//val
	FileHandle m_h_file;	///< �t�@�C���n���h��  �t�@�C������͂��ׂĂ��̃n���h������s����
	OpenBitSet m_open_mode;	///< �t�@�C���I�[�v�����[�h
public:
	//========================================================
	//func
	IO()  { m_h_file = INVALID_HANDLE; }							///< �R���X�g���N�^
	~IO() { Close(); }												///< �f�X�g���N�^
	//========================================================
	//�t�@�C���J��
	bool Open(const wchar_t* path, const OpenBitSet& open_mode);	///< �t�@�C�����J��
	void Close();													///< �t�@�C�������
	//========================================================
	//�t�@�C������
	bool Read(void* p_buff, size_t size) const;						///< �t�@�C���ǂݍ���
	bool Write(const void* p_buff, size_t size) const;				///< �t�@�C����������
	///-------------------------------------------------------
	///�V�[�N
	///@param[in]  pos  �V�[�N�̊�ƂȂ�ʒu
	bool Seek(SeekPos pos, int offset) const;
	//========================================================
	//�A�N�Z�T
	size_t GetFileSize() const;										///< �t�@�C���T�C�Y�擾
	size_t GetFilePos() const;										///< ���݂̃t�@�C���ʒu���擾
	bool   IsEnable() const { return m_h_file != INVALID_HANDLE; }	///�t�@�C�����J���Ă��邩
};
} //namespace io
} //namespace base

