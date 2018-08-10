///////////////////////////////////////////////////////////
/// 定義一覧
/// 
/// 
///////////////////////////////////////////////////////////
#pragma once


///////////////////////////////////////////////////////////
///BUILD_ERROR用クラス
///
///false時を未定義にすることで
///意図的にビルドに失敗するようにする
///////////////////////////////////////////////////////////
template<bool T> struct BuildError;
template<> struct BuildError < true > { };


//=========================================================
//define
///--------------------------------------------------------
///ビルドの段階で異常を検知する
#define BUILD_ERROR(result) BuildError<result>()
///--------------------------------------------------------
///コピー禁止クラス
#define NO_COPY_CLASS(class_name)						\
	class_name(const class_name&) = delete;				\
	class_name& operator=(const class_name&) = delete

//ビット
#define BIT_OR(a , b)			((a) | (b))			///< OR
#define BIT_AND(a , b)			((a) & (b))			///< AND
#define BIT_XOR(a , b)			((a) ^ (b))			///< XOR
#define BIT_NOT(val)			(~(val))			///< 反転
#define BIT_SHIFT_L(val , move)	((val) << (move))	///< シフト演算左
#define BIT_SHIFT_R(val , move)	((val) >> (move))	///< シフト演算右


//変換
#define TO_WSTR(str) L#str

