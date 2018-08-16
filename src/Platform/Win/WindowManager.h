///////////////////////////////////////////////////////////
///ウインドウ管理
///
///
///////////////////////////////////////////////////////////
#pragma once
//=========================================================
//include
#include "Type.h"
#include "Window.h"
#include <base/util/Singleton.h>
#include <Windows.h>
#include <list>


namespace win {
//*********************************************************
//WindowManager
//*********************************************************
class WindowManager : public base::util::Singleton<WindowManager>
{
public:
	struct EntryInfo
	{
		HINSTANCE h_instance;
		HINSTANCE h_prev_instance;
		LPSTR lp_cmd_line;
		int n_cmd_show;
		EntryInfo()
		{
			h_instance = h_prev_instance = nullptr;
			lp_cmd_line = nullptr;
			n_cmd_show = 0;
		}
	};
private:
	//=========================================================
	//val
	EntryInfo		m_entry_info;
	Window::NodePtr m_root_window_ptr;
public:
	//=========================================================
	//func
	~WindowManager();
	void Register(HINSTANCE h_instance, HINSTANCE h_prev_instance, LPSTR lp_cmd_line, int n_cmd_show);
	Window::NodePtr CreateWindowObject(const Window::CreateWindowParam& create_param);
	bool MessageProcess();

	template<class F> void FindWindowByTag(const std::wstring& tag_name, F& func);
	template<class F> void FindWindowByCategory(Category category, F& func);

	const EntryInfo& GetEntryInfo() const { return m_entry_info; }
};


//=========================================================
//検索_タグ名検索
template <typename F>
void WindowManager::FindWindowByTag(const std::wstring& tag_name, F& func)
{
	auto find_func = [&tag_name, &func](Window* p_window) -> bool
	{
		if (tag_name == p_window->GetTag())
			func(p_window);
		return true;
	};

	if (!m_root_window_ptr)	return;
	m_root_window_ptr->Foreach(find_func);
}


//=========================================================
//検索_カテゴリ検索
template <typename F>
void WindowManager::FindWindowByCategory(Category category, F& func)
{
	auto find_func = [&category, &func](Window* p_window) -> bool
	{
		if (category == p_window->GetProperty().category)
			func(p_window);
		return true;
	};

	if (!m_root_window_ptr)	return;
	m_root_window_ptr->Foreach(find_func);
}
} //namespace win

