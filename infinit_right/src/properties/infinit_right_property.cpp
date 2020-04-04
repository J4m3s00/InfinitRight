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
		if (fValue->GetUuid() == value->GetUuid()) { return; }
		IRJson oldValue = IRJson::object();
		IRJson newValue = IRJson::object();

		oldValue[fName] = JS_CON::ConvertValue(fValue->GetUuid());
		newValue[fName] = JS_CON::ConvertValue(value->GetUuid());

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
					IRString objectType;
					if (JS_CON::GetParamStringSafe("ObjectType", objectJson, objectType))
					{
						InfinitRightApp::gApp().GetActiveDrawing()->CreateNewObject(InfinitRightApp::new_object(objectType))->FromJs(objectJson);
					}
				}
			}

		}
	}

	void InfinitRightObjectProperty::SetJs(IRJson& json) const
	{
		static bool recursionStop = false; //Little blocker so objects can reference each other without infinit deep json
		if (fValue && !recursionStop)
		{
			recursionStop = true;
			fValue->SetJs(json[fName]);
		}
		recursionStop = false;
	}

}