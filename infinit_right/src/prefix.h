#pragma once

#ifdef DS_WIN
#pragma comment(lib, "rpcrt4.lib")  // UuidCreate - Minimum supported OS Win 2000
#endif

//------------------------------------------------------------------------------------------------------
//DEFAULT INCLUDES


#include <algorithm>
#include <chrono>
#include <cmath>
#include <cstdio>
#include <functional>
#include <fstream>
#include <iostream>
#include <map>
#include <stack>
#include <set>
#include <string>
#include <vector>
#include <typeinfo>
#include <thread>
#include <mutex>
#include <atomic>
#include <deque>


//------------------------------------------------------------------------------------------------------
//DEPENDENCIES INCLUDE

#include "nlohmann/json.hpp"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#ifdef IR_NAN_SUPPORT
#include <node.h>
#include <nan.h>
#endif

//------------------------------------------------------------------------------------------------------
//Typedefs

namespace IR {
	class IRUUID;
	class InfinitRightObject;
	class InfinitRightApp;
}

typedef nlohmann::json	IRJson;

typedef int32_t			i32;
typedef uint8_t			u8;
typedef uint16_t		u16;
typedef uint32_t		u32;
typedef uint64_t		u64;
typedef unsigned char	byte;
typedef std::string		IRString;
typedef std::map<IR::IRUUID, IR::InfinitRightObject*> TObjectMap;
typedef u32 			IRObjectId;

template <typename T>
using IRVector = std::vector<T>;

template <typename T1, typename T2>
using IRMap = std::map<T1, T2>;

typedef std::function< IR::InfinitRightObject * (const IR::IRUUID& uuid) >	TObjectConstFn;
typedef std::function< void (const IRString& command, const IRJson& args) > TCallbackFn;


/////////////////////////////////////////BRIDGING

class IR_ModuleFunctionInfo
{
	friend class ::IR::InfinitRightApp;
public:
	const IRJson& input;
private:
	IRJson fReturnValue;
public:
	IR_ModuleFunctionInfo(const IRJson& _input)
		: input(_input)
	{
		fReturnValue = IRJson::object();
	}

	void SetReturnValue(const IRJson& returnValue)
	{
		fReturnValue = returnValue;
	}
};

typedef std::function < void(IR_ModuleFunctionInfo & input)>	TBridgeFn;

//------------------------------------------------------------------------------------------------------
//DEFINES
#define IR_EXPORT void infinit_right_register_bridge_function()
#define IR_REGISTER_METHOD(fn) ::IR::InfinitRightApp::gApp().RegisterBridgeFunction(#fn, fn)
#define IR_REGISTER_OBJECT(objClss) ::IR::InfinitRightApp::gApp().RegisterObject(#objClss, objClss::CreateNew )
#define IR_GET_OBJECT_TPYE(objClss) ::IR
#define IR_MODULE_FN(fn) void fn (IR_ModuleFunctionInfo& info)

#define IR_BEGIN_OBJECT(clss) class clss : public ::IR::InfinitRightObject {\
public:\
static clss* CreateNew(const ::IR::IRUUID uuid = ::IR::IRUUID().CreateNew()) { clss* result = new clss(uuid); result->fObjectType = ::IR::InfinitRightApp::gApp().GetObjectIdFromTypeName(#clss); return result; }
#define  IR_END_OBJECT };



#define IR_DEFINE_PROPERTY(name, type) private:\
IR::InfinitRightValueProperty<type> f##name;\
public:\
const type& Get##name() const { return f##name.GetValue(); }\
IR::InfinitRightValueProperty<type>* Get##name##Property() { return &f##name; }\
void Set##name(const type& value) { f##name.SetValue(value); }


#define IR_DEFINE_OBJ_PROPERTY(name) private:\
IR::InfinitRightObjectProperty f##name;\
public:\
IR::InfinitRightObject* Get##name() const { return f##name.GetValue(); }\
IR::InfinitRightObjectProperty* Get##name##Property() { return &f##name; }\
void Set##name(IR::InfinitRightObject* value) { f##name.SetValue(value); }

#define IR_INIT_PROPERTY(name) f##name(#name, this)
#define IR_INIT_PROPERTY_A1(name, initValue) f##name(#name, this, initValue)


/*const type& get_##name() const { return f_##name.GetValue(); }\
::IR::InfinitRightValueProperty<type>* get_##name##_property() const { return &f_##name; }\
void set_##name(const type& value) { f_##name->SetValue(value); }*/

//------------------------------------------------------------------------------------------------------
//intern includes
extern IR_EXPORT; //Function Header need to be somewhere. A implementation of this function is necessery

#include "infinit_right_logging.h"
#include "infinit_right_uuid.h"


#include "properties/_ir_properties_prefix.h"
#include "object/_ir_object_prefix.h"
#include "undo/_ir_undo_prefix.h"
#include "drawing/_lr_drawing_prefix.h"


#include "infinit_right_app.h"