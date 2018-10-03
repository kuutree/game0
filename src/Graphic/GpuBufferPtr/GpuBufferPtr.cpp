//=========================================================
//include
#include "GpuBufferPtr.h"
#include "../GraphicManager.h"
#include <base/Debug/Assert.h>


namespace gr {
//=========================================================
//デストラクタ
GpuBufferPtr::~GpuBufferPtr()
{
	DB_ASSERT(!ptr.IsExist());
}


//=========================================================
//初期化
bool GpuBufferPtr::Initialize(const InitParam& init_param)
{
	//=========================================================
	//バッファ生成
	ID3D11Buffer* p_buff = nullptr;
	HRESULT		  result = GraphicManager::GetInstance().GetDevice()->CreateBuffer(
		&init_param.desc,
		&init_param.data,
		&p_buff);

	if (FAILED(result)) return false;

	ptr = p_buff;

	return true;
}


//=========================================================
//終了
void GpuBufferPtr::Finalize()
{
	ptr.Release();
}
} //namespace gr

