//=========================================================
//include
#include "ResourceManager.h"
#include "ResourceFactory.h"


namespace base {
namespace io {
//=========================================================
//リソース作成もしくはキャッシュ取得
Resource::ResourcePtr ResourceManager::CreateOrCacheResource(const Resource::InitParamBase& init_param)
{
	auto ite = m_resource_map.find(init_param.path);
	if (ite != m_resource_map.end())	return ite->second;
	
	Resource::ResourcePtr ptr = ResourceFactory::Create(init_param.class_id, init_param);

	if (!ptr)  return ptr;

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

