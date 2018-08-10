///////////////////////////////////////////////////////////
/// ��`�ꗗ
/// 
/// 
///////////////////////////////////////////////////////////
#pragma once


///////////////////////////////////////////////////////////
///BUILD_ERROR�p�N���X
///
///false���𖢒�`�ɂ��邱�Ƃ�
///�Ӑ}�I�Ƀr���h�Ɏ��s����悤�ɂ���
///////////////////////////////////////////////////////////
template<bool T> struct BuildError;
template<> struct BuildError < true > { };


//=========================================================
//define
///--------------------------------------------------------
///�r���h�̒i�K�ňُ�����m����
#define BUILD_ERROR(result) BuildError<result>()
///--------------------------------------------------------
///�R�s�[�֎~�N���X
#define NO_COPY_CLASS(class_name)						\
	class_name(const class_name&) = delete;				\
	class_name& operator=(const class_name&) = delete

//�r�b�g
#define BIT_OR(a , b)			((a) | (b))			///< OR
#define BIT_AND(a , b)			((a) & (b))			///< AND
#define BIT_XOR(a , b)			((a) ^ (b))			///< XOR
#define BIT_NOT(val)			(~(val))			///< ���]
#define BIT_SHIFT_L(val , move)	((val) << (move))	///< �V�t�g���Z��
#define BIT_SHIFT_R(val , move)	((val) >> (move))	///< �V�t�g���Z�E


//�ϊ�
#define TO_WSTR(str) L#str

