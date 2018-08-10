//=========================================================
//include
#include "CheckBox.h"


namespace win {
//=========================================================
//コンストラクタ
CheckBox::CheckBox()
{
	m_state = STATE_UNCHECK;
}


//=========================================================
//チェック状態をアプリケーション側から変更
void CheckBox::SetState(State state)
{
	if (m_state != state)
	{
		SendMessage(GetHandle(), BM_SETCHECK, state, 0);
		m_state = state;
	}
}


//=========================================================
//メッセージ
void CheckBox::OnMessage(WORD word)
{
	switch (word)
	{
	case BN_CLICKED:
		{
			LRESULT result = SendMessage(GetHandle(), BM_GETCHECK, 0, 0);
			m_state = (State)result;
		}
		break;
	default:  break;	//何もしない
	}
}


} //namespace win

