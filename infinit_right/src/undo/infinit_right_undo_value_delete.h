#pragma once

namespace IR {

	class InfinitRightUndoValueDelete : public InfinitRightUndoValue 
	{
	public:
		InfinitRightUndoValueDelete(const IRUUID& objectUuid, const IRJson& jsObject, const IRObjectId& objectId);
		~InfinitRightUndoValueDelete();
	private:
		IRJson		fJSObject;
	public:
		virtual void Undo();
		virtual void Redo();
		
		virtual void WriteCallbackJson(IRJson& json);
	};

}