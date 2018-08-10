//=========================================================
//include
#include "RadioButton.h"


namespace win {
//=========================================================
//コンストラクタ
RadioButton::RadioButton()
{
	m_is_check = false;
}


//=========================================================
//チェック状態を変更
void RadioButton::SetCheck(bool is_enable)
{
	if (m_is_check != is_enable)
	{
		if (is_enable)	SendMessage(GetHandle(), BM_SETCHECK, BST_CHECKED, 0);
		else			SendMessage(GetHandle(), BM_SETCHECK, BST_UNCHECKED, 0);

		m_is_check = is_enable;
	}
}


//=========================================================
//メッセージ
void RadioButton::OnMessage(WORD word)
{
	switch (word)
	{
	case BN_CLICKED:
		{
			LRESULT result = SendMessage(GetHandle(), BM_GETCHECK, 0, 0);
			m_is_check = (result == BST_CHECKED);
		}
		break;
	default:  break;	//何もしない
	}
}
} //namespace win


