#include "prefix.h"

namespace IR {

	InfinitRightObject::InfinitRightObject(const IRUUID& uuid)
		:	fProperties(),
			fName("Name", this),
			fUuid("UUID", this)
	{	
		fUuid.SetValue(uuid);
	}

	InfinitRightObject::~InfinitRightObject()
	{
		fProperties.clear();
	}

	void InfinitRightObject::PushProperty(InfinitRightProperty* prop)
	{
		fProperties.push_back(prop);
	}

	const IRString& InfinitRightObject::GetName() const
	{
		return fName.GetValue();
	}

	const InfinitRightValueProperty<IRString>* InfinitRightObject::GetNameProperty() const
	{
		return &fName;
	}

	void InfinitRightObject::SetName(const IRString& name)
	{
		fName.SetValue(name);
	}

	const IRUUID& InfinitRightObject::GetUuid() const
	{
		return fUuid.GetValue();
	}

	const InfinitRightValueProperty<IRUUID>* InfinitRightObject::GetUuidProperty() const
	{
		return &fUuid;
	}

	void InfinitRightObject::SetUuid(const IRUUID& uuid)
	{
		fUuid.SetValue(uuid);
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
	}



}