///////////////////////////////////////////////////////////
///GPUバッファのポインタ
///
///
///////////////////////////////////////////////////////////
#pragma once
//=========================================================
//include
#include "../DirectXPtr.h"
#include <d3d11.h>


namespace gr {
///////////////////////////////////////////////////////////
///GPUバッファのポインタ
///
///
///////////////////////////////////////////////////////////
struct GpuBufferPtr
{
public:
	//*********************************************************
	//InitParam
	//*********************************************************
	struct InitParam
	{
		D3D11_BUFFER_DESC	   desc;
		D3D11_SUBRESOURCE_DATA data;
		InitParam()
		{
			memset(&desc, 0, sizeof(desc));			
			memset(&data, 0, sizeof(data));
		}
	};
	//=========================================================
	//val
	DirectXPtr<ID3D11Buffer> ptr;
	//=========================================================
	//func
	~GpuBufferPtr();
	bool Initialize(const InitParam& init_param);
	void Finalize();
};
} //namespace gr

