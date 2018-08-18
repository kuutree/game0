#pragma once
//=========================================================
//include
#include "DirectXPtr.h"
#include <base/util/Singleton.h>
#include <Platform/Win/Window.h>
#include <d3d11.h>
//=========================================================
//lib
#pragma comment(lib, "d3d11.lib")


namespace gr {
//*********************************************************
//GraphicManager
//*********************************************************
class GraphicManager : public base::util::Singleton<GraphicManager>
{
public:
	struct CreateDeviceParam
	{
		win::Window::NodePtr window_ptr;
	};
private:
	//=========================================================
	//val
	DirectXPtr<ID3D11Device>			m_device_ptr;
	DirectXPtr<ID3D11DeviceContext>		m_device_context_ptr;
	DirectXPtr<IDXGISwapChain>			m_swapChain_ptr;
	DirectXPtr<ID3D11RenderTargetView>	m_render_target_view_ptr;
	win::Window::NodePtr				m_window_ptr;

public:
	//=========================================================
	//func
	void CreateDevice(const CreateDeviceParam& param);
	void BeginRender();
	void EndRender();
	DirectXPtr<ID3D11Device>&		 GetDevice() { return m_device_ptr; }
	DirectXPtr<ID3D11DeviceContext>& GetContext() { return m_device_context_ptr; }
};
} //namespace gr

