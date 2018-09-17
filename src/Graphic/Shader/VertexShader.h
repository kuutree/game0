///////////////////////////////////////////////////////////
///頂点シェーダ
///
///
///////////////////////////////////////////////////////////
#pragma once
//=========================================================
//include
#include <Base/IO/Resource.h>
#include "../DirectXPtr.h"
#include <d3d11.h>
#include <memory>


namespace gr {
namespace shader {
///////////////////////////////////////////////////////////
///頂点シェーダ
///
///
///////////////////////////////////////////////////////////
class VertexShader : public base::io::Resource
{
private:
	//=========================================================
	//val
	DirectXPtr<ID3D11VertexShader> m_vs_ptr;
public:
	//=========================================================
	//func
protected:
	virtual bool OnInitialize(const InitParamBase& init_param) override;
	virtual bool OnLoadComplete() override;
	virtual void OnFinalize() override;
};
} //namespace shader
} //namespace gr

