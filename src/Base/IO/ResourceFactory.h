///////////////////////////////////////////////////////////
///
///
///
///////////////////////////////////////////////////////////
#pragma once
//=========================================================
//include
#include "ResourceId.h"
#include "Resource.h"
#include <Base/Mem/Factory.h>
#include <memory>


//=========================================================
//define
#define REGISTER_RESOURCE_FACTORY_UNIT(RESOURCE_CLASS, CLASS_ID) \
class FactoryUnit##RESOURCE_CLASS : public base::io::ResourceFactory::Unit \
{ \
	static FactoryUnit##RESOURCE_CLASS s_instance; \
public: \
	FactoryUnit##RESOURCE_CLASS() { base::io::ResourceFactory::Register(CLASS_ID, this); } \
	virtual CreatePtr operator()(const CreateParam& param) override \
	{ \
		CreatePtr p_object = CreatePtr(new RESOURCE_CLASS()); \
		if(!p_object->Initialize(param)) return nullptr; \
		return p_object; \
	} \
}; \
FactoryUnit##RESOURCE_CLASS FactoryUnit##RESOURCE_CLASS::s_instance;


namespace base {
namespace io {
using ResourceFactory = base::mem::Factory<std::shared_ptr<Resource>, Resource::InitParam, RESOURCE_ID_MAX>;
} //namespace io
} //namespace base

