#pragma once

namespace IR {

	class InfinitRightUndoAction
	{
	public:
		InfinitRightUndoAction(const IRString& name);
		~InfinitRightUndoAction();
	private:
		IRString							fName;
		IRVector<InfinitRightUndoValue*>	fValues;
	public:

	};

}