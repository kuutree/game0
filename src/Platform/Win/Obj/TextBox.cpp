//=========================================================
//include
#include "TextBox.h"
#include "../WindowFactory.h"
#include "../WindowManager.h"
#include <Base/Debug/Assert.h>


namespace win {
//=========================================================
//クラス登録
REGISTER_WINDOW_FACTORY_UNIT(TextBox, TextBox::GetClassId());


//=========================================================
//初期化
void TextBox::OnInitialize(const CreateWindowParamBase& param)
{
	Window::OnInitialize(param);
	const CreateWindowParam&		_param = param.Cast<CreateWindowParam>();
	const WindowManager::EntryInfo& entry_info = WindowManager::GetInstance().GetEntryInfo();

	DB_ASSERT(_param.parent_ptr && _param.child_type == ChildType::CHILD_CHILD);

	//=========================================================
	//ウインドウ作成パラメータ設定
	CreateWindowArg arg;

	arg.class_name = L"EDIT";
	arg.title_name = nullptr;

	arg.h_parent	= (_param.parent_ptr) ? _param.parent_ptr->GetHandle() : nullptr;
	arg.h_instance	= entry_info.h_instance;
	arg.h_menu		= nullptr;
	arg.p_user_data = nullptr;		//コールバックに渡す値
	arg.rect		= _param.rect;	//位置・サイズ

	//スタイル設定
	arg.ex_style = 0;
	if (_param.is_draw_edge)	arg.ex_style |= WS_EX_CLIENTEDGE;

	arg.style |= (DWORD)_param.position | ES_AUTOHSCROLL;
	if (_param.is_tab_stop)		arg.style |= WS_TABSTOP;
	if (_param.is_multi_line)	arg.style |= ES_MULTILINE | ES_AUTOVSCROLL | ES_WANTRETURN;
	if (_param.is_read_only)	arg.style |= ES_READONLY;
	if (_param.is_number_only)	arg.style |= ES_NUMBER;

	if (Create(arg))
	{
		if (_param.parent_ptr)
			_param.parent_ptr->PushChild(GetSelf());
		Show(ShowType::SHOW_SHOW);
	}
}


//=========================================================
//メッセージ
void TextBox::OnMessage(WORD word)
{
	switch (word)
	{
	case BN_CLICKED:
		{
		}
		break;
	default:  break;	//何もしない
	}
}
} //namespace win

