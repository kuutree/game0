///////////////////////////////////////////////////////////
///頂点シェーダ
///
///
///////////////////////////////////////////////////////////
#pragma once
//=========================================================
//include
#include "../GraphicObject.h"
#include "../../DirectXPtr.h"
#include <Base/IO/ResourceManager.h>
#include <d3d11.h>
#include <memory>


namespace gr {
namespace shader {
///////////////////////////////////////////////////////////
///頂点シェーダ
///
///
///////////////////////////////////////////////////////////
class VertexShader : public GraphicObject
{
public:
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
		DirectXPtr<ID3D11VertexShader> m_vs_ptr;
	public:
		//=========================================================
		//func
		DirectXPtr<ID3D11VertexShader>GetResource() { return m_vs_ptr; }
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
		DirectXPtr<ID3D11VertexShader> m_vs_ptr;
	public:
		//=========================================================
		//func
		Command(DirectXPtr<ID3D11VertexShader> ptr) { m_vs_ptr = ptr; }
	protected:
		virtual bool OnApply(ID3D11DeviceContext* pContext) override;
		//デバッグ
#ifdef _DEBUG
		virtual std::wstring OnGetDebugName() override { return L"VertexShaderCommand"; }
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
	Resource::ResourcePtr		   m_resource_ptr;
	DirectXPtr<ID3D11VertexShader> m_vs_ptr;
public:
	//=========================================================
	//func
protected:
	virtual bool	   OnInitialize(const InitParamBase& init_param)  override;
	virtual void	   OnFinalize() override;
	virtual CommandPTr OnCreateCommand() override;
};
} //namespace shader
} //namespace gr

