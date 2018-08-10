#include "FrameLayout.h"
#include <base/math/MathUtil.h>
#include <base/debug/Assert.h>


namespace win {
//=========================================================
//子供を作る
void FrameLayout::MakeChild(FrameLayout** pFrameBuff, size_t buffSize, const Setting& setting) const
{
	RectInt child_pos;
	child_pos.SetLeftUpOrigin(m_contents_pos);

	int cut_x = (setting.cut_x > 0) ? (int)setting.cut_x : 1;
	int cut_y = (setting.cut_y > 0) ? (int)setting.cut_y : 1;
	DB_ASSERT(cut_x * cut_y >= buffSize);

	int add_x = child_pos.right / cut_x;
	int add_y = child_pos.bottom / cut_y;

	FrameLayout tmp;
	tmp.m_contents_pos.right = add_x;
	tmp.m_contents_pos.bottom = add_y;
	tmp.AddMargin(setting.margin);
	tmp.AddPadding(setting.padding);


	for (int i = 0; i < buffSize; ++i)
	{
		FrameLayout& frame = *pFrameBuff[i];
		frame.m_contents_pos = tmp.m_contents_pos;
		frame.m_margin		 = tmp.m_margin;
		frame.m_padding		 = tmp.m_padding;
		frame.m_contents_pos.ShiftX(add_x * (i % cut_x));
		frame.m_contents_pos.ShiftY(add_y * (i / cut_x));
	}
}


//=========================================================
//縦横指定した向きに分割する
void FrameLayout::Separate(RectInt* pDst0, RectInt* pDst1,  float ratio, bool isSideSeparate)
{
	ratio = base::math::Clamp(ratio, 0.0f, 1.0f);

	RectInt child_pos;
	child_pos.SetLeftUpOrigin(m_contents_pos);
	*pDst0 = *pDst1 = child_pos;

	if (isSideSeparate)	pDst0->right  = pDst1->left = (int)(pDst1->right * ratio);
	else				pDst0->bottom = pDst1->top  = (int)(pDst1->bottom * ratio);
}


//=========================================================
//スペースを割り当てる
void FrameLayout::_CalcSpace(RectInt* pPos, RectInt* pSpace, const RectInt& addSpace)
{
	int size_x = pPos->GetWidth();
	int size_y = pPos->GetHeight();
	int add;

	add = base::math::Min(addSpace.left, size_x);	pSpace->left += add;	pPos->left += add;	 size_x -= add;
	add = base::math::Min(addSpace.right, size_x);	pSpace->right += add;	pPos->right -= add;
	add = base::math::Min(addSpace.top, size_y);	pSpace->top += add;		pPos->top += add;	 size_y -= add;
	add = base::math::Min(addSpace.bottom, size_y);	pSpace->bottom += add;	pPos->bottom -= add;
}
}//namespace win

