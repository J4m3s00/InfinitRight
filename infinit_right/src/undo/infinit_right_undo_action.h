#pragma once

namespace IR {

	class InfinitRightUndoAction
	{
		friend class InfinitRightUndoManager;
	public:
		InfinitRightUndoAction(const IRString& name);
		~InfinitRightUndoAction();
	private:
		IRString							fName;
		IRVector<InfinitRightUndoValue*>	fValues;
	public:
		void AddObjectChangeValue(InfinitRightObject* object, const IRJson& js_oldValue, const IRJson& newValue);
		void AddObjectCreateValue(InfinitRightObject* object, const IRJson& js_object);
		void AddObjectDeleteValue(InfinitRightObject* object, const IRJson& js_object);
	};

}