#pragma once

namespace IR {

	class InfinitRightUndoValueDelete : public InfinitRightUndoValue 
	{
	public:
		InfinitRightUndoValueDelete(const IRUUID& objectUuid, const IRJson& jsObject);
		~InfinitRightUndoValueDelete();
	private:
		IRJson		fJSObject;
	public:
		virtual void Undo();
		virtual void Redo();
		virtual void RunCallbacks() {}
	};

}