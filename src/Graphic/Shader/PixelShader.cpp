//=========================================================
//include
#include "PixelShader.h"
#include "../GraphicManager.h"
#include <Base/IO/ResourceManager.h>


namespace gr {
namespace shader {
//=========================================================
//初期化
bool PixelShader::OnInitialize(const InitParamBase& init_param)
{
	if (!base::io::Resource::OnInitialize(init_param))	return false;

	return true;
}


//=========================================================
//読み込みが完了した
bool PixelShader::OnLoadComplete()
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
void PixelShader::OnFinalize()
{
	m_ps_ptr.Release();

	base::io::Resource::OnFinalize();
}
} //namespace shader
} //namespace gr

