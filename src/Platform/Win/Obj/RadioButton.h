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
	//========================================================
	//val
	bool m_is_check;
public:
	//========================================================
	//func
	RadioButton();
	void SetCheck(bool is_enable);					///< �`�F�b�N��Ԃ�ύX
	bool GetCheck() const { return m_is_check; }	///< �`�F�b�N��Ԃ��擾
protected:
	virtual void OnMessage(WORD word) override;
};
} //namespace win

