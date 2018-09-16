//=========================================================
//include
#include "New.h"
#include <stdlib.h>
#include "../thread/CriticalSection.h"
#include "../debug/Assert.h"


///////////////////////////////////////////////////////////
///アロケータ
///
///隠蔽するためにcppに記述
///////////////////////////////////////////////////////////
class Allocator
{
	//////////////////////////////////////////////////////////
	///全体のアロケート情報
	///
	//////////////////////////////////////////////////////////
	struct AllocInfo
	{
		int cnt;	///< アロケートカウント
		AllocInfo() { cnt = 0; }
	};
private:
	//========================================================
	//val
	AllocInfo					  m_alloc_info;
	base::thread::CriticalSection m_critical_section;
public:
	//========================================================
	//func
	///-------------------------------------------------------
	///コンストラクタ
	Allocator() {}
	///-------------------------------------------------------
	///デストラクタ
	~Allocator()
	{
		m_critical_section.Lock();
		DB_ASSERT(m_alloc_info.cnt == 0);
		m_critical_section.Unlock();
	}
	///-------------------------------------------------------
	///確保
	void* Malloc(size_t size, size_t alignment)
	{
		m_critical_section.Lock();

		//確保
		void* p = _aligned_malloc(size, alignment);
		DB_ASSERT(p != NULL);

		//アロケート情報更新
		++m_alloc_info.cnt;

		m_critical_section.Unlock();

		return p;
	}
	///-------------------------------------------------------
	///解放
	void Free(void* p)
	{
		m_critical_section.Lock();

		//解放
		_aligned_free(p);

		//アロケート情報更新
		--m_alloc_info.cnt;

		m_critical_section.Unlock();
	}
	///-------------------------------------------------------
	///現在のメモリ確保中の数を取得
	int GetAllocCnt()
	{
		m_critical_section.Lock();
		int cnt = m_alloc_info.cnt;
		m_critical_section.Unlock();

		return cnt;
	}
};


//=========================================================
//グローバル変数
Allocator g_allocator;


namespace base{
namespace mem{
//=========================================================
//確保
void* Malloc(size_t size, size_t alignment) { return g_allocator.Malloc(size, alignment); }


//=========================================================
//解放
void Free(void* p) { g_allocator.Free(p); }


//=========================================================
//現在のメモリ確保中の数を取得
int GetAllocCnt() { return g_allocator.GetAllocCnt(); }
}//namespace mem
}//namespace base
