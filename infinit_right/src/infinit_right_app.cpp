#include "prefix.h"

#ifdef _DSWIN
#include <process.h> /* for getpid() */
#else
#include <unistd.h> /* for getpid() */
#endif
namespace IR {

	InfinitRightApp::InfinitRightApp()
		: fUserData(nullptr)
	{
		fActiveDrawing = nullptr;
		IR_INFO("Application PID: " + std::to_string(getpid()));
	}

	InfinitRightApp::~InfinitRightApp()
	{
		for (InfinitRightDrawing* drawing : fLoadedDrawings)
		{
			delete drawing;
		}
		fLoadedDrawings.clear();
		if (fUserData)
		{
			free(fUserData);
		}
	}

	void InfinitRightApp::Initialize()
	{
		fActiveDrawing = new InfinitRightDrawing("Drawing 1");
		IR_REGISTER_OBJECT(InfinitRightObject);
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
			function(info);
		}
		return info.fReturnValue;
	}

	void InfinitRightApp::RegisterObject(const IRString& type, const TObjectConstFn& fn)
	{
		IRMap<IRString, u32>::iterator typeIterator = fObjectTypeNameIdMap.find(type);
		if (typeIterator == fObjectTypeNameIdMap.end()) //We couldnt found the type key. Create new one
		{
			fObjectTypeNameIdMap[type] = fObjectTypes.size();
			fObjectTypes.push_back(fn);
		}
	}
	void InfinitRightApp::RegisterChangeCallbackFunction(const TCallbackFn& fn)
	{ 
		fRegisteredCallbackFunction = fn; 
	}

	void InfinitRightApp::StartChangeCallback(const IRJson& args)
	{
		if (fRegisteredCallbackFunction)
		{
			fRegisteredCallbackFunction(args);
		}
	}

	IRObjectId InfinitRightApp::GetObjectIdFromTypeName(const IRString& objectTypeName)
	{
		return fObjectTypeNameIdMap[objectTypeName];
	}

	InfinitRightObject* InfinitRightApp::new_object(u32 type, const IRUUID& uuid)
	{
        IR_ASSERT(type < gApp().fObjectTypes.size(), "Cant find create function for object type");
		const TObjectConstFn& fn = gApp().fObjectTypes[type];
		if (fn)
		{
			return fn(uuid);
		}
		IR_ERROR("Could not find object type :" + std::to_string(type));
		return nullptr;
	}
}
