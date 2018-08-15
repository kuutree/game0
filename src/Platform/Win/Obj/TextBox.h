#pragma once
//=========================================================
//include
#include "../Window.h"


namespace win {
//*********************************************************
//テキストボックス
//*********************************************************
class TextBox : public Window
{
public:
	//*********************************************************
	//ウインドウ作成パラメータ
	//*********************************************************
	struct CreateWindowParam : public CreateWindowParamBase
	{
		bool is_tab_stop;	///< タブ入力でフォーカスがあう
		bool is_draw_edge;	///< 境界線描画
		bool is_multi_line;	///< 複数行表示	+ 縦スクロール
		bool is_read_only;	///< 読み込みのみ
		bool is_number_only;///< 数字入力のみ
		Position position;	///< 文字表示位置

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

