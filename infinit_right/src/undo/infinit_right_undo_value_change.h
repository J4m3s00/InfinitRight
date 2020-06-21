#pragma once

namespace IR {
	
	class InfinitRightUndoValueChange : public InfinitRightUndoValue
	{
	public:
		InfinitRightUndoValueChange(const IRUUID& objectUuid, const IRJson& oldValue, const IRJson& newValue, const IRObjectId& objectId);
		~InfinitRightUndoValueChange();
	private:
		IRJson		fOldValue;
		IRJson		fNewValue;
	public:
		virtual void Undo();
		virtual void Redo();
		
		virtual void WriteCallbackJson(IRJson& json);
	};

}