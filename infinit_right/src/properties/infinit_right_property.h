#pragma once

namespace IR {

	class InfinitRightObject;

	extern void HandleValueChange(InfinitRightObject* object, const IRJson& oldValue, const IRJson& newValue);

	class InfinitRightProperty
	{
	public:
		InfinitRightProperty(const IRString& name, InfinitRightObject* object);
		virtual ~InfinitRightProperty() {}

		virtual void FromJs(const IRJson& json) = 0;
		virtual void SetJs(IRJson& json) const = 0;
	protected:
		IRString			fName;
		InfinitRightObject* fObject;
	};

	template <typename ValueType>
	class InfinitRightValueProperty : public InfinitRightProperty
	{
	public:
		InfinitRightValueProperty(const IRString& name, InfinitRightObject* object) : InfinitRightProperty(name, object) { fValue = new ValueType(); }
		InfinitRightValueProperty(const IRString& name, InfinitRightObject* object, const ValueType& initValue) : InfinitRightProperty(name, object) { fValue = new ValueType(initValue); }
		virtual ~InfinitRightValueProperty() { if (fValue) { delete fValue;  } }
	private:
		ValueType* fValue;
	public:
		void SetValue(const ValueType& value)
		{
			if (*fValue == value) { return; }
			IRJson oldValue = IRJson::object();
			IRJson newValue = IRJson::object();

			oldValue[fName] = JS_CON::ConvertValue(fValue);
			newValue[fName] = JS_CON::ConvertValue(value);

			HandleValueChange(fObject, oldValue, newValue);
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
				JS_CON::ConvertObject(json[fName.c_str()], temp_value);
				SetValue(temp_value);
			}
		}

		virtual void SetJs(IRJson& json) const
		{
			json[fName] = JS_CON::ConvertValue(fValue);
		}
	};

	class InfinitRightObjectProperty : public InfinitRightProperty
	{
	public:
		InfinitRightObjectProperty(const IRString& name, InfinitRightObject* parentObject, InfinitRightObject* value = nullptr);
	private:
		InfinitRightObject* fValue;
	public:
		void SetValue(InfinitRightObject* value);

		InfinitRightObject* GetValue() const;

		virtual void FromJs(const IRJson& json);

		virtual void SetJs(IRJson& json) const;
	};
}