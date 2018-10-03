///////////////////////////////////////////////////////////
///頂点バッファ
///
///
///////////////////////////////////////////////////////////
#pragma once
//=========================================================
//include
#include "../GraphicObject.h"
#include "../../GpuBufferPtr/GpuBufferPtr.h"
#include <Base/IO/ResourceManager.h>


namespace gr {
namespace vertex {
///////////////////////////////////////////////////////////
///頂点バッファ
///
///
///////////////////////////////////////////////////////////
class VertexBuffer : public GraphicObject
{
public:
	//*********************************************************
	//VertexFormat
	//*********************************************************
	struct VertexFormat
	{
		size_t					 vertex_size	= sizeof(float) * 4;		///< 1頂点サイズ
		D3D11_PRIMITIVE_TOPOLOGY primitive_type = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
	};
	//*********************************************************
	//Resource
	//*********************************************************
	class Resource : public base::io::Resource
	{
	public:
		struct InitParam : base::io::Resource::InitParam
		{
			InitParam()
			{
				create_func = &base::io::Resource::InitParam::Create<Resource>;
			}
		};
	private:
		//=========================================================
		//val
		GpuBufferPtr m_gpu_buffer_ptr;
	public:
		//=========================================================
		//func
		GpuBufferPtr GetResource() { return m_gpu_buffer_ptr; }
	protected:
		virtual bool OnInitialize(const InitParamBase& init_param) override;
		virtual bool OnLoadComplete() override;
		virtual void OnFinalize() override;
	};
	//*********************************************************
	//Command
	//*********************************************************
	class Command : public GraphicObject::Command
	{
		//=========================================================
		//val
		GpuBufferPtr m_gpu_buffer_ptr;
		VertexFormat m_format;
	public:
		//=========================================================
		//func
		Command(GpuBufferPtr ptr, const VertexFormat format) { m_gpu_buffer_ptr = ptr, m_format = format; }
	protected:
		virtual bool OnApply(ID3D11DeviceContext* pContext) override;
		//デバッグ
#ifdef _DEBUG
		virtual std::wstring OnGetDebugName() override { return L"VertexBuffer"; }
#endif // _DEBUG
	};
	//*********************************************************
	//InitParam
	//*********************************************************
	struct InitParam : GraphicObject::InitParam
	{
		Resource::InitParam resource_param;
		virtual ~InitParam() { /*何もしない*/ }
	};
private:
	//=========================================================
	//val
	Resource::ResourcePtr m_resource_ptr;
	VertexFormat		  m_format;
	GpuBufferPtr		  m_gpu_buffer_ptr;
public:
	//=========================================================
	//func
	virtual bool	   OnInitialize(const InitParamBase& init_param)  override;
	virtual void	   OnFinalize() override;
	virtual CommandPTr OnCreateCommand() override;
};
} //namespace vertex
} //namespace gr

