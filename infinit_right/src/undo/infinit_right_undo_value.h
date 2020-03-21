#pragma once

namespace IR {

	class InfinitRightUndoValue
	{
	public:
		InfinitRightUndoValue(const IRUUID& objectUuid);
	protected:
		IRUUID				fObjectUuid;

	public:
		virtual void Undo() = 0;
		virtual void Redo() = 0;

		InfinitRightObject*		GetObject();
	};

}