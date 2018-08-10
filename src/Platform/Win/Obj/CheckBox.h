#pragma once
//=========================================================
//include
#include "../Window.h"


namespace win {
///////////////////////////////////////////////////////////
///�`�F�b�N�{�b�N�X
///
///
///////////////////////////////////////////////////////////
class CheckBox : public Window
{
public:
	//////////////////////////////////////////////////////////
	///���
	//////////////////////////////////////////////////////////
	enum State
	{
		STATE_UNCHECK		= BST_UNCHECKED,
		STATE_INDETERMINATE = BST_INDETERMINATE,
		STATE_CHECK			= BST_CHECKED,
	};
private:
	//========================================================
	//val
	State m_state;
public:
	//========================================================
	//func
	CheckBox();
	void SetState(State state);						///< �`�F�b�N��Ԃ��A�v���P�[�V����������ύX
	State GetState() const { return m_state;  }		///< �`�F�b�N��Ԃ��擾
protected:
	virtual void OnMessage(WORD word) override;
};
} //namespace win

