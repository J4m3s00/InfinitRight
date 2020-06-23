#define IR_NAN_SUPPORT
#include "prefix.h"
#include "objects/infinit_right_drawing_object.h"

using namespace IR;

IR_MODULE_FN(IR_GetSceneTree)
{
  InfinitRightUndoAction undoAction("IR_GetSceneTree");

  IRJson resultList = IRJson::array();
  InfinitRightDrawing* activeDrawing =InfinitRightApp::gApp().GetActiveDrawing();

  TObjectList objects = activeDrawing->GetObjects();
  for (InfinitRightObject* object : objects)
  {
    IRJson objectJs = IRJson::object();
    object->SetJs(objectJs);
    resultList.push_back(objectJs);
  }

  IRJson result = IRJson::object();
  result["Objects"] = resultList;
  info.SetReturnValue(result);
}

IR_MODULE_FN(IR_CreateNewObject)
{
	InfinitRightUndoAction undoAction("IR_CreateNewObject");
	const IRJson& stateObject = info.input;
	IRJson result = IRJson::object();

	u32 objectType = 0;
	JS_CON::GetParamUintSafe("ObjectType", stateObject, objectType);
  
  IRUUID parentUuid;
  JS_CON::GetParamUUIDSafe("ParentUuid", stateObject, parentUuid);
  InfinitRightObject* parentObject = InfinitRightApp::gApp().GetActiveDrawing()->GetObjectByUuid(parentUuid);

  InfinitRightObject* object = InfinitRightApp::gApp().GetActiveDrawing()->CreateNewObject(objectType, parentObject);
  object->FromJs(stateObject);

  object->SetJs(result);

	info.SetReturnValue(result);
}

IR_MODULE_FN(IR_SetObject)
{
  InfinitRightUndoAction undoAction("IR_SetObject");

  const IRJson& stateObject = info.input;

  IRUUID objectUuid;
  if (JS_CON::GetParamUUIDSafe("UUID", stateObject, objectUuid))
  {
    IRObjectId objectId = 0;
    JS_CON::GetParamUintSafe("ObjectType", stateObject, objectId);
    
    //TODO: Get the object by the object id. I need a map in the drawing for this though
    InfinitRightObject* object = InfinitRightApp::gApp().GetActiveDrawing()->GetObjectByUuid(objectUuid/*, objectId*/);
    if (object)
    {
      object->FromJs(stateObject);
    }
  }

}

IR_MODULE_FN(IR_DoUndo)
{
  InfinitRightUndoAction undoAction("IR_DoUndo", true);

  InfinitRightApp::gApp().GetUndoManager().DoUndo();
}


IR_MODULE_FN(IR_DoRedo)
{
  InfinitRightUndoAction undoAction("IR_DoRedo");

  InfinitRightApp::gApp().GetUndoManager().DoRedo();
}

IR_EXPORT 
{
  IR_REGISTER_OBJECT(InfinitRightDrawingObject);


  IR_REGISTER_METHOD(IR_CreateNewObject);
  IR_REGISTER_METHOD(IR_GetSceneTree);
  IR_REGISTER_METHOD(IR_SetObject);
  IR_REGISTER_METHOD(IR_DoUndo);
  IR_REGISTER_METHOD(IR_DoRedo);
}


#include <nan.h>
#include <v8.h>
struct GlobalData {
  bool connected = false;
  Nan::Callback ChangeCallback;
};


void CallCoreFn(const v8::FunctionCallbackInfo<v8::Value>& args) {
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

void RegisterCallbackFn(const v8::FunctionCallbackInfo<v8::Value>& info)
{
  IR::InfinitRightApp::gApp().UserData<GlobalData>()->ChangeCallback.Reset(info[0].As<v8::Function>());
  IR::InfinitRightApp::gApp().UserData<GlobalData>()->connected = true;
}

void Initialize(v8::Local<v8::Object> exports) {
  IR::InfinitRightApp::gApp().Initialize();
  IR::InfinitRightApp::gApp().SetUserData(new GlobalData());


  IR::InfinitRightApp::gApp().RegisterChangeCallbackFunction([](const IRJson& args) {
    GlobalData* data = IR::InfinitRightApp::gApp().UserData<GlobalData>();
    if (data->connected){
      v8::Local<v8::Value> argv[] = {JS_CON::GetV8FromJson(args)};
      Nan::Call(data->ChangeCallback, 1, argv);
    }
  });

  NODE_SET_METHOD(exports, "CallCoreFunction", CallCoreFn);
  NODE_SET_METHOD(exports, "RegisterCallbackFn", RegisterCallbackFn);
}

NODE_MODULE(InfinitRight, Initialize)
