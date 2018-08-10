///////////////////////////////////////////////////////////
///
///
///
///////////////////////////////////////////////////////////
#pragma once
//=========================================================
//include
#include "Type.h"
#include "Window.h"
#include <Base/Mem/Factory.h>
#include <memory>


//=========================================================
//define
#define REGISTER_WINDOW_FACTORY_UNIT(WINDOW_CLASS, CLASS_ID) \
class FactoryUnit##WINDOW_CLASS : public win::WindowFactory::Unit \
{ \
	static FactoryUnit##WINDOW_CLASS s_instance; \
public: \
	FactoryUnit##WINDOW_CLASS() { win::WindowFactory::Register(CLASS_ID, this); } \
	virtual CreatePtr operator()(const CreateParam& param) override \
	{ \
		CreatePtr p_object = CreatePtr(new WINDOW_CLASS()); \
		p_object->Initialize(param); \
		return p_object; \
	} \
}; \
FactoryUnit##WINDOW_CLASS FactoryUnit##WINDOW_CLASS::s_instance;


namespace win {
using WindowFactory = base::mem::Factory<std::shared_ptr<Window>, CreateWindowParam, WINDOW_ID_MAX>;
} //namespace win

