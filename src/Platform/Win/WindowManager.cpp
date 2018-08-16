#include "WindowManager.h"
#include "WindowFactory.h"


namespace win {
//=========================================================
//デストラクタ
WindowManager::~WindowManager()
{
	if (m_root_window_ptr)
	{
		m_root_window_ptr->Finalize();
		m_root_window_ptr.reset();
	}
}


//=========================================================
//エントリー情報登録
void WindowManager::Register(HINSTANCE h_instance, HINSTANCE h_prev_instance, LPSTR lp_cmd_line, int n_cmd_show)
{
	m_entry_info.h_instance		 = h_instance;
	m_entry_info.h_prev_instance = h_prev_instance;
	m_entry_info.lp_cmd_line	 = lp_cmd_line;
	m_entry_info.n_cmd_show		 = n_cmd_show;
}


//=========================================================
//ウインドウ追加
Window::NodePtr WindowManager::CreateWindowObject(const Window::CreateWindowParam& create_param)
{
	Window::NodePtr ptr = WindowFactory::Create(create_param.class_id, create_param);

	if (!create_param.parent_ptr)
	{
		DB_ASSERT(!m_root_window_ptr);
		m_root_window_ptr = ptr;
	}

	return ptr;
}


//=========================================================
//メッセージ処理
bool WindowManager::MessageProcess()
{
	if (!m_root_window_ptr)	PostQuitMessage(0);

	MSG msg;
	while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
		if (msg.message == WM_QUIT) return false;
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return true;
}
} //namespace win
