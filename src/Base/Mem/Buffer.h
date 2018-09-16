#pragma once
//=========================================================
//include
#include "Allocator.h"
#include "../debug/Assert.h"


namespace base{
namespace mem{
///////////////////////////////////////////////////////////
///線形配列
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
	ValueType* m_p_objects;		///< 配列オブジェクト
	size_t     m_use_size;		///< 使用中のバッファサイズ
	size_t     m_alloc_size;	///< 未使用を含めた確保済みバッファサイズ
	//=========================================================
	//private func
	///--------------------------------------------------------
	///再確保
	///
	///既存の配列内の有効オブジェクトは新規配列へコピーされる
	void _Realloc(size_t size)
	{
		ValueType* p_objects = Allocate(size);

		//有効なオブジェクトを新しい領域に移動する
		//ラムダ式
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
	///コンストラクタ
	Buffer()
	{
		m_p_objects = nullptr;
		m_use_size = m_alloc_size = 0;
	}
	///--------------------------------------------------------
	///デストラクタ
	~Buffer() { Clear(); }
	///--------------------------------------------------------
	///指定サイズの配列を予約する
	///
	///既にそのサイズ以上の配列がある場合は無視される
	void Reserve(size_t size)  { if (m_alloc_size < size)  _Realloc(size); }
	///--------------------------------------------------------
	///指定サイズの配列を有効にする
	///
	///@attention 現在の有効配列から不足分だけ新たにオブジェクトを作成するので連続呼び出しに注意
	void Resize(size_t size)
	{
		//現在の有効サイズより小さい?
		if (size < m_use_size)
		{
			//sizeの値よりオーバーしているオブジェクトを削除
			//ラムダ式
			auto cmd = [this](Iterator ite) { this->Destructor(ite); };
			Foreach(size, m_use_size - size, &cmd);

			m_use_size = size;
		}
		//現在の有効サイズより大きい?
		if (size > m_use_size)
		{
			//メモリの再確保が必要?
			if (m_alloc_size < size)	_Realloc(size);

			size_t offset = m_use_size;
			m_use_size = size;

			//現在の有効オブジェクト数から不足している数だけ新たにオブジェクトを作成
			//ラムダ式
			auto cmd = [this](Iterator ite) { this->Constructor(ite); };
			Foreach(offset, m_use_size - offset, &cmd);
		}
	}
	///--------------------------------------------------------
	///クリア
	void Clear()
	{
		if (m_p_objects != nullptr)
		{
			//有効オブジェクトの削除
			ClearUseObjects();

			//配列の解放
			Deallocate(m_p_objects);
			m_p_objects = nullptr;
			m_alloc_size = 0;
		}
	}
	///--------------------------------------------------------
	///全有効オブジェクト削除
	///
	///メモリは解放しない
	void ClearUseObjects()
	{
		if (m_p_objects != nullptr)
		{
			//有効オブジェクトの解放
			//ラムダ式
			auto cmd = [this](Iterator ite) { this->Destructor(ite); };
			Foreach(&cmd);

			m_use_size = 0;
		}
	}
	///--------------------------------------------------------
	///配列の先頭を指すアドレスを返す
	const ValueType* GetConstAddr() const { return m_p_objects; }
	///--------------------------------------------------------
	///配列の先頭を指すアドレスを返す
	ValueType* GetAddr() const { return m_p_objects; }
	///--------------------------------------------------------
	///有効な配列のサイズを取得
	size_t GetSize() const { return m_use_size; }
	///--------------------------------------------------------
	///配列のバイト単位でのサイズを取得
	size_t GetByteSize() const { return sizeof(ValueType) * m_use_size; }
	///--------------------------------------------------------
	///配列の先頭を返す
	///@return 配列が空の場合はNULL
	Iterator Begin() const { return m_p_objects; }
	Iterator begin() const { return m_p_objects; }
	///--------------------------------------------------------
	///配列の終端を返す
	///@return 配列が空の場合はNULL
	Iterator End() const { return m_p_objects + m_use_size; }
	Iterator end() const { return m_p_objects + m_use_size; }
	///--------------------------------------------------------
	///指定した処理をすべての要素に行う
	template <class FuncObject>
	void Foreach(FuncObject* p_func) { Foreach(Begin(), End(), p_func); }
	///--------------------------------------------------------
	///指定した処理をスライス範囲内の要素に行う
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
	///指定した処理を指定範囲内の要素に行う(static版)
	template <class FuncObject>
	static void Foreach(Iterator ite, Iterator end, FuncObject* p_func) { for (; ite != end; ++ite)  (*p_func)(ite); }
	//=========================================================
	//operator func
	///--------------------------------------------------------
	///指定位置の要素取得
	ValueType& operator[](size_t index) const { DB_ASSERT(index < GetSize()); return *(Begin() + index); }
};
}//namespace mem
}//namespace base