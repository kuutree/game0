//=========================================================
//include
#include "Button.h"


namespace win {
//=========================================================
//クリック状態クリア
void Button::ClearClick()
{
	m_is_clicked = false;
}


//=========================================================
//メッセージ
void Button::OnMessage(WORD word)
{
	switch (word)
	{
	case BN_CLICKED:
		m_is_clicked = true;
		break;
	default:  break;	//何もしない
	}
}
} //namespace win


