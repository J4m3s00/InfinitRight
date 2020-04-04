#pragma once

namespace IR {

	class InfinitRightObject
	{
	public:
		InfinitRightObject(const IRUUID& uuid = IRUUID().CreateNew());
		virtual ~InfinitRightObject();
	private:
		IRVector<InfinitRightProperty*>			fProperties;

		IR_DEFINE_PROPERTY(Name, IRString);
		IR_DEFINE_PROPERTY(Uuid, IRUUID);
		IR_DEFINE_OBJ_PROPERTY(Parent);
		IR_DEFINE_OBJ_PROPERTY(Next);
		IR_DEFINE_OBJ_PROPERTY(Prev);
		IR_DEFINE_OBJ_PROPERTY(FirstChild);

		IR_DEFINE_OBJ_PROPERTY(InternContainer);
	protected:
		IRString fObjectType;
	public:
		void FromJs(const IRJson& json);
		void SetJs(IRJson& json) const;

		virtual void OnFromJs(const IRJson& json) {}
		virtual void OnSetJs(IRJson& json) const {}

		void PushProperty(InfinitRightProperty* prop);

		void AddChild(InfinitRightObject* object);
		void SetNewNext(InfinitRightObject* next);
		void SetNewPrev(InfinitRightObject* prev);

	private:
		static void Delete(InfinitRightObject* obj); //This disconnects the object from the hierarchy
	};

}