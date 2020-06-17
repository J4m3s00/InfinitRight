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
		infinit_right_register_bridge_function();
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

	void InfinitRightApp::RegisterBridgeFunction(const IRString& name, const TBridgeFn& bridgeFn)
	{
		fBridgeFns[name] = bridgeFn;
	}

	IRJson InfinitRightApp::CallBridgeFunction(const IRString& name, const IRJson& input)
	{
		const TBridgeFn& function = fBridgeFns[name];
		IR_ModuleFunctionInfo info = IR_ModuleFunctionInfo( input );
		if (function)
		{
			IR_INFO("call " + name);
			function(info);
		}
		return info.fReturnValue;
	}

	void InfinitRightApp::RegisterObject(const IRString& type, const TObjectConstFn& fn)
	{
		fObjectTypes[type] = fn;
	}

	InfinitRightObject* InfinitRightApp::new_object(const IRString& type, const IRUUID& uuid)
	{
		const TObjectConstFn& fn = gApp().fObjectTypes[type];
		if (fn)
		{
			return fn(uuid);
		}
		IR_ERROR("Could not find object type :" + type);
		return nullptr;
	}
}