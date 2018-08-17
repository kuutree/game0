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
	//////////////////////////////////////////////////////////
	///�E�C���h�E�쐬�p�����[�^
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
	void SetState(State state);		///< �`�F�b�N��Ԃ��A�v���P�[�V����������ύX
	State GetState() const;			///< �`�F�b�N��Ԃ��擾
	static size_t GetClassId() { return WINDOW_CHECK_BOX_ID; }
protected:
	virtual void OnInitialize(const CreateWindowParamBase& param) override;
	virtual void OnMessage(WORD word) override;
};
} //namespace win

