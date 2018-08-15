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
//*********************************************************
//WindowId
//*********************************************************
enum WindowId : size_t
{
	WINDOW_ID,
	WINDOW_FRAME_ID,
	WINDOW_BUTTON_ID,
	WINDOW_CHECK_BOX_ID,
	WINDOW_RADIO_BUTTON_ID,
	WINDOW_TEXT_BOX_ID,
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
	void SetLeftUpOrigin(const T& width, const T& height)
	{
		right = width;
		bottom = height;
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
} //namespace win

