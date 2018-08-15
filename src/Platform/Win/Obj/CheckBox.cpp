//=========================================================
//include
#include "CheckBox.h"
#include "../WindowFactory.h"
#include "../WindowManager.h"
#include <Base/Debug/Assert.h>


namespace win {
//=========================================================
//クラス登録
REGISTER_WINDOW_FACTORY_UNIT(CheckBox, CheckBox::GetClassId());


//=========================================================
//チェック状態をアプリケーション側から変更
void CheckBox::SetState(State state)
{
	DB_ASSERT(m_is_enable_indeterminate || state != STATE_INDETERMINATE);

	if (m_state != state)
	{
		SendMessage(GetHandle(), BM_SETCHECK, state, 0);
		m_state = state;
	}
}


//=========================================================
//初期化
void CheckBox::OnInitialize(const CreateWindowParamBase& param)
{
	Window::OnInitialize(param);
	const CreateWindowParam&		_param = param.Cast<CreateWindowParam>();
	const WindowManager::EntryInfo& entry_info = WindowManager::GetInstance().GetEntryInfo();

	DB_ASSERT(_param.parent_ptr && _param.child_type == ChildType::CHILD_CHILD);

	//=========================================================
	//パラメータ設定
	m_is_enable_indeterminate = _param.is_enable_indeterminate;

	//=========================================================
	//ウインドウ作成パラメータ設定
	CreateWindowArg arg;

	arg.class_name = L"BUTTON";
	arg.title_name = _param.title_name.c_str();

	arg.h_parent	= (_param.parent_ptr) ? _param.parent_ptr->GetHandle() : nullptr;
	arg.h_instance	= entry_info.h_instance;
	arg.h_menu		= nullptr;
	arg.p_user_data = nullptr;		//コールバックに渡す値
	arg.rect		= _param.rect;	//位置・サイズ

	//スタイル設定
	arg.ex_style = 0;
	arg.style	 = (_param.is_enable_indeterminate) ? BS_AUTO3STATE : BS_AUTOCHECKBOX;
	if (_param.is_tab_stop)	 arg.style |= WS_TABSTOP;
	arg.style |= QueryStyleSettingChild(_param.parent_ptr, _param.child_type);

	if (Create(arg))
	{
		if (_param.parent_ptr)
			_param.parent_ptr->PushChild(GetSelf());
		Show(ShowType::SHOW_SHOW);
		SetState(_param.state);
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

