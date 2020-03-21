#include "prefix.h"

namespace IR {

	InfinitRightApp::InfinitRightApp()
	{
		fActiveDrawing = nullptr;
	}

	InfinitRightApp::~InfinitRightApp()
	{
		for (InfinitRightDrawing* drawing : fLoadedDrawings)
		{
			delete drawing;
		}
		fLoadedDrawings.clear();
	}

	void InfinitRightApp::Initialize()
	{

	}

	InfinitRightDrawing* InfinitRightApp::GetActiveDrawing()
	{
		return fActiveDrawing;
	}

	void InfinitRightApp::SetActiveDrawing(InfinitRightDrawing* drawing)
	{
		fActiveDrawing = drawing;
	}

	InfinitRightUndoManager& InfinitRightApp::GetUndoManager()
	{
		return fUndoManager;
	}

}