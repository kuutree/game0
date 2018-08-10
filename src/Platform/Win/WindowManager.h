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
	//=========================================================
	//using
	using WindowPtr = std::shared_ptr<Window>;
	using WindowPtrList = std::list<WindowPtr>;
private:
	//=========================================================
	//val
	EntryInfo	  m_entry_info;
	WindowPtrList m_window_ptr_list;
public:
	//=========================================================
	//func
	WindowManager();
	~WindowManager();
	void Register(HINSTANCE h_instance, HINSTANCE h_prev_instance, LPSTR lp_cmd_line, int n_cmd_show);
	WindowPtr CreateWindowObject(const CreateWindowParam& create_param);
	bool MessageProcess();

	const EntryInfo& GetEntryInfo() const { return m_entry_info; }
};
} //namespace win
