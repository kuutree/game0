#pragma once
//========================================================
//include
#include "..\Define.h"
#include "..\debug\Assert.h"


namespace base {
namespace util {
///////////////////////////////////////////////////////////
///シングルトン
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
	Singleton() { /*何もしない*/ }
public:
	//========================================================
	//func
	virtual ~Singleton() { /*何もしない*/ }
	//========================================================
	//static func
	///-------------------------------------------------------
	///明示的な初期化
	static void Initialize()
	{
		if (sp_instance)	Finalize();
		sp_instance = new T();
	}
	///-------------------------------------------------------
	///明示的な終了処理
	static void Finalize()
	{
		if (sp_instance)
		{
			delete sp_instance;
			sp_instance = nullptr;
		}
	}
	///-------------------------------------------------------
	///インスタンス取得
	static T& GetInstance()
	{
		DB_ASSERT(sp_instance != nullptr); 
		return *sp_instance;
	}
};
template <class T> T* Singleton<T>::sp_instance = nullptr;
} //namespace util
} //namespace base