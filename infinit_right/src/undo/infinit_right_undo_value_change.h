#pragma once

namespace IR {
	
	class InfinitRightUndoValueChange : public InfinitRightUndoValue
	{
	public:
		InfinitRightUndoValueChange(const IRUUID& objectUuid, const IRJson& oldValue, const IRJson& newValue);
		~InfinitRightUndoValueChange();
	private:
		IRJson		fOldValue;
		IRJson		fNewValue;
	public:
		virtual void Undo();
		virtual void Redo();
		virtual void RunCallbacks() {}
	};

}