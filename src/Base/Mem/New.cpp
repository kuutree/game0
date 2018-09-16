//=========================================================
//include
#include "New.h"
#include <stdlib.h>
#include "../thread/CriticalSection.h"
#include "../debug/Assert.h"


///////////////////////////////////////////////////////////
///�A���P�[�^
///
///�B�����邽�߂�cpp�ɋL�q
///////////////////////////////////////////////////////////
class Allocator
{
	//////////////////////////////////////////////////////////
	///�S�̂̃A���P�[�g���
	///
	//////////////////////////////////////////////////////////
	struct AllocInfo
	{
		int cnt;	///< �A���P�[�g�J�E���g
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
	///�R���X�g���N�^
	Allocator() {}
	///-------------------------------------------------------
	///�f�X�g���N�^
	~Allocator()
	{
		m_critical_section.Lock();
		DB_ASSERT(m_alloc_info.cnt == 0);
		m_critical_section.Unlock();
	}
	///-------------------------------------------------------
	///�m��
	void* Malloc(size_t size, size_t alignment)
	{
		m_critical_section.Lock();

		//�m��
		void* p = _aligned_malloc(size, alignment);
		DB_ASSERT(p != NULL);

		//�A���P�[�g���X�V
		++m_alloc_info.cnt;

		m_critical_section.Unlock();

		return p;
	}
	///-------------------------------------------------------
	///���
	void Free(void* p)
	{
		m_critical_section.Lock();

		//���
		_aligned_free(p);

		//�A���P�[�g���X�V
		--m_alloc_info.cnt;

		m_critical_section.Unlock();
	}
	///-------------------------------------------------------
	///���݂̃������m�ے��̐����擾
	int GetAllocCnt()
	{
		m_critical_section.Lock();
		int cnt = m_alloc_info.cnt;
		m_critical_section.Unlock();

		return cnt;
	}
};


//=========================================================
//�O���[�o���ϐ�
Allocator g_allocator;


namespace base{
namespace mem{
//=========================================================
//�m��
void* Malloc(size_t size, size_t alignment) { return g_allocator.Malloc(size, alignment); }


//=========================================================
//���
void Free(void* p) { g_allocator.Free(p); }


//=========================================================
//���݂̃������m�ے��̐����擾
int GetAllocCnt() { return g_allocator.GetAllocCnt(); }
}//namespace mem
}//namespace base
