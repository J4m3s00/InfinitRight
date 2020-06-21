#pragma once

namespace IR {

	class InfinitRightUndoManager
	{
	public:
		InfinitRightUndoManager();
		~InfinitRightUndoManager();
		
		InfinitRightUndoAction* GetActiveAction();
		void 					StartUndo(InfinitRightUndoAction* action);
		void 					EndUndo(InfinitRightUndoAction* undoAction);


		void							DoUndo();
		void							DoRedo();
	private:

	private:
		IRVector<InfinitRightUndoActionStorage*>	fPast;
		IRVector<InfinitRightUndoActionStorage*>	fFuture;
		InfinitRightUndoAction*						fActiveAction;
	};

}