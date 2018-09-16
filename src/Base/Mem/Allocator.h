#pragma once
//=========================================================
//include
#include "New.h"


namespace base {
namespace mem {
///////////////////////////////////////////////////////////
///指定型用のメモリ割り当て
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
	//メモリ確保・解放
	///--------------------------------------------------------
	///指定バイト数のメモリ確保
	ValueType* Allocate(size_t size)  { return static_cast<ValueType*>(base::mem::Malloc(sizeof(ValueType) * size, ALIGNMENT)); }
	///--------------------------------------------------------
	///メモリ解放
	///@param  p_object  NULL不可
	void Deallocate(ValueType* p_object)  { base::mem::Free(p_object); }
	//=========================================================
	//配置new・delete
	///--------------------------------------------------------
	///指定オブジェクトのコンストラクタ呼び出し
	///@param  p_object  NULL不可
	void Constructor(ValueType* p_object)  { new(p_object)ValueType; }
	///--------------------------------------------------------
	///指定オブジェクトのコンストラクタ呼び出し
	///@param  p_object  NULL不可
	template<class InitVal>
	void Constructor(ValueType* p_object , const InitVal& src)  { new(p_object)ValueType(src); }
	///--------------------------------------------------------
	///指定オブジェクトのデストラクタ呼び出し
	///@param  p_object  NULL不可
	void Destructor(ValueType* p_object)	{ p_object->~ValueType(); }
};
} //namespace mem
} //namespace base
