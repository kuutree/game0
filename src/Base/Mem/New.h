///////////////////////////////////////////////////////////
///new�Edelete�I�[�o�[���[�h
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
///�m��
void* Malloc(size_t size, size_t alignment);
///--------------------------------------------------------
///���
void Free(void* p);
///--------------------------------------------------------
///���݂̃������m�ے��̐����擾
int GetAllocCnt();
}//namespace mem
}//namespace base


//=========================================================
//�m��
inline void* operator new(size_t size){ return base::mem::Malloc(size, base::mem::DEFAULT_ALIGNMENT); }
inline void* operator new[](size_t size) { return base::mem::Malloc(size, base::mem::DEFAULT_ALIGNMENT); }
//=========================================================
//�A���C�����g�m��
inline void* operator new(size_t size, size_t aligment){ return base::mem::Malloc(size, aligment); }
inline void* operator new[](size_t size, size_t aligment){ return base::mem::Malloc(size, aligment); }
//=========================================================
//���
inline void operator delete(void* p) { base::mem::Free(p); }
inline void operator delete[](void* p) { base::mem::Free(p); }
//=========================================================
//�A���C�����g�J��
inline void operator delete(void* p, size_t aligment){ base::mem::Free(p); }
inline void operator delete[](void* p, size_t aligment){ base::mem::Free(p); }

