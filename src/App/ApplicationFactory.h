///////////////////////////////////////////////////////////
///
///
///
///////////////////////////////////////////////////////////
#pragma once
//=========================================================
//include
#include "Type.h"
#include "Application.h"
#include <Base/Mem/Factory.h>
#include <memory>


//=========================================================
//define
#define REGISTER_APPLICATION_FACTORY_UNIT(APPLICATION_CLASS, CLASS_ID) \
class FactoryUnit##APPLICATION_CLASS : public app::ApplicationFactory::Unit \
{ \
	static FactoryUnit##APPLICATION_CLASS s_instance; \
public: \
	FactoryUnit##APPLICATION_CLASS() { app::ApplicationFactory::Register(CLASS_ID, this); } \
	virtual CreatePtr operator()(const CreateParam& param) override \
	{ \
		CreatePtr p_object = CreatePtr(new APPLICATION_CLASS()); \
		p_object->Initialize(param); \
		return p_object; \
	} \
}; \
FactoryUnit##APPLICATION_CLASS FactoryUnit##APPLICATION_CLASS::s_instance;


namespace app {
using ApplicationFactory = base::mem::Factory<std::shared_ptr<Application>, CreateApplicationParam, APPLICATION_ID_MAX>;
} //namespace app
