///////////////////////////////////////////////////////////
///
///
///
///////////////////////////////////////////////////////////
#pragma once
//=========================================================
//include
#include <Windows.h>
#include <memory>


namespace win {
//=========================================================
//前方宣言
class Window;


//*********************************************************
//WindowId
//*********************************************************
enum WindowId : size_t
{
	WINDOW_ID,
	WINDOW_FRAME_ID,
	WINDOW_ID_MAX,
};


//*********************************************************
//ChildType
//*********************************************************
enum class ChildType : size_t
{
	CHILD_NONE,				///< 子ウインドウとして作成しない
	CHILD_CHILD = WS_CHILD,	///< 親ウインドウの一部としてウインドウ作成
	CHILD_POPUP = WS_POPUP,	///< ポップアップウインドウとしてウインドウ作成
};


//*********************************************************
//ShowType
//*********************************************************
enum class ShowType : size_t
{
	SHOW_HIDE	  = SW_HIDE,		///< ウィンドウを非表示
	SHOW_MAXIMIZE = SW_MAXIMIZE,	///< ウィンドウを最大化します
	SHOW_MINIMIZE = SW_MINIMIZE,	///< ウィンドウを最小化します
	SHOW_RESTORE  = SW_RESTORE,		///< ウィンドウをアクティブにする	最小化または最大化されている場合は元の位置とサイズに戻る
	SHOW_SHOW	  = SW_SHOW			///< ウィンドウをアクティブにする
};


//*********************************************************
//Position
//*********************************************************
enum class Position : size_t
{
	POSITION_LEFT = ES_LEFT,
	POSITION_CENTER = ES_CENTER,
	POSITION_RIGHT = ES_RIGHT,
};


//*********************************************************
//FramePosition
//*********************************************************
template<class T>
struct Rect
{
	T left, right, top, bottom;

	Rect() { Clear(); }
	Rect(T width, T height) { left = top = 0, right = width, bottom = height; }
	void Clear() { left = right = top = bottom = 0; }
	void SetLeftUpOrigin(const Rect& pos)
	{
		right = pos.GetWidth();
		bottom = pos.GetHeight();
		left = top = 0;
	}
	void ShiftX(T x) { left += x, right += x; }
	void ShiftY(T y) { top += y, bottom += y; }
	T GetWidth() const { return right - left; }
	T GetHeight() const { return bottom - top; }

	void RECTToRect(const RECT& rect) { left = rect.left, right = rect.right, top = rect.top, bottom = rect.bottom; }
	void RectToRECT(RECT* p_dst) const { p_dst->left = left, p_dst->right = right, p_dst->top = top, p_dst->bottom = bottom; }
};
using RectInt = Rect<int>;


//*********************************************************
//CreateWindowParam
//*********************************************************
struct CreateWindowParam
{
	std::shared_ptr<Window> parent_ptr;
	size_t					class_id   = WindowId::WINDOW_ID;
	ChildType				child_type = ChildType::CHILD_NONE;
	int						show_mode  = 0;
	HINSTANCE				h_instance = nullptr;
	virtual ~CreateWindowParam() { /*何もしない*/ }
	template<class T> const T& Cast() const { return static_cast<const T&>(*this); }

	//base::math::RectInt		area;
	//union
	//{
	//	struct
	//	{
	//		bool is_tab_stop;	///< タブ入力でフォーカスがあう
	//		bool is_caption;	///< タイトルを表示するか
	//		bool is_frame;		///< フレームを表示するか
	//		bool is_close;		///< 閉じるボタンをつけるか
	//		bool is_adjust;		///< areaで指定した値をクライアント領域を現す領域扱いとし、ウィンドウ位置とサイズを調節する
	//		const wchar_t* title;
	//	} overlap;
	//	struct
	//	{
	//		bool is_tab_stop;	///< タブ入力でフォーカスがあう
	//		bool is_draw_edge;	///< 境界線描画
	//		bool is_multi_line;	///< 複数行表示	+ 縦スクロール
	//		bool is_read_only;	///< 読み込みのみ
	//		bool is_number_only;///< 数字入力のみ
	//		Position position;	///< 文字表示位置
	//	} edit;
	//	struct
	//	{
	//		bool is_tab_stop;	///< タブ入力でフォーカスがあう
	//	} button;
	//};
	//
	//CreateInfo(WndType _type) { SetDefaultParam(_type); }
	//void SetDefaultParam(WndType _type);	///< 指定したウインドウタイプで使用されるパラメータの初期化する
};
} //namespace win
