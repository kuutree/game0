#pragma once
//=========================================================
//include
#include "../Type.h"
#include "../Define.h"


namespace base {
namespace util {
///////////////////////////////////////////////////////////
///ビットフラグ集合
///
///
///////////////////////////////////////////////////////////
template<class _EnumType, uint _BIT_ALL>
class Bit
{
	//========================================================
	//type
	using EnumType = _EnumType;
	//========================================================
	//const
	static const uint BIT_ALL  = _BIT_ALL;
	static const uint BIT_MASK = BIT_NOT(_BIT_ALL);
	//========================================================
	//val
	uint m_val;
public:
	//========================================================
	//func
	Bit(const Bit& src)	{ m_val = src.m_val; }
	Bit(uint val = 0)	{ m_val = BIT_AND(val, BIT_ALL); }
	//========================================================
	//ビット操作
	void Flip() { m_val = BIT_XOR(BIT_NOT(m_val), BIT_MASK); }	///< ビットの反転
	//========================================================
	//ビット状態取得
	bool IsAnyEnable() const { return m_val != 0; }				///< 1つでもビットが立っている
	///-------------------------------------------------------
	///指定値で選択されたビットが有効になっているか
	bool IsEnable(EnumType val) const { return (m_val & val) == val; }
	bool IsEnable(uint val) const	  { return (m_val & val) == val; }
	uint GetBit()					  { return m_val; }
	//========================================================
	//operator
	bool operator[](uint val) const	{ return BIT_AND(m_val, val) == val; }
	Bit& operator=(const Bit& src)	{ m_val = src.m_val;				return *this; }
	Bit& operator=(uint val)		{ m_val = BIT_AND(val, BIT_ALL);	return *this; }
	Bit& operator|=(const Bit& src)	{ m_val |= src.m_val;				return *this; }
	Bit& operator|=(uint val)		{ m_val |= BIT_AND(val, BIT_ALL);	return *this; }
	Bit& operator&=(const Bit& src)	{ m_val &= src.m_val;				return *this; }
	Bit& operator&=(uint val)		{ m_val &= val;						return *this; }
	bool operator==(uint val) const	{ return m_val == val; }
	bool operator!=(uint val) const	{ return m_val != val; }
};
} //namespace util
} //namespace base

