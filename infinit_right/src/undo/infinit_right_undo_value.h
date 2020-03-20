#pragma once

namespace IR {

	class InfinitRightUndoValue
	{
	public:
		InfinitRightUndoValue(const IRUUID& objectUuid);
	protected:
		IRUUID				fObjectUuid;

	public:
		InfinitRightObject*		GetObject();
	};

}