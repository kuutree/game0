///////////////////////////////////////////////////////////
///プッシュボタン
///
///
///////////////////////////////////////////////////////////
#pragma once
//=========================================================
//include
#include "../Window.h"


namespace win {
///////////////////////////////////////////////////////////
///プッシュボタン
///
///
///////////////////////////////////////////////////////////
class Button : public Window
{
public:
	struct CreateWindowParam : public Window::CreateWindowParam
	{
		std::wstring title_name;
		bool		 is_tab_stop;

		CreateWindowParam()
		{
			is_tab_stop = true;
			class_id	= GetClassId();
		}
	};
public:
	//========================================================
	//accessor
	static size_t GetClassId() { return WINDOW_BUTTON_ID; }
protected:
	virtual void OnInitialize(const CreateWindowParamBase& param) override;
	virtual void OnMessage(WORD word) override;
};
} //namespace win

