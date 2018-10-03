//=========================================================
//include
#include "VertexShader.h"
#include "../../GraphicManager.h"


namespace gr {
namespace shader {
//*********************************************************
//VertexShader
//*********************************************************
//=========================================================
//初期化
bool VertexShader::OnInitialize(const InitParamBase& init_param)
{
	if (!GraphicObject::OnInitialize(init_param))	return false;

	const VertexShader::InitParam& _init_param = init_param.Cast<VertexShader>();

	m_resource_ptr = base::io::ResourceManager::GetInstance().CreateOrCacheResource(_init_param.resource_param);
	if (!m_resource_ptr)	return false;

	VertexShader::Resource* pResource = static_cast<VertexShader::Resource*>(m_resource_ptr.get());
	m_vs_ptr = pResource->GetResource();
	
	return true;
}


//=========================================================
//終了
void VertexShader::OnFinalize()
{
	GraphicObject::OnFinalize();

	m_vs_ptr.Release();
	m_resource_ptr.reset();
}


//=========================================================
//コマンド生成
VertexShader::CommandPTr VertexShader::OnCreateCommand()
{
	CommandPTr ptr = CommandPTr(new Command(m_vs_ptr));

	return ptr;
}


//*********************************************************
//Resource
//*********************************************************
//=========================================================
//初期化
bool VertexShader::Resource::OnInitialize(const InitParamBase& init_param)
{
	if (!base::io::Resource::OnInitialize(init_param))	return false;

	return true;
}


//=========================================================
//読み込みが完了した
bool VertexShader::Resource::OnLoadComplete()
{
	if (!base::io::Resource::OnLoadComplete())	return false;

	//=========================================================
	//頂点シェーダー生成
	HRESULT	result;
	ID3D11VertexShader* p_ps;
	result = GraphicManager::GetInstance().GetDevice()->CreateVertexShader(
		GetBuff(),
		GetBuffSize(),
		nullptr,
		&p_ps);

	if (FAILED(result)) return false;

	m_vs_ptr = p_ps;

	return true;
}


//=========================================================
//終了
void VertexShader::Resource::OnFinalize()
{
	m_vs_ptr.Release();

	base::io::Resource::OnFinalize();
}


//*********************************************************
//Command
//*********************************************************
//=========================================================
//コマンド実行
bool VertexShader::Command::OnApply(ID3D11DeviceContext* pContext)
{
	if (!GraphicObject::Command::OnApply(pContext))	return false;

	pContext->VSSetShader(m_vs_ptr.Get(), nullptr, 0);

	return true;
}
} //namespace shader
} //namespace gr

