//=========================================================
//include
#include "RadioButton.h"
#include "../WindowFactory.h"
#include "../WindowManager.h"
#include <Base/Debug/Assert.h>


namespace win {
//=========================================================
//�N���X�o�^
REGISTER_WINDOW_FACTORY_UNIT(RadioButton, RadioButton::GetClassId());


//=========================================================
//�`�F�b�N��Ԃ�ύX
void RadioButton::SetCheck(bool is_enable)
{
	if (is_enable)	SendMessage(GetHandle(), BM_SETCHECK, BST_CHECKED, 0);
	else			SendMessage(GetHandle(), BM_SETCHECK, BST_UNCHECKED, 0);
}


//=========================================================
//�`�F�b�N��Ԃ��擾
bool RadioButton::GetCheck() const
{
	LRESULT result = SendMessage(GetHandle(), BM_GETCHECK, 0, 0);
	return (result == BST_CHECKED);
}


//=========================================================
//������
void RadioButton::OnInitialize(const CreateWindowParamBase& param)
{
	Window::OnInitialize(param);

	const CreateWindowParam&		_param	   = param.Cast<CreateWindowParam>();
	const WindowManager::EntryInfo& entry_info = WindowManager::GetInstance().GetEntryInfo();

	DB_ASSERT(_param.parent_ptr && _param.child_type == ChildType::CHILD_CHILD);

	SetCategory(CATEGORY_RADIO_BUTTON);

	//=========================================================
	//�E�C���h�E�쐬�p�����[�^�ݒ�
	CreateWindowArg arg;

	arg.class_name = L"BUTTON";
	arg.title_name = _param.title_name.c_str();

	arg.h_parent    = (_param.parent_ptr) ? _param.parent_ptr->GetHandle() : nullptr;
	arg.h_instance  = entry_info.h_instance;
	arg.h_menu	    = nullptr;
	arg.p_user_data = nullptr;		//�R�[���o�b�N�ɓn���l
	arg.rect		= _param.rect;	//�ʒu�E�T�C�Y

	//�X�^�C���ݒ�
	arg.ex_style = 0;
	arg.style = BS_AUTORADIOBUTTON;
	if (_param.is_tab_stop)	 arg.style |= WS_TABSTOP;
	arg.style |= QueryStyleSettingChild(_param.parent_ptr, _param.child_type);

	if (Create(arg))
	{
		if (_param.parent_ptr)
			_param.parent_ptr->PushChild(GetSelf());
		Show(ShowType::SHOW_SHOW);
	}
}


//=========================================================
//���b�Z�[�W
void RadioButton::OnMessage(WORD word)
{
	switch (word)
	{
	case BN_CLICKED:
		{
			ControllerPtr ptr = GetControllerPtr();
			if (ptr)	GetControllerPtr()->OnClick(this);
		}
		break;
	default:  break;	//�������Ȃ�
	}
}
} //namespace win

