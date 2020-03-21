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
		void AddObjectChangeValue(const IRUUID& objectUuid, const IRJson& oldValue, const IRJson& newValue);
		void AddObjectCreateValue(const IRUUID& objectUuid, const IRJson& object);
		void AddObjectDeleteValue(const IRUUID& objectUuid, const IRJson& object);
	};

}