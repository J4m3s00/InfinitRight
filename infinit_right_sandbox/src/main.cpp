#include "prefix.h"

#include "objects/TestObject.h"

using namespace IR;

IR_MODULE_FN(IR_CreateNewObject)
{
	InfinitRightUndoAction undoAction("IR_CreateNewObject");
	const IRJson& stateObject = info.input;
	IRJson result = IRJson::object();

	IRString objectType;
	if (JS_CON::GetParamStringSafe("ObjectType", stateObject, objectType))
	{
		
		InfinitRightObject* object = InfinitRightApp::gApp().GetActiveDrawing()->CreateNewObject(InfinitRightApp::new_object(objectType));

		object->SetJs(result);
	}


	info.SetReturnValue(result);
}

IR_MODULE_FN(IR_SetObject)
{
	InfinitRightUndoAction undoAction("IR_SetObject");
	const IRJson& stateObject = info.input;

	IRUUID objectUuid;
	if (JS_CON::GetParamUUIDSafe("UUID", stateObject, objectUuid))
	{
		InfinitRightObject* object = InfinitRightApp::gApp().GetActiveDrawing()->GetObjectByUuid(objectUuid);
		if (object)
		{
			object->FromJs(stateObject);
		}
	}
}

IR_MODULE_FN(IR_GetObject)
{
	const IRJson& stateObject = info.input;
	IRJson result = IRJson::object();

	IRUUID objectUuid;
	if (JS_CON::GetParamUUIDSafe("UUID", stateObject, objectUuid))
	{
		InfinitRightObject* object = InfinitRightApp::gApp().GetActiveDrawing()->GetObjectByUuid(objectUuid);
		if (object)
		{
			object->SetJs(result);
		}
	}

	info.SetReturnValue(result);
}

IR_MODULE_FN(IR_DeleteObject)
{
	InfinitRightUndoAction undoAction("IR_DeleteObject");
	const IRJson& stateObject = info.input;

	IRUUID objectUuid;
	if (JS_CON::GetParamUUIDSafe("UUID", stateObject, objectUuid))
	{
		InfinitRightApp::gApp().GetActiveDrawing()->DeleteObject(objectUuid);
	}
}

IR_EXPORT
{
	IR_REGISTER_OBJECT(TestObject);

	IR_REGISTER_METHOD(IR_CreateNewObject); 
	IR_REGISTER_METHOD(IR_SetObject);
	IR_REGISTER_METHOD(IR_DeleteObject);
	IR_REGISTER_METHOD(IR_GetObject);
}



int main()
{
	////////////////////////////////ALWAYS FIRST//////////////////////////////
	InfinitRightApp::gApp().Initialize();
	///////////////////////////////////////////////////////////////////////////
	InfinitRightDrawing* drawing = new InfinitRightDrawing("TestDrawing");
	InfinitRightApp::gApp().SetActiveDrawing(drawing);

	IRUUID firstUuid;
	IRUUID secondUuid;

	IRJson createReq1 = IRJson::object();
	createReq1["ObjectType"] = "TestObject";

	IRJson createReq2 = IRJson::object();
	createReq2["ObjectType"] = "TestObject";

	JS_CON::ConvertObject(InfinitRightApp::gApp().CallBridgeFunction("IR_CreateNewObject", createReq1)["UUID"], firstUuid);
	JS_CON::ConvertObject(InfinitRightApp::gApp().CallBridgeFunction("IR_CreateNewObject", createReq2)["UUID"], secondUuid);

	IRJson request1 = IRJson::object();
	request1["UUID"] = JS_CON::ConvertValue(firstUuid);
	request1["Name"] = "First Object";


	IRJson request2 = IRJson::object();
	request2["UUID"] = JS_CON::ConvertValue(secondUuid);
	request2["Name"] = "Second Object";

	InfinitRightApp::gApp().CallBridgeFunction("IR_SetObject", request1);
	InfinitRightApp::gApp().CallBridgeFunction("IR_SetObject", request2);



	IRJson firstObject = InfinitRightApp::gApp().CallBridgeFunction("IR_GetObject", { { "UUID", JS_CON::ConvertValue(firstUuid) } });
	IR_ERROR("PRINTING FIRST OBJECT!");
	IR_WARN(firstObject.dump());
	IR_ERROR("READY PRINTING FIRST OBJECT!");

	IRJson secondObject = InfinitRightApp::gApp().CallBridgeFunction("IR_GetObject", { { "UUID", JS_CON::ConvertValue(firstUuid) } });
	IR_ERROR("PRINTING SECOND OBJECT!");
	IR_WARN(secondObject.dump());
	IR_ERROR("READY PRINTING SECOND OBJECT!");




	IRJson request3 = IRJson::object();
	request3["UUID"] = JS_CON::ConvertValue(firstUuid);


	IRJson request4 = IRJson::object();
	request4["UUID"] = JS_CON::ConvertValue(secondUuid);

	InfinitRightApp::gApp().CallBridgeFunction("IR_DeleteObject", request3);
	InfinitRightApp::gApp().CallBridgeFunction("IR_DeleteObject", request4);


	return 0;
}