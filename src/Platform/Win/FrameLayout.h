#pragma once
#include "Type.h"


namespace win{
//*********************************************************
//FrameLayout
//*********************************************************
class FrameLayout
{
public:
	//*********************************************************
	//Setting
	//*********************************************************
	struct Setting
	{
		size_t  cut_x, cut_y;
		RectInt margin;
		RectInt padding;

		Setting() { cut_x = cut_y = 1; }
	};
private:
	//=========================================================
	//val
	RectInt m_contents_pos;
	RectInt m_margin;
	RectInt m_padding;
public:
	//=========================================================
	//func
	void MakeChild(FrameLayout** p_frame_buff, size_t buff_size, const Setting& setting) const;
	void Separate(RectInt* pDst0, RectInt* p_dst1, float ratio, bool is_side_separate);
	void AddMargin(const RectInt& margin)	{ _CalcSpace(&m_contents_pos, &m_margin, margin); }
	void AddPadding(const RectInt& padding)	{ _CalcSpace(&m_contents_pos, &m_padding, padding); }

	void SetContentsPos(RectInt& pos) { m_contents_pos = pos; }
	void SetMargin(RectInt& margin)	  { m_margin = margin; }
	void SetPadding(RectInt& padding) { m_padding = padding; }

	const RectInt& GetContentsPos() const { return m_contents_pos; }
	const RectInt& GetMargin() const	  { return m_margin; }
	const RectInt& GetPadding() const	  { return m_padding; }
private:
	void _CalcSpace(RectInt* p_pos, RectInt* p_space, const RectInt& add_space);
};
}//namespace win

