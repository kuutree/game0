///////////////////////////////////////////////////////////
///DirectXポインター
///
///
///////////////////////////////////////////////////////////
#pragma once
//=========================================================
//include
#include <Base/Debug/Assert.h>


namespace gr {
///////////////////////////////////////////////////////////
///DirectXポインター
///
///
///////////////////////////////////////////////////////////
template <class T>
class DirectXPtr
{
	//=========================================================
	//using
	using SelfType = DirectXPtr<T>;
	using Ptr	   = T*;
	using Ref	   = T&;

	//=========================================================
	//val
	Ptr m_ptr;
public:
	//=========================================================
	//func
	//コンストラクタ・デストラクタ
	DirectXPtr() { m_ptr = nullptr; }
	DirectXPtr(const SelfType& src) { _Copy(src); }
	DirectXPtr(Ptr src) { _Copy(src); }
	~DirectXPtr() { Release(); }

	///参照カウントを減らしてオブジェクトを内部で解放
	void Release() 
	{
		if (m_ptr != nullptr)
		{
			m_ptr->Release();
			m_ptr = nullptr;
		}
	}

	//=========================================================
	//アクセサ
	bool IsExist() const { return m_ptr != nullptr; }
	Ptr  Get() const	 { return m_ptr; }
private:
	//参照追加
	///-------------------------------------------------------
	///参照カウンタアップ
	void _Copy(const SelfType& src)
	{
		if (src.IsExist())
		{
			_Copy(src.m_ptr);
			m_ptr->AddRef();
		}
		else  _Copy(src.m_ptr);
	}
	///-------------------------------------------------------
	///単純コピー
	void _Copy(Ptr src) { m_ptr = src; }
public:
	//=================================================
	//演算子
	Ptr operator->() const { DB_ASSERT(m_ptr != nullptr); return m_ptr; }
	Ref operator*()  const { DB_ASSERT(m_ptr != nullptr); return *m_ptr; }
	void operator =(const SelfType& src) { Release(); _Copy(src); }
	void operator =(Ptr src) { Release(); _Copy(src); }
	bool operator==(const SelfType& src) const { return m_ptr == src.m_ptr; }
	bool operator!=(const SelfType& src) const { return m_ptr != src.m_ptr; }
};
} //namespace gr
