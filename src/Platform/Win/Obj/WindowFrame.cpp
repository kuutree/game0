#include "WindowFrame.h"
#include "../WindowFactory.h"
#include "../WindowManager.h"


namespace win {
//=========================================================
//クラス登録
REGISTER_WINDOW_FACTORY_UNIT(WindowFrame, WindowFrame::GetClassId());


//=========================================================
//コンストラクタ
WindowFrame::WindowFrame()
{
	m_hinstance = nullptr;
}


//=========================================================
//初期化
void WindowFrame::OnInitialize(const win::CreateWindowParam& param)
{
	Window::OnInitialize(param);

	const CreateWindowParam&		_param	   = param.Cast<CreateWindowParam>();
	const WindowManager::EntryInfo& entry_info = WindowManager::GetInstance().GetEntryInfo();

	//=========================================================
	//メンバー反映
	m_class_name = _param.class_name;
	m_title_name = _param.title_name;
	m_hinstance  = entry_info.h_instance;

	//=========================================================
	//ウインドウ作成パラメータ設定
	CreateWindowArg arg;

	arg.class_name = m_class_name.c_str();
	arg.title_name = m_title_name.c_str();

	arg.h_parent	 = (_param.parent_ptr) ? _param.parent_ptr->GetHandle() : nullptr;
	arg.h_instance	 = m_hinstance;
	arg.h_menu	     = nullptr;
	arg.p_user_data  = this;	//コールバックに渡す値

	//スタイル設定
	arg.ex_style = 0;
	arg.style	 = WS_OVERLAPPED;
	if (_param.is_frame)	arg.style |= WS_DLGFRAME;
	if (_param.is_caption)	arg.style |= WS_CAPTION;
	if (_param.is_close)
	{
		DB_ASSERT(_param.is_caption);	//タイトルバーがないとだめなので
		arg.style |= WS_SYSMENU;
	}
	arg.style |= QueryStyleSettingChild(_param.parent_ptr, _param.child_type);

	//位置・サイズ
	RECT rect;
	_param.rect.RectToRECT(&rect);
	AdjustWindowRect(&rect, arg.style, arg.h_menu != nullptr);
	arg.rect.RECTToRect(rect);

	//=========================================================
	//ウィンドウクラスを登録
	WNDCLASSEX wcex;
	memset(&wcex, 0, sizeof(wcex));

	wcex.cbSize		   = sizeof(wcex);
	wcex.style		   = CS_HREDRAW | CS_VREDRAW;	//縦横にウインドウサイズが変更されたら再描画
	wcex.lpfnWndProc   = _WndProc;
	wcex.cbClsExtra	   = 0;
	wcex.cbWndExtra	   = 0;
	wcex.hInstance	   = arg.h_instance;
	wcex.hIcon		   = nullptr;
	wcex.hCursor	   = nullptr;
	wcex.lpszMenuName  = nullptr;
	wcex.lpszClassName = arg.class_name;
	
	RegisterClassEx(&wcex);

	if (Create(arg))
	{
		if (_param.parent_ptr)
			_param.parent_ptr->PushChild(GetSelf());
		Show(entry_info.n_cmd_show);
	}
}


//=========================================================
//終了
void WindowFrame::OnFinalize()
{
	Window::OnFinalize();

	//ウィンドウクラスを登録解除
	if (m_hinstance != nullptr)
	{
		BOOL result = UnregisterClass(m_class_name.c_str(), m_hinstance);
		DB_ASSERT(result != 0);

		m_class_name.clear();
		m_title_name.clear();
		m_hinstance = nullptr;
	}
}


//=========================================================
//ウインドウメッセージ処理
LRESULT CALLBACK WindowFrame::_WndProc(HWND h_wnd, UINT message, WPARAM w_param, LPARAM l_param)
{
	switch (message) {
	//=========================================================
	case WM_CREATE:
		SetWindowLongPtr(h_wnd, GWLP_USERDATA, (LONG_PTR)(((CREATESTRUCT*)l_param)->lpCreateParams));
		break;
	//=========================================================
	//WM_COMMAND
	case WM_COMMAND:
		{
			HWND h_command_wnd = (HWND)l_param;	// lParamはウインドウハンドル
			WORD ctrl_command  = HIWORD(w_param);
			//=========================================================
			//ラムダ式	検索用
			auto func = [h_command_wnd](const NodeType* p_node) -> bool
			{
				return h_command_wnd == p_node->GetHandle();
			};

			WindowFrame* wnd_frame  = (WindowFrame*)GetWindowLongPtr(h_wnd, GWLP_USERDATA);
			//=========================================================
			//子ウインドウに通知
			NodePtr ptr = wnd_frame->FindNode(func);
			if (ptr)  ptr->Message(ctrl_command);
		}
		break;
	//=========================================================
	//WM_CLOSE
	case WM_CLOSE:
		PostMessage(h_wnd, WM_DESTROY, 0, 0);
		break;
	//=========================================================
	//WM_DESTROY
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}

	return(DefWindowProc(h_wnd, message, w_param, l_param));
}
} //namespace win
