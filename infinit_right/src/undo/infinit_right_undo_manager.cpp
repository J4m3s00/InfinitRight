#include "prefix.h"

namespace IR {

	InfinitRightUndoManager::InfinitRightUndoManager()
	{

	}

	InfinitRightUndoManager::~InfinitRightUndoManager()
	{

	}

	InfinitRightUndoAction* InfinitRightUndoManager::GetActiveAction()
	{
		return fActiveAction;
	}

	void InfinitRightUndoManager::SetActiveAction(InfinitRightUndoAction* action)
	{
		fActiveAction = action;
		IR_INFO("Start Undo: " + action->fName);
	}

	void InfinitRightUndoManager::DoUndo()
	{
		if (fPast.size() > 0)
		{
			InfinitRightUndoAction* action_to_undo = fPast.back();
			//Do the undo
			for (InfinitRightUndoValue* undoValue : action_to_undo->fValues)
			{
				undoValue->Undo();
			}
			//Remove action from past and push to future
			fPast.pop_back();
			fFuture.push_back(action_to_undo);
		}
	}

	void InfinitRightUndoManager::DoRedo()
	{
		if (fFuture.size() > 0)
		{
			InfinitRightUndoAction* action_to_undo = fFuture.back();
			//Do the undo
			for (size_t i = action_to_undo->fValues.size() - 1; i >= 0; i--)
			{
				InfinitRightUndoValue* undoValue = action_to_undo->fValues[i];
				undoValue->Redo();
			}
			//Remove action from past and push to future
			fPast.push_back(action_to_undo);
			fFuture.pop_back();
		}
	}

}