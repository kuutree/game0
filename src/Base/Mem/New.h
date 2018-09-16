///////////////////////////////////////////////////////////
///new・deleteオーバーロード
///
///
///////////////////////////////////////////////////////////
#pragma once
//=========================================================
//include
#include <new.h>


namespace base{
namespace mem{
//=========================================================
//const
static const size_t DEFAULT_ALIGNMENT = 16;
//=========================================================
//func
///--------------------------------------------------------
///確保
void* Malloc(size_t size, size_t alignment);
///--------------------------------------------------------
///解放
void Free(void* p);
///--------------------------------------------------------
///現在のメモリ確保中の数を取得
int GetAllocCnt();
}//namespace mem
}//namespace base


//=========================================================
//確保
inline void* operator new(size_t size){ return base::mem::Malloc(size, base::mem::DEFAULT_ALIGNMENT); }
inline void* operator new[](size_t size) { return base::mem::Malloc(size, base::mem::DEFAULT_ALIGNMENT); }
//=========================================================
//アライメント確保
inline void* operator new(size_t size, size_t aligment){ return base::mem::Malloc(size, aligment); }
inline void* operator new[](size_t size, size_t aligment){ return base::mem::Malloc(size, aligment); }
//=========================================================
//解放
inline void operator delete(void* p) { base::mem::Free(p); }
inline void operator delete[](void* p) { base::mem::Free(p); }
//=========================================================
//アライメント開放
inline void operator delete(void* p, size_t aligment){ base::mem::Free(p); }
inline void operator delete[](void* p, size_t aligment){ base::mem::Free(p); }

