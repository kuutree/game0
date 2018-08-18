#include "GraphicManager.h"


namespace gr {
//=========================================================
//コンストラクタ
void GraphicManager::CreateDevice(const CreateDeviceParam& param)
{
	//=========================================================
	//デバイス・コンテキスト・スワップチェーンの生成
	HRESULT hr;
	DXGI_SWAP_CHAIN_DESC desc;
	memset(&desc, 0, sizeof(desc));
	desc.BufferDesc.Width = 1920;
	desc.BufferDesc.Height = 1080;
	desc.BufferDesc.RefreshRate.Numerator = 0;
	desc.BufferDesc.RefreshRate.Denominator = 1;
	desc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM_SRGB;
	desc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	desc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
	desc.SampleDesc.Count = 1;
	desc.SampleDesc.Quality = 0;
	desc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	desc.BufferCount = 1;
	desc.OutputWindow = param.window_ptr->GetHandle();
	desc.Windowed = TRUE;
	desc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
	desc.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;

	ID3D11Device*		 p_device		  = nullptr;
	ID3D11DeviceContext* p_device_context = nullptr;
	IDXGISwapChain*		 p_swapChain	  = nullptr;
	hr = D3D11CreateDeviceAndSwapChain(
		nullptr,
		D3D_DRIVER_TYPE_HARDWARE,
		nullptr,
		0,
		nullptr,
		0,
		D3D11_SDK_VERSION,
		&desc,
		&p_swapChain,
		&p_device,
		nullptr,
		&p_device_context);

	DB_ASSERT(SUCCEEDED(hr));

	m_device_ptr		 = p_device;
	m_device_context_ptr = p_device_context;
	m_swapChain_ptr		 = p_swapChain;
	m_window_ptr		 = param.window_ptr;

	//=========================================================
	//スワップチェーンからバックバッファ取得
	DirectXPtr<ID3D11Texture2D> back_buff_ptr;
	ID3D11Texture2D*			p_back_buffer = nullptr;
	hr = p_swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&p_back_buffer);
	DB_ASSERT(SUCCEEDED(hr));
	back_buff_ptr = p_back_buffer;

	//=========================================================
	//レンダリングターゲットを作成
	ID3D11RenderTargetView*	p_render_target_view = nullptr;
	hr = m_device_ptr->CreateRenderTargetView(p_back_buffer, nullptr, &p_render_target_view);
	DB_ASSERT(SUCCEEDED(hr));
	m_render_target_view_ptr = p_render_target_view;

	//=========================================================
	//作成したレンダリングターゲットを設定
	m_device_context_ptr->OMSetRenderTargets(1, &p_render_target_view, nullptr);

	//=========================================================
	//ビューポート設定
	D3D11_VIEWPORT vp;
	vp.TopLeftX = 0;
	vp.TopLeftY = 0;
	vp.Width = 1920;
	vp.Height = 1080;
	vp.MinDepth = 0.0f;
	vp.MaxDepth = 1.0f;
	m_device_context_ptr->RSSetViewports(1, &vp);
}


//=========================================================
//描画開始
void GraphicManager::BeginRender()
{
	float ClearColor[] = { 0.0f, 0.0f, 1.0f, 1.0f };
	m_device_context_ptr->ClearRenderTargetView(m_render_target_view_ptr.Get(), ClearColor);
}


//=========================================================
//描画終了
void GraphicManager::EndRender()
{
	m_swapChain_ptr->Present(0, 0);
}

} //namespace gr

