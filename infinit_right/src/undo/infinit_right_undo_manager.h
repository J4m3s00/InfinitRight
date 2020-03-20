#pragma once

namespace IR {

	class InfinitRightUndoManager
	{
	public:
		InfinitRightUndoManager();
		~InfinitRightUndoManager();
	private:
		IRVector<InfinitRightUndoAction*> fPast;
		IRVector<InfinitRightUndoAction*> fFuture;
	};

}