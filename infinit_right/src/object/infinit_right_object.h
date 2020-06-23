#pragma once

namespace IR {

	class InfinitRightObject
	{
	public:
		static InfinitRightObject* CreateNew(const ::IR::IRUUID uuid = ::IR::IRUUID().CreateNew());
	public:
		InfinitRightObject(const IRUUID& uuid = IRUUID().CreateNew());
		virtual ~InfinitRightObject();
	private:
		IRVector<InfinitRightProperty*>			fProperties;

		IR_DEFINE_PROPERTY(Name, IRString);
		IRUUID fUuid;
	protected:
		IRObjectId fObjectType;
		IRObjectId fSuperType;		//This is the type of the first inheritance after the InfnitRightObject, This is used for callbacks to group all objects together that are inhertited
	public:
		void FromJs(const IRJson& json);
		void SetJs(IRJson& json) const;

		virtual void OnFromJs(const IRJson& json) {}
		virtual void OnSetJs(IRJson& json) const {}

		void PushProperty(InfinitRightProperty* prop);

		const IRUUID& GetUuid() const { return fUuid; }
		const IRObjectId& GetObjectTypeId() const { return fObjectType; }
		const IRObjectId& GetObjectSuperId() const { return fSuperType; }	// This is used for the callbacks, to group different object types to the one at the top of the inheritance

	private:
		static void Delete(InfinitRightObject* obj); //This disconnects the object from the hierarchy
	};

}