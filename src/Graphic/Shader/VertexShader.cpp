//=========================================================
//include
#include "VertexShader.h"
#include "../GraphicManager.h"
#include <Base/IO/ResourceManager.h>


namespace gr {
namespace shader {
//=========================================================
//初期化
bool VertexShader::OnInitialize(const InitParamBase& init_param)
{
	if (!base::io::Resource::OnInitialize(init_param))	return false;

	return true;
}


//=========================================================
//読み込みが完了した
bool VertexShader::OnLoadComplete()
{
	if (!base::io::Resource::OnLoadComplete())	return false;

	//=========================================================
	//頂点シェーダー生成
	HRESULT	result;
	ID3D11VertexShader* p_vs;
	result = GraphicManager::GetInstance().GetDevice()->CreateVertexShader(
		GetBuff(),
		GetBuffSize(),
		nullptr,
		&p_vs);

	if (FAILED(result)) return false;

	m_vs_ptr = p_vs;

	return true;
}


//=========================================================
//終了
void VertexShader::OnFinalize()
{
	m_vs_ptr.Release();

	base::io::Resource::OnFinalize();
}
} //namespace shader
} //namespace gr

