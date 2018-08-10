#pragma once
//=========================================================
//include
#include "../Window.h"


namespace win {
///////////////////////////////////////////////////////////
///ラジオボタン
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
	void SetCheck(bool is_enable);					///< チェック状態を変更
	bool GetCheck() const { return m_is_check; }	///< チェック状態を取得
protected:
	virtual void OnMessage(WORD word) override;
};
} //namespace win

