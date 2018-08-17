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
	//////////////////////////////////////////////////////////
	///ウインドウ作成パラメータ
	//////////////////////////////////////////////////////////
	struct CreateWindowParam : public CreateWindowParamBase
	{
		std::wstring title_name;
		bool		 is_enable_indeterminate;
		bool		 is_tab_stop;
		State		 state;

		CreateWindowParam()
		{
			is_enable_indeterminate = false;
			is_tab_stop = true;
			class_id = GetClassId();
			state = STATE_UNCHECK;
		}
	};
private:
	//========================================================
	//val
	bool m_is_enable_indeterminate = false;
public:
	//========================================================
	//func
	void SetState(State state);		///< チェック状態をアプリケーション側から変更
	State GetState() const;			///< チェック状態を取得
	static size_t GetClassId() { return WINDOW_CHECK_BOX_ID; }
protected:
	virtual void OnInitialize(const CreateWindowParamBase& param) override;
	virtual void OnMessage(WORD word) override;
};
} //namespace win

