#pragma once
//=========================================================
//include
#include "../Window.h"


namespace win {
///////////////////////////////////////////////////////////
///�v�b�V���{�^��
///
///
///////////////////////////////////////////////////////////
class Button : public Window
{
private:
	//========================================================
	//val
	bool m_is_clicked;
public:
	//========================================================
	//func
	Button() { m_is_clicked = false; }

	void ClearClick();			///< �N���b�N��ԃN���A
	//========================================================
	//accessor
	bool IsClick() const	{ return m_is_clicked; }
protected:
	virtual void OnMessage(WORD word) override;
};
} //namespace win

