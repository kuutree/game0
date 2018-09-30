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
	//=========================================================
	//前方宣言
	struct InitParamBase;
	//=========================================================
	//using
	using ResourcePtr = std::shared_ptr<Resource>;
	using InitParam	  = InitParamBase;
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
		//=========================================================
		//using
		using CreateFunc  = ResourcePtr(*)(const InitParamBase& param);
		//=========================================================
		//val
		CreateFunc create_func;
		HashPath   path;	
		//=========================================================
		//func
		virtual ~InitParamBase() { /*何もしない*/ }

		template<class T> typename const T::InitParam& Cast() const { return static_cast<typename const T::InitParam&>(*this); }
		template<class T> static ResourcePtr Create(const InitParamBase& param)
		{
			ResourcePtr ptr(new T);
			if (!ptr->Initialize(param))	return ResourcePtr();

			return ptr;
		}
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
	virtual ~Resource() {  }
	bool Initialize(const InitParamBase& init_param);	///< 初期化
	void Finalize();

	State		GetStatus() const	{ return m_state; }
	const char* GetBuff() const		{ return m_file_buff.GetAddr(); }
	size_t		GetBuffSize() const { return m_file_buff.GetByteSize(); }
protected:
	virtual bool OnInitialize(const InitParamBase& init_param) { return true;/*何もしない*/ }
	virtual bool OnLoadComplete() { return true;/*何もしない*/ }
	virtual void OnFinalize() { /*何もしない*/ }
};
} //namespace io
} //namespace base

