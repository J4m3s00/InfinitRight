#pragma once

namespace IR {

	class InfinitRightObject;

	class InfinitRightProperty
	{
	public:
		InfinitRightProperty(const IRString& name, InfinitRightObject* object);
		virtual ~InfinitRightProperty() {}

		virtual void FromJs(const IRJson& json) = 0;
		virtual void SetJs(IRJson& json) const = 0;
	protected:
		IRString fName;
	};

	template <typename ValueType>
	class InfinitRightValueProperty : public InfinitRightProperty
	{
	public:
		InfinitRightValueProperty(const IRString& name, InfinitRightObject* object) : InfinitRightProperty(name, object) { fValue = new ValueType(); }
		virtual ~InfinitRightValueProperty() { if (fValue) { delete fValue;  } }
	private:
		ValueType* fValue;
	public:
		void SetValue(const ValueType&value)
		{
			*fValue = value;
		}

		const ValueType& GetValue() const
		{
			return *fValue;
		}

		virtual void FromJs(const IRJson& json)
		{
			if (JS_CON::HasObjectProperty(fName.c_str(), json))
			{
				ValueType temp_value;
				JS_CON::ConvertObject(json, temp_value);
				SetValue(temp_value);
			}
		}

		virtual void SetJs(IRJson& json) const
		{
			json[fName] = JS_CON::ConvertValue(fValue);
		}
	};

}