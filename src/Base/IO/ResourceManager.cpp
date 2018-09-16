//=========================================================
//include
#include "ResourceManager.h"


namespace base {
namespace io {
//=========================================================
//リソース作成もしくはキャッシュ取得
std::shared_ptr<Resource> ResourceManager::CreateOrCacheResource(const Resource::InitParamBase& init_param)
{
	auto ite = m_resource_map.find(init_param.path);
	if (ite != m_resource_map.end())	return ite->second;
	
	std::shared_ptr<Resource> ptr = std::shared_ptr<Resource>(new Resource());
	ptr->Initialize(init_param);
	m_resource_map.insert(std::make_pair(init_param.path, ptr));

	return ptr;
}


//=========================================================
//ロード完了
bool ResourceManager::IsLoadComplete() const
{
	for (const auto& pair: m_resource_map)
		if (pair.second->GetStatus() != Resource::STATE_LOAD_COMPLETE)
			return false;

	return true;
}
} //namespace io
} //namespace base

