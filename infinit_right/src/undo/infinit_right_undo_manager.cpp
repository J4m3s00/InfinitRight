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

	void InfinitRightUndoManager::StartUndo(InfinitRightUndoAction* action)
	{
		fActiveAction = action;
		IR_INFO("Start Undo: " + action->GetName());
	}

	void InfinitRightUndoManager::EndUndo(InfinitRightUndoAction* action)
	{
		IR_INFO("End Undo " + action->GetName());
		fActiveAction = nullptr;

		if (action->GetUndoValueList().empty()) { return; }

		if (action->IsUndoAction()) { IR_INFO("Add to future " + action->GetName()); fFuture.push_back(new InfinitRightUndoActionStorage(action));}
		else { IR_INFO("Add to past " + action->GetName()); fPast.push_back(new InfinitRightUndoActionStorage(action));}
	}

	void InfinitRightUndoManager::DoUndo()
	{
		IR_INFO("DO UNDO: ");
		if (fPast.size() > 0)
		{
			InfinitRightUndoActionStorage* action_to_undo = fPast.back();
			//Do the undo
			for (InfinitRightUndoValue* undoValue : action_to_undo->GetUndoValues())
			{
				undoValue->Undo();
			}
			//Remove action from past and push to future
			fPast.pop_back();
		}
	}

	void InfinitRightUndoManager::DoRedo()
	{
		if (fFuture.size() > 0)
		{
			InfinitRightUndoActionStorage* action_to_undo = fFuture.back();
			const IRVector<InfinitRightUndoValue*>& valueList = action_to_undo->GetUndoValues();
			//Do the undo
			for (i32 i = (i32)valueList.size() - 1; i >= 0; i--)
			{
				InfinitRightUndoValue* undoValue = valueList[i];
				undoValue->Undo();
			}
			//Remove action from past and push to future

        fFuture.pop_back();
		}
	}

}
