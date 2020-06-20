#include "prefix.h"

using namespace IR;

IR_MODULE_FN(IR_CreateNewObject)
{
	InfinitRightUndoAction undoAction("IR_CreateNewObject");
	const IRJson& stateObject = info.input;
	IRJson result = IRJson::object();

	IRString objectType;
	JS_CON::GetParamStringSafe("ObjectType", stateObject, objectType);
  
  IRUUID parentUuid;
  JS_CON::GetParamUUIDSafe("ParentUuid", stateObject, parentUuid);
  InfinitRightObject* parentObject = InfinitRightApp::gApp().GetActiveDrawing()->GetObjectByUuid(parentUuid);

  if (objectType.empty())
  {
   objectType = "InfinitRightObject"; 
  }
  InfinitRightObject* object = InfinitRightApp::gApp().GetActiveDrawing()->CreateNewObject(objectType, parentObject);

  object->SetJs(result);

	info.SetReturnValue(result);
}

IR_EXPORT 
{
  IR_REGISTER_METHOD(IR_CreateNewObject);
}








void CallCoreFn(const v8::FunctionCallbackInfo<v8::Value>& args) {
    std::cout << "Call core" << std::endl;
    if (args[0]->IsObject())
    {
        IRJson stateObject = IR::JS_CON::GetJsonFromV8(args[0].As<v8::Object>());
        IRString commandString;
        if (IR::JS_CON::GetParamStringSafe("Command", stateObject, commandString))
        {
            IRJson input = IRJson::object();
            if (IR::JS_CON::HasObjectProperty("Args", stateObject) && !stateObject["Args"].is_null())
            {
                input = stateObject["Args"];
            }
            IRJson result = IR::InfinitRightApp::gApp().CallBridgeFunction(commandString, input);
            args.GetReturnValue().Set(IR::JS_CON::GetV8FromJson(result));
        }
    }
}

void Initialize(v8::Local<v8::Object> exports) {
  IR::InfinitRightApp::gApp().Initialize();

  NODE_SET_METHOD(exports, "CallCoreFunction", CallCoreFn);
}

NODE_MODULE(InfinitRight, Initialize)
