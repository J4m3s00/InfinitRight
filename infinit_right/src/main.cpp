#include "prefix.h"

using namespace IR;

int main()
{
	InfinitRightDrawing drawing("TestDrawing");

	IRUUID firstUuid;
	IRUUID secondUuid;

	{
		InfinitRightUndoAction undoAction("Test_CreateObjects");
		firstUuid = drawing.CreateNewObject(new InfinitRightObject())->GetUuid();
		secondUuid = drawing.CreateNewObject(new InfinitRightObject())->GetUuid();
	}

	{
		InfinitRightUndoAction undoAction("Test_SetNames");
		InfinitRightObject* firstObject = drawing.GetObjectByUuid(firstUuid);
		if (firstObject)
		{
			firstObject->SetName("First Object");
		}

		InfinitRightObject* secondObject = drawing.GetObjectByUuid(secondUuid);
		if (secondObject)
		{
			secondObject->SetName("Second Object");
		}
	}

	{
		InfinitRightUndoAction undoAction("Test_Delete Objects");
		drawing.DeleteObject(firstUuid);
		drawing.DeleteObject(secondUuid);
	}

	return 0;
}