#pragma once

namespace IR {

	class InfinitRightProperty
	{
	public:
		InfinitRightProperty(const IRString& name) : fName(name) {}
	protected:
		IRString fName;
	};

	template <typename ValueType>
	class InfinitRightValueProperty : public InfinitRightProperty
	{
	public:
		InfinitRightValueProperty(const IRString& name) : InfinitRightProperty(name) { fValue = new ValueType(); }
	private:
		ValueType* fValue;
	};

}