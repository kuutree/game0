//=========================================================
//include
#include "Button.h"


namespace win {
//=========================================================
//�N���b�N��ԃN���A
void Button::ClearClick()
{
	m_is_clicked = false;
}


//=========================================================
//���b�Z�[�W
void Button::OnMessage(WORD word)
{
	switch (word)
	{
	case BN_CLICKED:
		m_is_clicked = true;
		break;
	default:  break;	//�������Ȃ�
	}
}
} //namespace win


