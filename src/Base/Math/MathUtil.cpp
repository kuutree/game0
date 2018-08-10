//=========================================================
//include
#include "MathUtil.h"


namespace base {
namespace math {
//=========================================================
//�񎟕������̉�
bool SolutionOfQuadraticEquation(float* p_result0, float* p_result1, float a, float b, float c)
{
	//x = -b +-sqrt(b^2 - 4ac) / 2a;
	float tmp = (b * b) - (4 * a * c);

	//���������ɂȂ�
	if (tmp < 0.0f)
	{
		*p_result0 = 0.0f, *p_result1 = 0.0f;
		return false;
	}
	float denominator = 2 * a;
	tmp	= sqrtf(tmp);

	if (denominator != 0.0f) *p_result0 = (-b + tmp) / denominator, *p_result1 = (-b - tmp) / denominator;
	else					 *p_result0 = 0.0f, *p_result1 = 0.0f;
	return true;
}
} //math 
} //base

