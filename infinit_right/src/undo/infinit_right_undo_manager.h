#pragma once

namespace IR {

	class InfinitRightUndoManager
	{
		friend class InfinitRightUndoAction;
	public:
		InfinitRightUndoManager();
		~InfinitRightUndoManager();
		
		InfinitRightUndoAction* GetActiveAction();


		void							DoUndo();
		void							DoRedo();
	private:
		void SetActiveAction(InfinitRightUndoAction* action);

	private:
		IRVector<InfinitRightUndoAction*>	fPast;
		IRVector<InfinitRightUndoAction*>	fFuture;
		InfinitRightUndoAction*				fActiveAction;
	};

}