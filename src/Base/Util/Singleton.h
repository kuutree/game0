#pragma once
//========================================================
//include
#include "..\Define.h"
#include "..\debug\Assert.h"


namespace base {
namespace util {
///////////////////////////////////////////////////////////
///�V���O���g��
///
///
///////////////////////////////////////////////////////////
template <class T>
class Singleton
{
	NO_COPY_CLASS(Singleton);
	//========================================================
	//static val
	static T* sp_instance;
protected:
	Singleton() { /*�������Ȃ�*/ }
public:
	//========================================================
	//func
	virtual ~Singleton() { /*�������Ȃ�*/ }
	//========================================================
	//static func
	///-------------------------------------------------------
	///�����I�ȏ�����
	static void Initialize()
	{
		if (sp_instance)	Finalize();
		sp_instance = new T();
	}
	///-------------------------------------------------------
	///�����I�ȏI������
	static void Finalize()
	{
		if (sp_instance)
		{
			delete sp_instance;
			sp_instance = nullptr;
		}
	}
	///-------------------------------------------------------
	///�C���X�^���X�擾
	static T& GetInstance()
	{
		DB_ASSERT(sp_instance != nullptr); 
		return *sp_instance;
	}
};
template <class T> T* Singleton<T>::sp_instance = nullptr;
} //namespace util
} //namespace base