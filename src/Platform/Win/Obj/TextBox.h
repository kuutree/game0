#pragma once
//=========================================================
//include
#include "../Window.h"


namespace win {
//*********************************************************
//�e�L�X�g�{�b�N�X
//*********************************************************
class TextBox : public Window
{
public:
	//*********************************************************
	//�E�C���h�E�쐬�p�����[�^
	//*********************************************************
	struct CreateWindowParam : public CreateWindowParamBase
	{
		bool is_tab_stop;	///< �^�u���͂Ńt�H�[�J�X������
		bool is_draw_edge;	///< ���E���`��
		bool is_multi_line;	///< �����s�\��	+ �c�X�N���[��
		bool is_read_only;	///< �ǂݍ��݂̂�
		bool is_number_only;///< �������͂̂�
		Position position;	///< �����\���ʒu

		CreateWindowParam()
		{
			class_id		 = GetClassId();
			is_tab_stop		 = true;
			is_draw_edge	 = true;
			is_multi_line	 = false;
			is_read_only	 = false;
			is_number_only	 = false;
			position		 = Position::POSITION_LEFT;
		}
	};
private:
	//========================================================
	//val
public:
	//========================================================
	//func
	static size_t GetClassId() { return WINDOW_TEXT_BOX_ID; }
protected:
	virtual void OnInitialize(const CreateWindowParamBase& param) override;
	virtual void OnMessage(WORD word) override;
};
} //namespace win

