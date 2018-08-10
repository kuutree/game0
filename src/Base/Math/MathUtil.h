///////////////////////////////////////////////////////////
///数学的汎用処理
///
///
///////////////////////////////////////////////////////////
#pragma once
//=========================================================
//include
#include <math.h>
#include <float.h>


namespace base {
namespace math {
//=========================================================
//前方宣言
float ToRadian(float degree);
//=========================================================
//const
const float PI			  = 3.14159265359f;
const float RADIAN_90	  = ToRadian(90.0f);
const float RADIAN_180	  = ToRadian(180.0f);
const float RADIAN_360	  = ToRadian(360.0f);
const float FLOAT_EPSILON = FLT_EPSILON;
//=========================================================
//func
template<class T> bool IsGreater(const T& val, const T& max)  { return val > max; }					  ///< 指定値より大きい
template<class T> bool IsLess(const T& val, const T& min) 	  { return val < min; }					  ///< 指定値より小さい
template<class T> const T& Max(const T& val1, const T& val2)  { return (val1 > val2) ? val1 : val2; } ///< 最大値取得
template<class T> const T& Min(const T& val1, const T& val2)  { return (val1 < val2) ? val1 : val2; } ///< 最小値取得
template<class T> const T& Clamp(const T& val, const T& min, const T& max) { return (val  > max) ? max : ((val  < min) ? min : val); } ///< 値を指定範囲内に収める
template<class T> int Sign(const T& val)	{ return ((val != 0) ? ((val > 0) ? 1 : -1) : 0); }		///< 符号
template<class T> T Abs(const T& val)		{ return (val > 0) ? val : -val; }						///< 絶対値
template<class T> void Exchange(T* p1, T* p2) { T tmp = *p1; *p1 = *p2; *p2 = tmp; }				///< 値を交換する
inline bool  IsEqualFloat(float v0, float v1, float tolerance = FLOAT_EPSILON)	{ return (v0 <= v1 + tolerance && v0 >= v1 - tolerance); }	///< 指定した値はほぼ等しいか
inline bool  IsZeroFloat(float val, float tolerance = FLOAT_EPSILON)			{ return IsEqualFloat(val, 0.0f, tolerance); }				///< 指定した小数値は0か？
inline float Reciprocal(float v)					{ return (v != 0.0f) ? 1.0f / v : 0.0f; }		///< 逆数  ０の場合は無限ではなく0を返す
inline float Lerp(float ratio, float v0, float v1)	{ return (v1 - v0) * ratio + v0; }				///< 線形補間
inline float Sqrt(float val)						{ return sqrtf(val); }							///< 平方根
inline float HalfRadian(float radian)																///< -180～180の間でラジアン値を表現
{
	int sign = Sign(radian);
	radian -= (int)(radian * (1.0f / RADIAN_360)) * RADIAN_360;
	if (radian * sign > RADIAN_360 * 0.5f)	radian -= RADIAN_360 * sign;
	return radian;
}
inline float ToRadian(float degree)					{ return degree * (PI / 180.0f); }				///< 角度からラジアンに変換
inline float ToDegree(float radian)					{ return radian * (180.0f / PI); }				///< ラジアンから角度に変換
inline float Cos(float radian)						{ return cosf(radian); }						///< コサイン
inline float Sin(float radian)						{ return sinf(radian); }						///< サイン
inline float Tangent(float cos, float sin)			{ return sin * Reciprocal(cos); }				///< タンジェント
inline float Cotangent(float cos, float sin)		{ return Reciprocal(Tangent(cos, sin)); }		///< コタンジェント
inline float Atan2(float cos, float sin)			{ return atan2f(sin, cos); }					///< アークタンジェント
///--------------------------------------------------------
///二次方程式の解
///ax^2 + bx + c = 0
///x = -b +-sqrt(b2 - 4ac) / 2a;
bool SolutionOfQuadraticEquation(float* p_result0, float* p_result1, float a, float b, float c);
} //namespace math
} //namespace base