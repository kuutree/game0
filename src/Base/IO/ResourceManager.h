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
	using PtrMap = std::map<HashPath, Resource::ResourcePtr>;
private:
	//=========================================================
	//val
	PtrMap m_resource_map;
public:
	//=========================================================
	//func
	Resource::ResourcePtr CreateOrCacheResource(const Resource::InitParamBase& init_param);
	bool IsLoadComplete() const;
};
} //namespace io
} //namespace base

