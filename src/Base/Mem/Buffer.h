#pragma once
//=========================================================
//include
#include "Allocator.h"
#include "../debug/Assert.h"


namespace base{
namespace mem{
///////////////////////////////////////////////////////////
///���`�z��
///
///////////////////////////////////////////////////////////
template<class T, class _Allocator = Allocator<T> >
class Buffer : private _Allocator
{
public:
	//=========================================================
	//type
	typedef Buffer<T, _Allocator> SelfType;
	typedef T  ValueType;
	typedef T* Iterator;
	typedef _Allocator AllocatorType;
private:
	//=========================================================
	//value
	ValueType* m_p_objects;		///< �z��I�u�W�F�N�g
	size_t     m_use_size;		///< �g�p���̃o�b�t�@�T�C�Y
	size_t     m_alloc_size;	///< ���g�p���܂߂��m�ۍς݃o�b�t�@�T�C�Y
	//=========================================================
	//private func
	///--------------------------------------------------------
	///�Ċm��
	///
	///�����̔z����̗L���I�u�W�F�N�g�͐V�K�z��փR�s�[�����
	void _Realloc(size_t size)
	{
		ValueType* p_objects = Allocate(size);

		//�L���ȃI�u�W�F�N�g��V�����̈�Ɉړ�����
		//�����_��
		ValueType* p_dst = p_objects;
		auto cmd = [this, &p_dst](Iterator ite)
		{
			this->Constructor(p_dst, *ite);
			this->Destructor(ite);
			++p_dst;
		};
		Foreach(&cmd);

		m_p_objects = p_objects;
		m_alloc_size = size;
	}
public:
	//=========================================================
	//func
	///--------------------------------------------------------
	///�R���X�g���N�^
	Buffer()
	{
		m_p_objects = nullptr;
		m_use_size = m_alloc_size = 0;
	}
	///--------------------------------------------------------
	///�f�X�g���N�^
	~Buffer() { Clear(); }
	///--------------------------------------------------------
	///�w��T�C�Y�̔z���\�񂷂�
	///
	///���ɂ��̃T�C�Y�ȏ�̔z�񂪂���ꍇ�͖��������
	void Reserve(size_t size)  { if (m_alloc_size < size)  _Realloc(size); }
	///--------------------------------------------------------
	///�w��T�C�Y�̔z���L���ɂ���
	///
	///@attention ���݂̗L���z�񂩂�s���������V���ɃI�u�W�F�N�g���쐬����̂ŘA���Ăяo���ɒ���
	void Resize(size_t size)
	{
		//���݂̗L���T�C�Y��菬����?
		if (size < m_use_size)
		{
			//size�̒l���I�[�o�[���Ă���I�u�W�F�N�g���폜
			//�����_��
			auto cmd = [this](Iterator ite) { this->Destructor(ite); };
			Foreach(size, m_use_size - size, &cmd);

			m_use_size = size;
		}
		//���݂̗L���T�C�Y���傫��?
		if (size > m_use_size)
		{
			//�������̍Ċm�ۂ��K�v?
			if (m_alloc_size < size)	_Realloc(size);

			size_t offset = m_use_size;
			m_use_size = size;

			//���݂̗L���I�u�W�F�N�g������s�����Ă��鐔�����V���ɃI�u�W�F�N�g���쐬
			//�����_��
			auto cmd = [this](Iterator ite) { this->Constructor(ite); };
			Foreach(offset, m_use_size - offset, &cmd);
		}
	}
	///--------------------------------------------------------
	///�N���A
	void Clear()
	{
		if (m_p_objects != nullptr)
		{
			//�L���I�u�W�F�N�g�̍폜
			ClearUseObjects();

			//�z��̉��
			Deallocate(m_p_objects);
			m_p_objects = nullptr;
			m_alloc_size = 0;
		}
	}
	///--------------------------------------------------------
	///�S�L���I�u�W�F�N�g�폜
	///
	///�������͉�����Ȃ�
	void ClearUseObjects()
	{
		if (m_p_objects != nullptr)
		{
			//�L���I�u�W�F�N�g�̉��
			//�����_��
			auto cmd = [this](Iterator ite) { this->Destructor(ite); };
			Foreach(&cmd);

			m_use_size = 0;
		}
	}
	///--------------------------------------------------------
	///�z��̐擪���w���A�h���X��Ԃ�
	const ValueType* GetConstAddr() const { return m_p_objects; }
	///--------------------------------------------------------
	///�z��̐擪���w���A�h���X��Ԃ�
	ValueType* GetAddr() const { return m_p_objects; }
	///--------------------------------------------------------
	///�L���Ȕz��̃T�C�Y���擾
	size_t GetSize() const { return m_use_size; }
	///--------------------------------------------------------
	///�z��̃o�C�g�P�ʂł̃T�C�Y���擾
	size_t GetByteSize() const { return sizeof(ValueType) * m_use_size; }
	///--------------------------------------------------------
	///�z��̐擪��Ԃ�
	///@return �z�񂪋�̏ꍇ��NULL
	Iterator Begin() const { return m_p_objects; }
	Iterator begin() const { return m_p_objects; }
	///--------------------------------------------------------
	///�z��̏I�[��Ԃ�
	///@return �z�񂪋�̏ꍇ��NULL
	Iterator End() const { return m_p_objects + m_use_size; }
	Iterator end() const { return m_p_objects + m_use_size; }
	///--------------------------------------------------------
	///�w�肵�����������ׂĂ̗v�f�ɍs��
	template <class FuncObject>
	void Foreach(FuncObject* p_func) { Foreach(Begin(), End(), p_func); }
	///--------------------------------------------------------
	///�w�肵���������X���C�X�͈͓��̗v�f�ɍs��
	template <class FuncObject>
	void Foreach(size_t index, size_t size, FuncObject* p_func)
	{
		DB_ASSERT(index + size <= GetSize());

		Iterator ite = Begin() + index;
		Foreach(ite, ite + size, p_func);
	}
	//=========================================================
	//static func
	///--------------------------------------------------------
	///�w�肵���������w��͈͓��̗v�f�ɍs��(static��)
	template <class FuncObject>
	static void Foreach(Iterator ite, Iterator end, FuncObject* p_func) { for (; ite != end; ++ite)  (*p_func)(ite); }
	//=========================================================
	//operator func
	///--------------------------------------------------------
	///�w��ʒu�̗v�f�擾
	ValueType& operator[](size_t index) const { DB_ASSERT(index < GetSize()); return *(Begin() + index); }
};
}//namespace mem
}//namespace base