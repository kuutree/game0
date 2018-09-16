#pragma once
//=========================================================
//include
#include "New.h"


namespace base {
namespace mem {
///////////////////////////////////////////////////////////
///�w��^�p�̃��������蓖��
///
///
///////////////////////////////////////////////////////////
template<class T>
class Allocator
{
private:
	//=========================================================
	//type
	typedef T ValueType;
	//=========================================================
	//const
	static const size_t ALIGNMENT = (__alignof(ValueType) > base::mem::DEFAULT_ALIGNMENT) ? __alignof(ValueType) : base::mem::DEFAULT_ALIGNMENT;
public:
	//=========================================================
	//�������m�ہE���
	///--------------------------------------------------------
	///�w��o�C�g���̃������m��
	ValueType* Allocate(size_t size)  { return static_cast<ValueType*>(base::mem::Malloc(sizeof(ValueType) * size, ALIGNMENT)); }
	///--------------------------------------------------------
	///���������
	///@param  p_object  NULL�s��
	void Deallocate(ValueType* p_object)  { base::mem::Free(p_object); }
	//=========================================================
	//�z�unew�Edelete
	///--------------------------------------------------------
	///�w��I�u�W�F�N�g�̃R���X�g���N�^�Ăяo��
	///@param  p_object  NULL�s��
	void Constructor(ValueType* p_object)  { new(p_object)ValueType; }
	///--------------------------------------------------------
	///�w��I�u�W�F�N�g�̃R���X�g���N�^�Ăяo��
	///@param  p_object  NULL�s��
	template<class InitVal>
	void Constructor(ValueType* p_object , const InitVal& src)  { new(p_object)ValueType(src); }
	///--------------------------------------------------------
	///�w��I�u�W�F�N�g�̃f�X�g���N�^�Ăяo��
	///@param  p_object  NULL�s��
	void Destructor(ValueType* p_object)	{ p_object->~ValueType(); }
};
} //namespace mem
} //namespace base
