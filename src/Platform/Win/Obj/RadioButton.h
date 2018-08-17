#pragma once
//=========================================================
//include
#include "../Window.h"


namespace win {
///////////////////////////////////////////////////////////
///���W�I�{�^��
///
///
///////////////////////////////////////////////////////////
class RadioButton : public Window
{
public:
	struct CreateWindowParam : public CreateWindowParamBase
	{
		std::wstring title_name;
		bool		 is_tab_stop;

		CreateWindowParam()
		{
			is_tab_stop = true;
			class_id = GetClassId();
		}
	};
public:
	//========================================================
	//func
	void SetCheck(bool is_enable);					///< �`�F�b�N��Ԃ�ύX
	bool GetCheck() const;							///< �`�F�b�N��Ԃ��擾
	static size_t GetClassId() { return WINDOW_RADIO_BUTTON_ID; }
protected:
	virtual void OnInitialize(const CreateWindowParamBase& param) override;
	virtual void OnMessage(WORD word) override;
};
} //namespace win

