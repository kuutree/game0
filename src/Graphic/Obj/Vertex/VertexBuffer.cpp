//=========================================================
//include
#include "VertexBuffer.h"


namespace gr {
namespace vertex {
//*********************************************************
//VertexBuffer
//*********************************************************
//=========================================================
//初期化
bool VertexBuffer::OnInitialize(const InitParamBase& init_param)
{
	if (!GraphicObject::OnInitialize(init_param))	return false;

	const VertexBuffer::InitParam& _init_param = init_param.Cast<VertexBuffer>();

	m_resource_ptr = base::io::ResourceManager::GetInstance().CreateOrCacheResource(_init_param.resource_param);
	if (!m_resource_ptr)	return false;

	VertexBuffer::Resource* pResource = static_cast<VertexBuffer::Resource*>(m_resource_ptr.get());
	m_gpu_buffer_ptr = pResource->GetResource();

	return true;
}


//=========================================================
//終了
void VertexBuffer::OnFinalize()
{
	GraphicObject::OnFinalize();

	m_gpu_buffer_ptr.Finalize();
	m_resource_ptr.reset();
}


//=========================================================
//コマンド生成
VertexBuffer::CommandPTr VertexBuffer::OnCreateCommand()
{
	CommandPTr ptr = CommandPTr(new Command(m_gpu_buffer_ptr, m_format));

	return ptr;
}


//*********************************************************
//Resource
//*********************************************************
//=========================================================
//セッティング
bool VertexBuffer::Resource::OnInitialize(const InitParamBase& init_param)
{
	if (!base::io::Resource::OnInitialize(init_param))	return false;

	return true;

}


//=========================================================
//セッティング
bool VertexBuffer::Resource::OnLoadComplete()
{
	if (!base::io::Resource::OnLoadComplete())	return false;

	GpuBufferPtr::InitParam init_param;
	init_param.data.pSysMem	  = GetBuff();
	init_param.desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	init_param.desc.ByteWidth = (UINT)GetBuffSize();

	bool result = m_gpu_buffer_ptr.Initialize(init_param);

	return result;
}


//=========================================================
//セッティング
void VertexBuffer::Resource::OnFinalize()
{
	m_gpu_buffer_ptr.Finalize();

	base::io::Resource::OnFinalize();
}


//*********************************************************
//Command
//*********************************************************
//=========================================================
//コマンド実行
bool VertexBuffer::Command::OnApply(ID3D11DeviceContext* pContext)
{
	if (!GraphicObject::Command::OnApply(pContext))	return false;

	ID3D11Buffer* p_buff_container[] = { m_gpu_buffer_ptr.ptr.Get() };
	UINT stride_buff[] = { (UINT)m_format.vertex_size };
	UINT offset_buff[] = { 0 };

	pContext->IASetVertexBuffers(0, 1, p_buff_container, stride_buff, offset_buff);
	pContext->IASetPrimitiveTopology(m_format.primitive_type);

	return true;
}


} //namespace vertex
} //namespace gr

