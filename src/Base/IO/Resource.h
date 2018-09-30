///////////////////////////////////////////////////////////
//リソース
//
//
///////////////////////////////////////////////////////////
#pragma once
//=========================================================
//include
#include "ResourceId.h"
#include "HashPath.h"
#include "../Mem/Buffer.h"
#include "../Util/Singleton.h"
#include "../Debug/Assert.h"
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
		size_t	 class_id = GetClassId();
		HashPath path;
		virtual ~InitParamBase() { /*何もしない*/ }
	};
	//=========================================================
	//using
	using ResourcePtr = std::shared_ptr<Resource>;
	using InitParam	  = InitParamBase;
private:
	//=========================================================
	//val
	State m_state;
	mem::Buffer<char> m_file_buff;
public:
	//=========================================================
	//func
	Resource();
	virtual ~Resource() {  }
	bool Initialize(const InitParamBase& init_param);	///< 初期化
	void Finalize();

	State		GetStatus() const	{ return m_state; }
	const char* GetBuff() const		{ return m_file_buff.GetAddr(); }
	size_t		GetBuffSize() const { return m_file_buff.GetByteSize(); }
	static size_t GetClassId()		{ return RESOURCE_ID_RESOURCE; }
protected:
	virtual bool OnInitialize(const InitParamBase& init_param) { return true;/*何もしない*/ }
	virtual bool OnLoadComplete() { return true;/*何もしない*/ }
	virtual void OnFinalize() { /*何もしない*/ }
};
} //namespace io
} //namespace base

