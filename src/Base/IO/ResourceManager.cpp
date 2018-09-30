//=========================================================
//include
#include "ResourceManager.h"
#include "../Debug/Assert.h"


namespace base {
namespace io {
//=========================================================
//デストラクタ
ResourceManager::~ResourceManager()
{
	Reflesh();
	DB_ASSERT(m_resource_map.size() == 0);
}


//=========================================================
//リソース作成もしくはキャッシュ取得
Resource::ResourcePtr ResourceManager::CreateOrCacheResource(const Resource::InitParamBase& init_param)
{
	//=========================================================
	//重複チェック
	auto ite = m_resource_map.find(init_param.path);
	if (ite != m_resource_map.end())	return ite->second;
	
	//=========================================================
	//新規作成
	Resource::ResourcePtr ptr = init_param.create_func(init_param);
	if (!ptr)  return Resource::ResourcePtr();

	m_resource_map[init_param.path] = ptr;

	return ptr;
}


//=========================================================
//リソースリフレッシュ
void ResourceManager::Reflesh()
{
	PtrMap::iterator ite = m_resource_map.begin();

	while(ite != m_resource_map.end())
	{
		if (ite->second.use_count() == 1)
		{
			ite->second->Finalize();
			ite = m_resource_map.erase(ite);
		}
		else  ++ite;
	}
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

