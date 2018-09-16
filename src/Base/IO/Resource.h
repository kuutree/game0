///////////////////////////////////////////////////////////
//リソース
//
//
///////////////////////////////////////////////////////////
#pragma once
//=========================================================
//include
#include "HashPath.h"
#include "../Mem/Buffer.h"
#include "../Util/Singleton.h"
#include <memory>


namespace base {
namespace io {
///////////////////////////////////////////////////////////
//リソース
//
//
///////////////////////////////////////////////////////////
class Resource
{
public:
	//*********************************************************
	//State
	//*********************************************************
	enum State
	{
		STATE_NONE,
		STATE_LOAD_COMPLETE
	};
	//*********************************************************
	//InitParamBase
	//*********************************************************
	struct InitParamBase
	{
		HashPath path;
		virtual ~InitParamBase() { /*何もしない*/ }
	};
private:
	//=========================================================
	//val
	State m_state;
	mem::Buffer<char> m_file_buff;
public:
	//=========================================================
	//func
	Resource();
	bool Initialize(const InitParamBase& init_param);	///< 初期化
	void Finalize();
	State GetStatus() const { return m_state; }
};
} //namespace io
} //namespace base

