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
		u32 fObjectType;
	public:
		void FromJs(const IRJson& json);
		void SetJs(IRJson& json) const;

		virtual void OnFromJs(const IRJson& json) {}
		virtual void OnSetJs(IRJson& json) const {}

		void PushProperty(InfinitRightProperty* prop);

		const IRUUID& GetUuid() const { return fUuid; }

	private:
		static void Delete(InfinitRightObject* obj); //This disconnects the object from the hierarchy
	};

}