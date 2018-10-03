//=========================================================
//include
#include "PixelShader.h"
#include "../../GraphicManager.h"


namespace gr {
namespace shader {
//*********************************************************
//PixelShader
//*********************************************************
//=========================================================
//初期化
bool PixelShader::OnInitialize(const InitParamBase& init_param)
{
	if (!GraphicObject::OnInitialize(init_param))	return false;

	const PixelShader::InitParam& _init_param = init_param.Cast<PixelShader>();

	m_resource_ptr = base::io::ResourceManager::GetInstance().CreateOrCacheResource(_init_param.resource_param);
	if (!m_resource_ptr)	return false;

	PixelShader::Resource* pResource = static_cast<PixelShader::Resource*>(m_resource_ptr.get());
	m_ps_ptr = pResource->GetResource();
	
	return true;
}


//=========================================================
//終了
void PixelShader::OnFinalize()
{
	GraphicObject::OnFinalize();

	m_ps_ptr.Release();
	m_resource_ptr.reset();
}


//=========================================================
//コマンド生成
PixelShader::CommandPTr PixelShader::OnCreateCommand()
{
	CommandPTr ptr = CommandPTr(new Command(m_ps_ptr));

	return ptr;
}


//*********************************************************
//Resource
//*********************************************************
//=========================================================
//初期化
bool PixelShader::Resource::OnInitialize(const InitParamBase& init_param)
{
	if (!base::io::Resource::OnInitialize(init_param))	return false;

	return true;
}


//=========================================================
//読み込みが完了した
bool PixelShader::Resource::OnLoadComplete()
{
	if (!base::io::Resource::OnLoadComplete())	return false;

	//=========================================================
	//頂点シェーダー生成
	HRESULT	result;
	ID3D11PixelShader* p_ps;
	result = GraphicManager::GetInstance().GetDevice()->CreatePixelShader(
		GetBuff(),
		GetBuffSize(),
		nullptr,
		&p_ps);

	if (FAILED(result)) return false;

	m_ps_ptr = p_ps;

	return true;
}


//=========================================================
//終了
void PixelShader::Resource::OnFinalize()
{
	m_ps_ptr.Release();

	base::io::Resource::OnFinalize();
}


//*********************************************************
//Command
//*********************************************************
//=========================================================
//コマンド実行
bool PixelShader::Command::OnApply(ID3D11DeviceContext* pContext)
{
	if (!GraphicObject::Command::OnApply(pContext))	return false;

	pContext->PSSetShader(m_ps_ptr.Get(), nullptr, 0);

	return true;
}
} //namespace shader
} //namespace gr

