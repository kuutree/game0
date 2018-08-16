#include "Window.h"
#include "WindowManager.h"
#include <base/debug/Assert.h>


namespace win {
//=========================================================
//static
const RectInt Window::SD_SIZE	   = RectInt(720, 480);
const RectInt Window::HD_SIZE	   = RectInt(1280, 720);
const RectInt Window::FULL_HD_SIZE = RectInt(1920, 1080);


//=========================================================
//デストラクタ
Window::~Window()
{
	DB_ASSERT(m_h_wndow == nullptr);
}


//=========================================================
//初期化
void Window::Initialize(const CreateWindowParamBase& param)
{
	m_tag = param.tag;
	OnInitialize(param);
}


//=========================================================
//終了
void Window::Finalize()
{
	for (NodePtrList::iterator ite = GetChildPtrList().begin(); ite != GetChildPtrList().end(); ite = GetChildPtrList().begin())
	{
		auto& node_ptr = *ite;
		node_ptr->Finalize();
		PopChild(node_ptr);	
	}
	
	OnFinalize();
}


//=========================================================
//メッセージ
void Window::Message(WORD word)
{
	OnMessage(word);
}


//=========================================================
//表示・非表示
void Window::Show(ShowType show_type)
{
	Show((int)show_type);
}


//=========================================================
//ウインドウ作成
bool Window::Create(const CreateWindowArg& param)
{
	m_h_wndow = CreateWindowEx(
		param.ex_style,					//拡張ウインドウスタイル
		param.class_name,				//ウインドウクラス名
		param.title_name,				//ウインドウ名、タイトルバーがある場合はタイトル名として表示
		param.style,					//ウインドウスタイル
		//ウインドウ配置
		param.rect.left, param.rect.top,
		param.rect.GetWidth(), param.rect.GetHeight(),
		param.h_parent,					//親ウインドウ
		param.h_menu,					//子ウインドウ
		param.h_instance,				//インスタンスハンドル
		param.p_user_data);				//ユーザーデータ	

	return (m_h_wndow != nullptr);
}



//=========================================================
//スタイル問い合わせ-子供関連
uint32_t Window::QueryStyleSettingChild(NodePtr parent_ptr, ChildType child_type) const
{
	if (!parent_ptr)	return 0;
	//=========================================================
	//スタイル
	switch (child_type)
	{
	case ChildType::CHILD_CHILD:	return WS_CHILD;
	case ChildType::CHILD_POPUP:	return WS_POPUP;
	default:
		DB_ASSERT(false);
		break;
	}

	return 0;
}


//=========================================================
//表示設定変更
void Window::Show(int show)
{
	ShowWindow(m_h_wndow, show);
}


//=========================================================
//終了
void Window::OnFinalize()
{
	if (m_h_wndow != nullptr)
	{
		DestroyWindow(m_h_wndow);
		m_h_wndow = nullptr;
	}
}
}//namespace win

