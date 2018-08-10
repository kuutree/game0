///////////////////////////////////////////////////////////
///ファクトリ
///
///
///////////////////////////////////////////////////////////
#pragma once
//=========================================================
//include
#include <array>


namespace base {
namespace mem {
//*********************************************************
//Factory
//*********************************************************
template<class TPtr, class TParam, size_t ClassIdMax>
class Factory
{
public:
	//=========================================================
	//using
	using CreatePtr   = TPtr;
	using CreateParam = TParam;
	using SelfType	  = Factory<TPtr, TParam, ClassIdMax>;
	//*********************************************************
	//Unit
	//*********************************************************
	class Unit
	{
	public:
		using CreatePtr	  = TPtr;
		using CreateParam = TParam;
	public:
		virtual ~Unit() { /*何もしない*/ }
		virtual CreatePtr operator()(const CreateParam& param) = 0;
	};
private:
	//=========================================================
	//val
	static SelfType				  s_factory;
	std::array<Unit*, ClassIdMax> m_p_unit_buff;
public:
	//=========================================================
	//func
	static void Register(size_t class_id, Unit* p_unit)
	{
		s_factory.m_p_unit_buff[class_id] = p_unit;
	}
	static CreatePtr Create(size_t class_id, const CreateParam& param)
	{
		Unit* p_unit = s_factory.m_p_unit_buff[class_id];
		return (p_unit != nullptr) ? (*p_unit)(param) : nullptr;
	}
};
//=========================================================
//static
template<class TPtr, class TParam, size_t ClassIdMax>
Factory<TPtr, TParam, ClassIdMax> Factory<TPtr, TParam, ClassIdMax>::s_factory;
} //namespace mem
} //namespace base

