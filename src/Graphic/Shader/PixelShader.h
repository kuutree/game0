///////////////////////////////////////////////////////////
///ピクセルシェーダ
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
///ピクセルシェーダ
///
///
///////////////////////////////////////////////////////////
class PixelShader : public base::io::Resource
{
private:
	//=========================================================
	//val
	DirectXPtr<ID3D11PixelShader> m_ps_ptr;
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
