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
void Window::Initialize(const win::CreateWindowParam& param)
{
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

















































//#pragma once
//  //=========================================================
//  //include
//#include <base\math\Geometric.h>
//#include <Windows.h>
//#include <base\util\TreeStructure.h>
//#include <memory>
//
//
//namespace window {
//	///////////////////////////////////////////////////////////
//	///ウインドウ
//	///
//	///
//	///////////////////////////////////////////////////////////
//	class Window : public base::util::TreeStructure
//	{
//	public:
//		///////////////////////////////////////////////////////////
//		///ウインドウの種類
//		///
//		///
//		///////////////////////////////////////////////////////////
//		enum class WndType
//		{
//			OVERLAP,
//			EDIT,
//			BUTTON,
//			MAX,
//		};
//		///////////////////////////////////////////////////////////
//		///子供としてウインドウを作成する場合の種類
//		///
//		///
//		///////////////////////////////////////////////////////////
//		enum ChildType
//		{
//			CHILD_NONE,				///< 子ウインドウとして作成しない
//			CHILD_CHILD = WS_CHILD,	///< 親ウインドウの一部としてウインドウ作成
//			CHILD_POPUP = WS_POPUP,	///< ポップアップウインドウとしてウインドウ作成
//		};
//		///////////////////////////////////////////////////////////
//		///表示状態
//		///
//		///
//		///////////////////////////////////////////////////////////
//		enum ShowType
//		{
//			SHOW_HIDE = SW_HIDE,		///< ウィンドウを非表示
//			SHOW_MAXIMIZE = SW_MAXIMIZE,	///< ウィンドウを最大化します
//			SHOW_MINIMIZE = SW_MINIMIZE,	///< ウィンドウを最小化します
//			SHOW_RESTORE = SW_RESTORE,		///< ウィンドウをアクティブにする	最小化または最大化されている場合は元の位置とサイズに戻る
//			SHOW_SHOW = SW_SHOW			///< ウィンドウをアクティブにする
//		};
//		///////////////////////////////////////////////////////////
//		///テキスト表示位置
//		///
//		///
//		///////////////////////////////////////////////////////////
//		enum Position
//		{
//			POSITION_LEFT = ES_LEFT,
//			POSITION_CENTER = ES_CENTER,
//			POSITION_RIGHT = ES_RIGHT,
//		};
//		///////////////////////////////////////////////////////////
//		///ウインドウ作成パラメータ
//		///
//		///
//		///////////////////////////////////////////////////////////
//		struct CreateInfo
//		{
//			WndType					type;
//			std::weak_ptr<Window>	parent_ptr;
//			ChildType				child_type;
//			int						show_mode;
//			HINSTANCE				h_instance;
//			base::math::RectInt		area;
//			union
//			{
//				struct
//				{
//					bool is_tab_stop;	///< タブ入力でフォーカスがあう
//					bool is_caption;	///< タイトルを表示するか
//					bool is_frame;		///< フレームを表示するか
//					bool is_close;		///< 閉じるボタンをつけるか
//					bool is_adjust;		///< areaで指定した値をクライアント領域を現す領域扱いとし、ウィンドウ位置とサイズを調節する
//					const wchar_t* title;
//				} overlap;
//				struct
//				{
//					bool is_tab_stop;	///< タブ入力でフォーカスがあう
//					bool is_draw_edge;	///< 境界線描画
//					bool is_multi_line;	///< 複数行表示	+ 縦スクロール
//					bool is_read_only;	///< 読み込みのみ
//					bool is_number_only;///< 数字入力のみ
//					Position position;	///< 文字表示位置
//				} edit;
//				struct
//				{
//					bool is_tab_stop;	///< タブ入力でフォーカスがあう
//				} button;
//			};
//
//			CreateInfo(WndType _type) { SetDefaultParam(_type); }
//			void SetDefaultParam(WndType _type);	///< 指定したウインドウタイプで使用されるパラメータの初期化する
//		};
//	private:
//		//========================================================
//		//const
//		static const wchar_t* CLASS_NAMES[(size_t)WndType::MAX];
//		//========================================================
//		//val
//		HWND m_h_wndow;		///< ウインドウハンドル
//	public:
//		//========================================================
//		//func
//		Window() { m_h_wndow = nullptr; }					///< コンストラクタ
//		bool Create(const CreateInfo& init_param);			///< ウインドウ作成
//		void Show(int show_mode);							///< 表示/非表示
//		HWND GetWindowHandle() const { return m_h_wndow; }	///< ウインドウハンドルの取得
//	};
//} //namespace window
//



//  //=========================================================
//  //include
//#include "Window.h"
//#include "WindowSystem.h"
//#include <base\debug\Assert.h>
//
//
//namespace window {
//	//=========================================================
//	//static
//	const wchar_t* Window::CLASS_NAMES[(size_t)WndType::MAX] = {
//		L"OVERLAP",
//		L"EDIT",
//		L"BUTTON"
//	};
//
//
//	///////////////////////////////////////////////////////////
//	///Window::CreateInfo
//	///
//	///
//	///////////////////////////////////////////////////////////
//	//=========================================================
//	//指定したウインドウタイプで使用されるパラメータの初期化する
//	void Window::CreateInfo::SetDefaultParam(WndType _type)
//	{
//		DB_ASSERT(type != WndType::MAX);
//
//		type = _type;
//		parent_ptr.reset();
//		child_type = CHILD_NONE;
//		show_mode = SHOW_SHOW;
//		h_instance = nullptr;
//		area.Clear();
//
//		switch (type)
//		{
//			//========================================================
//			//OVERLAP
//		case WndType::OVERLAP:
//			overlap.is_tab_stop = false;
//			overlap.is_caption = true;
//			overlap.is_frame = true;
//			overlap.is_close = true;
//			overlap.is_adjust = true;
//			overlap.title = nullptr;
//			break;
//			//========================================================
//			//EDIT
//		case WndType::EDIT:
//			edit.is_tab_stop = true;
//			edit.is_draw_edge = true;
//			edit.is_multi_line = false;
//			edit.is_read_only = false;
//			edit.is_number_only = false;
//			edit.position = POSITION_LEFT;
//			break;
//			//========================================================
//			//BUTTON
//		case WndType::BUTTON:
//			button.is_tab_stop = true;
//			break;
//			//========================================================
//			//default
//		default:
//			break;
//		}
//	}
//
//
//	//=========================================================
//	//ウインドウ作成
//	bool Window::Create(const CreateInfo& init_param)
//	{
//		std::shared_ptr<Window>	parent_ptr = init_param.parent_ptr.lock();
//
//		HWND  parent_hwnd = nullptr;
//		HMENU hmenu = nullptr;
//		const wchar_t* title = L"";
//		const wchar_t* class_name = CLASS_NAMES[(size_t)init_param.type];
//		bool  is_new_class = false;
//		DWORD style = 0;
//		DWORD ex_style = 0;
//		int	  parent_flag = ((parent_ptr && parent_ptr->GetWindowHandle() != nullptr) ? 2 : 0)
//			| ((init_param.child_type != CHILD_NONE) ? 1 : 0);
//
//		base::math::RectInt area = init_param.area;
//
//		//=========================================================
//		//子ウインドウ
//		if (parent_flag == 0x03)
//		{
//			if (init_param.child_type == CHILD_CHILD)	style |= WS_CHILD;
//			else if (init_param.child_type == CHILD_POPUP)	style |= WS_POPUP;
//
//			parent_hwnd = parent_ptr->GetWindowHandle();
//		}
//		else if (parent_flag != 0x00)	return false;
//		//=========================================================
//		//オーバーラップウィンドウ
//		if (init_param.type == WndType::OVERLAP)
//		{
//			if (init_param.overlap.title == nullptr)	return false;
//
//			if (init_param.overlap.is_tab_stop)		style |= WS_TABSTOP;
//			if (init_param.overlap.is_caption
//				&&  init_param.overlap.is_frame)		style |= WS_OVERLAPPED;
//			else if (init_param.overlap.is_frame)   style |= WS_POPUP | WS_DLGFRAME;
//			else if (init_param.overlap.is_caption) style |= WS_POPUP | WS_CAPTION;
//			else									style |= WS_POPUP;
//			if (init_param.overlap.is_close)
//			{
//				if (!init_param.overlap.is_caption)	return false;	//タイトルバーがないとだめなので
//				style |= WS_SYSMENU;
//			}
//
//			is_new_class = true;
//			title = init_param.overlap.title;
//
//			if (init_param.overlap.is_adjust)
//			{
//				if (style == WS_OVERLAPPED) return false;	//WS_OVERLAPPEDのみだとAdjustWindowRectが意図した値を返さない
//
//				RECT rect = { area.x, area.y, area.x + area.w, area.y + area.h };
//				if (AdjustWindowRect(&rect, style, hmenu != nullptr) == FALSE)	return false;
//
//				//area.x = rect.left, area.y = rect.top;	//位置はそのまま
//				area.w = rect.right - rect.left, area.h = rect.bottom - rect.top;
//			}
//		}
//		//=========================================================
//		//テキストボックス
//		else if (init_param.type == WndType::EDIT)
//		{
//			if (init_param.edit.is_draw_edge)	ex_style |= WS_EX_CLIENTEDGE;
//
//			style |= (DWORD)init_param.edit.position | ES_AUTOHSCROLL;
//			if (init_param.edit.is_tab_stop)	style |= WS_TABSTOP;
//			if (init_param.edit.is_multi_line)	style |= ES_MULTILINE | ES_AUTOVSCROLL | ES_WANTRETURN;
//			if (init_param.edit.is_read_only)	style |= ES_READONLY;
//			if (init_param.edit.is_number_only)	style |= ES_NUMBER;
//		}
//		//=========================================================
//		//ボタン
//		else if (init_param.type == WndType::BUTTON)
//		{
//			style |= BS_PUSHBUTTON;
//			if (init_param.button.is_tab_stop)	 style |= WS_TABSTOP;
//		}
//
//		//=========================================================
//		//新しくウインドウクラスを追加する
//		if (is_new_class)
//		{
//			WNDCLASSEX class_info;
//			memset(&class_info, 0, sizeof(WNDCLASSEX));
//			class_info.cbSize = sizeof(class_info);
//			//class_info.lpfnWndProc	 = &Manager::WindowProcedure;
//			class_info.hInstance = init_param.h_instance;
//			class_info.lpszClassName = title;
//			RegisterClassEx(&class_info);
//
//			class_name = class_info.lpszClassName;
//		}
//
//
//		m_h_wndow = CreateWindowEx(
//			ex_style,						//拡張ウインドウスタイル
//			class_name,						//ウインドウクラス名
//			title,							//ウインドウ名、タイトルバーがある場合はタイトル名として表示
//			style,							//ウインドウスタイル
//											//ウインドウ配置
//			area.x, area.y,
//			area.w, area.h,
//			parent_hwnd,					//親ウインドウ
//			hmenu,							//子ウインドウ
//			init_param.h_instance,			//インスタンスハンドル
//			this);							//ユーザーデータ	
//
//		Show(init_param.show_mode);
//		return m_h_wndow != nullptr;
//	}
//
//
//	//=========================================================
//	//表示/非表示
//	void Window::Show(int show_mode)
//	{
//		if (m_h_wndow != nullptr)  ShowWindow(m_h_wndow, show_mode);
//	}
//} //namespace window
//
//
