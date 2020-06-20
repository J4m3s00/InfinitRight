#include "prefix.h"

namespace IR {
 
 
 	InfinitRightObject* InfinitRightObject::CreateNew(const ::IR::IRUUID uuid)
	{ 
		InfinitRightObject* result = new InfinitRightObject(uuid); 
		result->fObjectType = ::IR::InfinitRightApp::gApp().GetObjectIdFromTypeName("InfinitRightObject"); 
		return result; 
	}

	InfinitRightObject::InfinitRightObject(const IRUUID& uuid)
		: fProperties(),
		fUuid(uuid),
		IR_INIT_PROPERTY(Name)
	{	
	}

	InfinitRightObject::~InfinitRightObject()
	{
		fProperties.clear();
	}

	void InfinitRightObject::PushProperty(InfinitRightProperty* prop)
	{
		fProperties.push_back(prop);
	}

	void InfinitRightObject::FromJs(const IRJson& json)
	{
		for (InfinitRightProperty* prop : fProperties)
		{
			prop->FromJs(json);
		}
		OnFromJs(json);
	}

	void InfinitRightObject::SetJs(IRJson& json) const
	{
		for (InfinitRightProperty* prop : fProperties)
		{
			prop->SetJs(json);
		}
		OnSetJs(json);

		json["UUID"] = JS_CON::ConvertValue(fUuid);
		json["ObjectType"] = JS_CON::ConvertValue(fObjectType);
	}
}