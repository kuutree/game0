//=========================================================
//include
#include "CheckBox.h"


namespace win {
//=========================================================
//�R���X�g���N�^
CheckBox::CheckBox()
{
	m_state = STATE_UNCHECK;
}


//=========================================================
//�`�F�b�N��Ԃ��A�v���P�[�V����������ύX
void CheckBox::SetState(State state)
{
	if (m_state != state)
	{
		SendMessage(GetHandle(), BM_SETCHECK, state, 0);
		m_state = state;
	}
}


//=========================================================
//���b�Z�[�W
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
	default:  break;	//�������Ȃ�
	}
}


} //namespace win

