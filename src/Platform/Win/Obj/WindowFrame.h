///////////////////////////////////////////////////////////
///フレーム型ウインドウ
///
///
///////////////////////////////////////////////////////////
#pragma once
//=========================================================
//include
#include "../Window.h"
#include <string>


namespace win {
//*********************************************************
//WindowFrame
//*********************************************************
class WindowFrame : public Window
{
public:
	struct CreateWindowParam : public CreateWindowParamBase
	{
		std::wstring class_name;
		std::wstring title_name;
		bool is_caption;
		bool is_frame;
		bool is_close;
		bool is_adjust;

		CreateWindowParam()
		{
			is_caption  = true;
			is_frame    = true;
			is_close    = true;
			is_adjust   = true;
			class_id	= WindowFrame::GetClassId();
		}
	};
private:
	//=========================================================
	//val
	std::wstring m_class_name;
	std::wstring m_title_name;
	HINSTANCE	 m_hinstance;
public:
	//=========================================================
	//func
	WindowFrame();
	static size_t GetClassId() { return WINDOW_FRAME_ID; }
protected:
	virtual void OnInitialize(const CreateWindowParamBase& param) override;
	virtual void OnFinalize() override;
private:
	static LRESULT CALLBACK _WndProc(HWND h_wnd, UINT message, WPARAM w_param, LPARAM l_param);	///< ウインドウメッセージ処理
};
} //namespace win

