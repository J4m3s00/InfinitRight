#pragma once
#pragma comment(lib, "rpcrt4.lib")  // UuidCreate - Minimum supported OS Win 2000

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

//------------------------------------------------------------------------------------------------------
//Typedefs

namespace IR {
	class IRUUID;
	class InfinitRightObject;
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

template <typename T>
using IRVector = std::vector<T>;



#include "infinit_right_logging.h"
#include "infinit_right_uuid.h"


#include "properties/_ir_properties_prefix.h"
#include "object/_ir_object_prefix.h"
#include "undo/_ir_undo_prefix.h"
#include "drawing/_lr_drawing_prefix.h"


#include "infinit_right_app.h"