///////////////////////////////////////////////////////////
//リソースマネージャー
//
//
///////////////////////////////////////////////////////////
#pragma once
//=========================================================
//include
#include "Resource.h"
#include "../Util/Singleton.h"
#include <memory>
#include <map>


namespace base {
namespace io {
///////////////////////////////////////////////////////////
//リソースマネージャー
//
//
///////////////////////////////////////////////////////////
class ResourceManager : public util::Singleton<ResourceManager>
{
public:
	//=========================================================
	//using
	using PtrMap = std::map<HashPath, std::shared_ptr<Resource>>;
private:
	//=========================================================
	//val
	PtrMap m_resource_map;
public:
	//=========================================================
	//func
	std::shared_ptr<Resource> CreateOrCacheResource(const Resource::InitParamBase& init_param);
	bool IsLoadComplete() const;
};
} //namespace io
} //namespace base

