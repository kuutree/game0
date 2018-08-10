#pragma once
//=========================================================
//include
#include "../Window.h"


namespace win {
///////////////////////////////////////////////////////////
///チェックボックス
///
///
///////////////////////////////////////////////////////////
class CheckBox : public Window
{
public:
	//////////////////////////////////////////////////////////
	///状態
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
	void SetState(State state);						///< チェック状態をアプリケーション側から変更
	State GetState() const { return m_state;  }		///< チェック状態を取得
protected:
	virtual void OnMessage(WORD word) override;
};
} //namespace win

