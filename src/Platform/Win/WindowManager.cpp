#include "WindowManager.h"
#include "WindowFactory.h"


namespace win {
//=========================================================
//コンストラクタ
WindowManager::WindowManager()
{
}


//=========================================================
//デストラクタ
WindowManager::~WindowManager()
{
	WindowPtrList::iterator ite = m_window_ptr_list.begin();

	while (ite != m_window_ptr_list.end())
	{
		(*ite)->Finalize();
		ite = m_window_ptr_list.erase(ite);
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
WindowManager::WindowPtr WindowManager::CreateWindowObject(const Window::CreateWindowParam& create_param)
{
	WindowPtr ptr = WindowFactory::Create(create_param.class_id, create_param);
	m_window_ptr_list.push_back(ptr);

	return ptr;
}


//=========================================================
//メッセージ処理
bool WindowManager::MessageProcess()
{
	if (m_window_ptr_list.size() == 0)	PostQuitMessage(0);

	MSG msg;
	while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
		if (msg.message == WM_QUIT) return false;
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return true;
}
} //namespace win
