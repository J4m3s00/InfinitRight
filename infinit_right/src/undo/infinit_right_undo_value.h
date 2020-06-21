#pragma once

namespace IR {

	class InfinitRightUndoValue
	{
	public:
		InfinitRightUndoValue(const IRUUID& objectUuid, const IRObjectId& objectId);
	protected:
		IRUUID				fObjectUuid;
		IRObjectId			fObjectId;
	public:
		virtual void Undo() = 0;
		virtual void Redo() = 0;

		virtual void WriteCallbackJson(IRJson& json) {};

		InfinitRightObject*		GetObject();
	};

}