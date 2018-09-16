#pragma once
//=========================================================
//include
#include <Windows.h>


namespace base {
namespace thread {
///////////////////////////////////////////////////////////
///”r‘¼
///
///
///////////////////////////////////////////////////////////
class CriticalSection
{
	CRITICAL_SECTION m_object;
public:
	CriticalSection()	{ InitializeCriticalSection(&m_object); }
	~CriticalSection()	{ DeleteCriticalSection(&m_object); }
	void Lock()			{ EnterCriticalSection(&m_object); }
	void Unlock()		{ LeaveCriticalSection(&m_object); }
};
} //namespace thread
} //namespace base