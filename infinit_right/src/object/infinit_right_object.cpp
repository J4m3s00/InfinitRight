#include "prefix.h"

namespace IR {

	InfinitRightObject::InfinitRightObject(const IRUUID& uuid)
		: fProperties(),
		IR_INIT_PROPERTY(Name),
		IR_INIT_PROPERTY_A1(Uuid, uuid),
		IR_INIT_PROPERTY(Parent),
		IR_INIT_PROPERTY(Next),
		IR_INIT_PROPERTY(Prev),
		IR_INIT_PROPERTY(FirstChild),
		IR_INIT_PROPERTY(InternContainer)
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

		json["ObjectType"] = fObjectType;
	}



	void InfinitRightObject::AddChild(InfinitRightObject* object)
	{
		Delete(object);
		InfinitRightObject* currentChild = GetFirstChild();
		if (!currentChild)
		{
			SetFirstChild(object);
		}
		else
		{
			while (currentChild->GetNext())
			{
				currentChild = currentChild->GetNext();
			}
			currentChild->SetNext(object);
			object->SetPrev(currentChild);
			object->SetParent(currentChild->GetParent());
		}
	}

	void InfinitRightObject::SetNewNext(InfinitRightObject* next)
	{
		Delete(next);
		InfinitRightObject* currentNext = GetNext();

		SetNext(next);
		if (currentNext)
		{
			currentNext->SetPrev(next);
		}

		if (next)
		{
			next->SetNext(currentNext);
			next->SetPrev(this);
			next->SetParent(GetParent());
		}
	}

	void InfinitRightObject::SetNewPrev(InfinitRightObject* prev)
	{
		Delete(prev);
		InfinitRightObject* currentPrev = GetPrev();

		SetPrev(prev);
		if (currentPrev)
		{
			currentPrev->SetNext(prev);
		}

		if (prev)
		{
			prev->SetPrev(currentPrev);
			prev->SetNext(this);
			prev->SetParent(GetParent());
		}
	}




	//STATIC HELPER FN
	void InfinitRightObject::Delete(InfinitRightObject* obj)
	{
		if (!obj) { return;  }
		InfinitRightObject* prev = obj->GetPrev();
		InfinitRightObject* next = obj->GetNext();
		InfinitRightObject* parent = obj->GetParent();

		if (!prev && parent && parent->GetFirstChild() == obj) { parent->SetFirstChild(next); }

		if (next) { next->SetPrev(prev); }
		if (prev) { prev->SetNext(next); }
	}
}