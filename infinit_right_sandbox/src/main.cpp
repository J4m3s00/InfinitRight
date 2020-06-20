#if 0
#include <string>

#include "gravity_compiler.h"
#include "gravity_core.h"
#include "gravity_vm.h"
#include "gravity_macros.h"
#include "gravity_vmmacros.h"
#include "gravity_opcodes.h"

void report_error (gravity_vm *vm, error_type_t error_type, const char *description, error_desc_t error_desc, void *xdata) {
        printf("%s\n", description);
        exit(0);
    }

bool my_function (gravity_vm *vm, gravity_value_t *args, uint16_t nargs, uint32_t rindex) {
        // do something useful here
		printf("My Func nargs: %d", nargs);
    
        gravity_object_t* obj = VALUE_AS_OBJECT(args[0]);

		gravity_string_t* str = VALUE_AS_STRING(args[1]);
		const char* c  = str->s;
		printf("%s\n", c);

		gravity_vm_setslot(vm, VALUE_FROM_CSTRING(vm, "THIS IS RESULT"), rindex);
		return true;
    }

	#define SOURCE "extern var MyClass;func main() {var foo = MyClass(); var res = foo.myfunc(\"Hello World\"); System.print(res);}"


int main()
{
	gravity_delegate_t delegate = {
        .error_callback = report_error
    };
    
    // setup compiler
    gravity_vm *vm = gravity_vm_new(&delegate);
    gravity_class_t *c = gravity_class_new_pair (vm, "MyClass", NULL, 0, 0);

    // Allocate and bind closures to the newly created class
    gravity_class_bind(c, "myfunc", NEW_CLOSURE_VALUE(my_function));

    // Register class inside VM
    gravity_vm_setvalue(vm, "MyClass", VALUE_FROM_OBJECT(c));

	gravity_compiler_t *compiler = gravity_compiler_create(&delegate);


    gravity_closure_t *closure = gravity_compiler_run(compiler, SOURCE, strlen(SOURCE), 0, true, true);
    
    // sanity check on compiled source
    if (!closure) {
        // an error occurred while compiling source code and it has already been reported by the report_error callback
        gravity_compiler_free(compiler);
        return 1;
    }

	gravity_vm_runmain(vm, closure);

	return 0;
}

#else
#include "prefix.h"

#include "objects/TestObject.h"

using namespace IR;

IR_MODULE_FN(IR_CreateNewObject)
{
	InfinitRightUndoAction undoAction("IR_CreateNewObject");
	const IRJson& stateObject = info.input;
	IRJson result = IRJson::object();

	u32 objectType;
	if (JS_CON::GetParamUintSafe("ObjectType", stateObject, objectType))
	{
		IRUUID parentUuid;
		JS_CON::GetParamUUIDSafe("ParentUuid", stateObject, parentUuid);
		InfinitRightObject* parentObject = InfinitRightApp::gApp().GetActiveDrawing()->GetObjectByUuid(parentUuid);


		InfinitRightObject* object = InfinitRightApp::gApp().GetActiveDrawing()->CreateNewObject(objectType, parentObject);

		object->SetJs(result);
	}


	info.SetReturnValue(result);
}

IR_MODULE_FN(IR_SetObject)
{
	InfinitRightUndoAction undoAction("IR_SetObject");
	const IRJson& stateObject = info.input;

	IRUUID objectUuid;
	if (JS_CON::GetParamUUIDSafe("Uuid", stateObject, objectUuid))
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
	if (JS_CON::GetParamUUIDSafe("Uuid", stateObject, objectUuid))
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
	if (JS_CON::GetParamUUIDSafe("Uuid", stateObject, objectUuid))
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

	IRJson result = InfinitRightApp::gApp().CallBridgeFunction("IR_CreateNewObject", createReq1);
	IR_ERROR("RESULT: " + result.dump());

	JS_CON::GetParamUUIDSafe("Uuid", result, firstUuid);

	IRJson createReq2 = IRJson::object();
	createReq2["ObjectType"] = "TestObject";
	createReq2["ParentUuid"] = JS_CON::ConvertValue(firstUuid);
	JS_CON::GetParamUUIDSafe("Uuid", InfinitRightApp::gApp().CallBridgeFunction("IR_CreateNewObject", createReq2), secondUuid);

	IRJson request1 = IRJson::object();
	request1["Uuid"] = JS_CON::ConvertValue(firstUuid);
	request1["Name"] = "First Object";


	IRJson request2 = IRJson::object();
	request2["Uuid"] = JS_CON::ConvertValue(secondUuid);
	request2["Name"] = "Second Object";
	request2["Number"] = JS_CON::ConvertValue(4);

	InfinitRightApp::gApp().CallBridgeFunction("IR_SetObject", request1);
	InfinitRightApp::gApp().CallBridgeFunction("IR_SetObject", request2);



	IRJson firstObject = InfinitRightApp::gApp().CallBridgeFunction("IR_GetObject", { { "Uuid", JS_CON::ConvertValue(firstUuid) } });
	IR_ERROR("PRINTING FIRST OBJECT!");
	IR_WARN(firstObject.dump());
	IR_ERROR("READY PRINTING FIRST OBJECT!");

	IRJson secondObject = InfinitRightApp::gApp().CallBridgeFunction("IR_GetObject", { { "Uuid", JS_CON::ConvertValue(secondUuid) } });
	IR_ERROR("PRINTING SECOND OBJECT!");
	IR_WARN(secondObject.dump());
	IR_ERROR("READY PRINTING SECOND OBJECT!");




	IRJson request3 = IRJson::object();
	request3["Uuid"] = JS_CON::ConvertValue(firstUuid);


	IRJson request4 = IRJson::object();
	request4["Uuid"] = JS_CON::ConvertValue(secondUuid);

	InfinitRightApp::gApp().CallBridgeFunction("IR_DeleteObject", request3);
	InfinitRightApp::gApp().CallBridgeFunction("IR_DeleteObject", request4);


	return 0;
}
#endif
