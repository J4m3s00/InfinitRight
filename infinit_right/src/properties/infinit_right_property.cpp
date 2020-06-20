#include "prefix.h"

namespace IR {

	void HandleValueChange(InfinitRightObject* object, const IRJson& oldValue, const IRJson& newValue)
	{
		InfinitRightUndoAction* currentAction = InfinitRightApp::gApp().GetUndoManager().GetActiveAction();
		if (currentAction && object)
		{
			currentAction->AddObjectChangeValue(object->GetUuid(), oldValue, newValue);
		}
	}

	InfinitRightProperty::InfinitRightProperty(const IRString& name, InfinitRightObject* object)
		: fName(name), fObject(object)
	{
		object->PushProperty(this);
	}
	

	//----------------------------------------------------------------------------------------------------------------------------------------
	//INFINIT RIGHT OBJECT PROPERTY

	InfinitRightObjectProperty::InfinitRightObjectProperty(const IRString& name, InfinitRightObject* parentObject, InfinitRightObject* value)
		: InfinitRightProperty(name, parentObject)
	{
		fValue = value;
	}
	void InfinitRightObjectProperty::SetValue(InfinitRightObject* value)
	{
		if (fValue == value) { return; }
		if (fValue && value && fValue->GetUuid() == value->GetUuid()) { return; }

		IRJson oldValue = IRJson::object();
		IRJson newValue = IRJson::object();

		oldValue[fName] = JS_CON::ConvertValue(fValue ? fValue->GetUuid() : IRUUID());
		newValue[fName] = JS_CON::ConvertValue(value ? value->GetUuid() : IRUUID());

		HandleValueChange(fObject, oldValue, newValue);
		fValue = value;
	}

	InfinitRightObject* InfinitRightObjectProperty::GetValue() const
	{
		return fValue;
	}

	void InfinitRightObjectProperty::FromJs(const IRJson& json)
	{
		if (JS_CON::HasObjectProperty(fName.c_str(), json))
		{
			const IRJson& objectJson = json[fName];

			IRUUID objectUuid;
			if (JS_CON::GetParamUUIDSafe("UUID", objectJson, objectUuid))
			{
				InfinitRightObject* object = InfinitRightApp::gApp().GetActiveDrawing()->GetObjectByUuid(objectUuid);
				if (object)
				{
					SetValue(object);
				} //If we could not find the object with the uuid we crete it
				else
				{
					u32 objectType;
					if (JS_CON::GetParamUintSafe("ObjectType", objectJson, objectType))
					{
						InfinitRightApp::gApp().GetActiveDrawing()->CreateNewObject(objectType)->FromJs(objectJson);
					}
				}
			}

		}
	}

	void InfinitRightObjectProperty::SetJs(IRJson& json) const
	{
		static bool recursionStop = false; //Little blocker so objects can reference each other without infinit deep json
		if (fValue)
		{
			if (!recursionStop)
			{
				recursionStop = true;
				fValue->SetJs(json[fName]);
			}
			else
			{
				json[fName] = JS_CON::ConvertValue(fValue->GetUuid());
			}
		}
		recursionStop = false;
	}

}