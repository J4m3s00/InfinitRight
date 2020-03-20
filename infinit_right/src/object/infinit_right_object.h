#pragma once

namespace IR {

	class InfinitRightObject
	{
	public:
		InfinitRightObject(const IRUUID& uuid = IRUUID().CreateNew());
		virtual ~InfinitRightObject();
	private:
		IRVector<InfinitRightProperty*>			fProperties;
		InfinitRightValueProperty<IRString>		fName;
		InfinitRightValueProperty<IRUUID>		fUuid;
	public:
		const IRString&								GetName() const;
		const InfinitRightValueProperty<IRString>*	GetNameProperty() const;
		void										SetName(const IRString& name);

		const IRUUID&								GetUuid() const;
		const InfinitRightValueProperty<IRUUID>*	GetUuidProperty() const;
		void										SetUuid(const IRUUID& name);

		void FromJs(const IRJson& json);
		void SetJs(IRJson& json) const;

		virtual void OnFromJs(const IRJson& json) {}
		virtual void OnSetJs(IRJson& json) const {}

		void PushProperty(InfinitRightProperty* prop);
	};

}