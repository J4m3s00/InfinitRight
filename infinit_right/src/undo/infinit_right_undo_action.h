#pragma once

namespace IR {

	class InfinitRightUndoAction
	{
	public:
		InfinitRightUndoAction(const IRString& name, bool isUndoAction = false);
		~InfinitRightUndoAction();
	private:
		IRString							fName;
		IRVector<InfinitRightUndoValue*>	fValues;
		bool								fIsUndoAction;
	public:
		const IRVector<InfinitRightUndoValue*>& GetUndoValueList() const;
		const IRString& 						GetName() const;

		bool 									IsUndoAction() const;

		void AddObjectChangeValue(InfinitRightObject* object, const IRJson& js_oldValue, const IRJson& newValue);
		void AddObjectCreateValue(InfinitRightObject* object, const IRJson& js_object);
		void AddObjectDeleteValue(InfinitRightObject* object, const IRJson& js_object);
	};

	class InfinitRightUndoActionStorage
	{
	public:
		InfinitRightUndoActionStorage(InfinitRightUndoAction* action);
		~InfinitRightUndoActionStorage();

		const IRVector<InfinitRightUndoValue*> GetUndoValues();
	private:
		IRVector<InfinitRightUndoValue*> 	fValues;
	};

}