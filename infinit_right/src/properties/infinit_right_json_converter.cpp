#include "prefix.h"

namespace IR { namespace JS_CON {


		bool HasObjectProperty(const IRString& paramName, const IRJson& js_object)
		{
			return js_object.find(paramName) != js_object.end();
		}

		bool HasObjectProperty(const char* paramName, const IRJson& js_object)
		{
			return js_object.find(paramName) != js_object.end();
		}


		i32 GetParamInt(const char* paramName, const IRJson& js_object)
		{
			int result = 0;
			const IRJson& jsParam = js_object[paramName];
			if (!jsParam.is_number_integer()) { IR_WARN("Javascript value is not an Integer!"); IR_WARN("Object: " + jsParam.dump()); return 0; }
			result = jsParam.get<int>();
			return result;
		}

		bool GetParamIntSafe(const char* paramName, const IRJson& js_object, i32& outValue)
		{
			if (!HasObjectProperty(paramName, js_object))
			{
				outValue = 0;
				return false;
			}
			outValue = GetParamInt(paramName, js_object);
			return true;
		}

		u32 GetParamUint(const char* paramName, const IRJson& js_object)
		{
			int result = 0;
			const IRJson& jsParam = js_object[paramName];
			if (!jsParam.is_number_unsigned()) { IR_WARN("Javascript value is not an Unsigned Integer!"); IR_WARN("Object: " + jsParam.dump()); return 0; }
			result = jsParam.get<int>();
			return result;
		}

		bool GetParamUintSafe(const char* paramName, const IRJson& js_object, u32& outValue)
		{
			if (!HasObjectProperty(paramName, js_object))
			{
				outValue = 0;
				return false;
			}
			outValue = GetParamUint(paramName, js_object);
			return true;
		}

		float GetParamFloat(const char* paramName, const IRJson& js_object)
		{
			float result = 0;
			const IRJson& jsParam = js_object[paramName];
			if (!jsParam.is_number_float()) { IR_WARN("Javascript value is not a Float!"); IR_WARN("Object: " + jsParam.dump()); return 0.0; }
			result = jsParam.get<float>();
			return result;
		}

		bool GetParamFloatSafe(const char* paramName, const IRJson& js_object, float& outValue)
		{
			if (!HasObjectProperty(paramName, js_object))
			{
				outValue = 0.0;
				return false;
			}
			outValue = GetParamFloat(paramName, js_object);
			return true;
		}

		double GetParamDouble(const char* paramName, const IRJson& js_object)
		{
			double result = 0;
			const IRJson& jsParam = js_object[paramName];
			if (!jsParam.is_number()) { IR_WARN("Javascript value is not a Number!"); IR_WARN("Object: " + jsParam.dump()); return 0.0; }
			result = jsParam.get<double>();
			return result;
		}

		bool GetParamDoubleSafe(const char* paramName, const IRJson& js_object, double& outValue)
		{
			if (!HasObjectProperty(paramName, js_object))
			{
				outValue = 0.0;
				return false;
			}
			outValue = GetParamDouble(paramName, js_object);
			return true;
		}


		long GetParamLong(const char* paramName, const IRJson& js_object)
		{
			long result = 0;
			const IRJson& jsParam = js_object[paramName];
			if (!jsParam.is_number()) { IR_WARN("Javascript value is not a Number!"); IR_WARN("Object: " + jsParam.dump()); return 0; }
			result = jsParam.get<long>();
			return result;
		}

		bool GetParamLongSafe(const char* paramName, const IRJson& js_object, long& outValue)
		{
			if (!HasObjectProperty(paramName, js_object))
			{
				outValue = 0;
				return false;
			}
			outValue = GetParamLong(paramName, js_object);
			return true;
		}

		glm::vec2 GetParamVec2(const char* paramName, const IRJson& js_object)
		{
			glm::vec2 result(0.0f);
			const IRJson& jsParam = js_object[paramName];
			if (!jsParam.is_object()) { IR_WARN("IRJson vec2 is not an IRJsonObject!"); IR_WARN("Object: " + jsParam.dump()); return result; }
			GetParamFloatSafe("X", jsParam, result.x);
			GetParamFloatSafe("Y", jsParam, result.y);
			return result;
		}

		bool GetParamVec2Safe(const char* paramName, const IRJson& js_object, glm::vec2& outValue)
		{
			if (!HasObjectProperty(paramName, js_object))
			{
				outValue = glm::vec2();
				return false;
			}
			outValue = GetParamVec2(paramName, js_object);
			return true;
		}

		glm::vec3 GetParamVec3(const char* paramName, const IRJson& js_object)
		{
			glm::vec3 result(0.0f);
			const IRJson& jsParam = js_object[paramName];
			if (!jsParam.is_object()) { IR_WARN("IRJson vec3 is not an IRJsonObject!"); IR_WARN("Object: " + jsParam.dump()); return result; }
			GetParamFloatSafe("X", jsParam, result.x);
			GetParamFloatSafe("Y", jsParam, result.y);
			GetParamFloatSafe("Z", jsParam, result.z);
			return result;
		}

		bool GetParamVec3Safe(const char* paramName, const IRJson& js_object, glm::vec3& outValue)
		{
			if (!HasObjectProperty(paramName, js_object))
			{
				outValue = glm::vec3();
				return false;
			}
			outValue = GetParamVec3(paramName, js_object);
			return true;
		}

		glm::vec4 GetParamVec4(const char* paramName, const IRJson& js_object)
		{
			glm::vec4 result(0.0f);
			const IRJson& jsParam = js_object[paramName];
			if (!jsParam.is_object()) { IR_WARN("IRJson vec4 is not an IRJsonObject!"); IR_WARN("Object: " + jsParam.dump()); return result; }
			GetParamFloatSafe("X", jsParam, result.x);
			GetParamFloatSafe("Y", jsParam, result.y);
			GetParamFloatSafe("Z", jsParam, result.z);
			return result;
		}

		bool GetParamVec4Safe(const char* paramName, const IRJson& js_object, glm::vec4& outValue)
		{
			if (!HasObjectProperty(paramName, js_object))
			{
				outValue = glm::vec4();
				return false;
			}
			outValue = GetParamVec4(paramName, js_object);
			return true;
		}

		glm::mat4 GetParamMat4(const char* paramName, const IRJson& js_object)
		{
			const IRJson& jsParam = js_object[paramName];
			if (!jsParam.is_array()) { IR_WARN("IRJson mat4 is not an IRJsonArray!"); IR_WARN("Object: " + jsParam.dump()); return glm::mat4(1.0); }

			return glm::mat4(jsParam[0].get<float>(), jsParam[1].get<float>(), jsParam[2].get<float>(), jsParam[3].get<float>(),
				jsParam[4].get<float>(), jsParam[5].get<float>(), jsParam[6].get<float>(), jsParam[7].get<float>(),
				jsParam[8].get<float>(), jsParam[9].get<float>(), jsParam[10].get<float>(), jsParam[11].get<float>(),
				jsParam[12].get<float>(), jsParam[13].get<float>(), jsParam[14].get<float>(), jsParam[15].get<float>());
		}

		bool GetParamMat4Safe(const char* paramName, const IRJson& js_object, glm::mat4& outValue)
		{
			if (!HasObjectProperty(paramName, js_object))
			{
				outValue = glm::mat4();
				return false;
			}
			outValue = GetParamMat4(paramName, js_object);
			return true;
		}

		IRUUID GetParamUUID(const char* paramName, const IRJson& js_object)
		{
			const IRJson& jsParam = js_object[paramName];
			if (!jsParam.is_string()) { IR_WARN("IRJson IRUUID is not an IRJsonIRString!"); IR_WARN("Object: " + jsParam.dump()); return IRUUID(); }

			IRString uuiString = GetParamString(paramName, js_object);
			IRUUID result;
			result.FromString(uuiString);
			return result;
		}

		bool GetParamUUIDSafe(const char* paramName, const IRJson& js_object, IRUUID& outValue)
		{
			if (!HasObjectProperty(paramName, js_object))
			{
				outValue = IRUUID();
				return false;
			}
			outValue = GetParamUUID(paramName, js_object);
			return true;
		}

		IRString GetParamString(const char* paramName, const IRJson& js_object)
		{
			const IRJson& jsParam = js_object[paramName];
			if (!jsParam.is_string()) { IR_WARN("IRJson IRUUID is not an IRJsonIRString!"); IR_WARN("Object: " + jsParam.dump()); return ""; }

			IRString result = js_object[paramName].get<IRString>();
			return result;
		}

		bool GetParamStringSafe(const char* paramName, const IRJson& js_object, IRString& outValue)
		{
			if (!HasObjectProperty(paramName, js_object))
			{
				outValue = "";
				return false;
			}
			outValue = GetParamString(paramName, js_object);
			return true;
		}

		IRJson ConvertValue(int value)
		{
			return value;
		}

		IRJson ConvertValue(int* value)
		{
			return *value;
		}

		IRJson ConvertValue(u32 value)
		{
			return value;
		}

		IRJson ConvertValue(u32* value)
		{
			return *value;
		}

		IRJson ConvertValue(float value)
		{
			return value;
		}

		IRJson ConvertValue(float* value)
		{
			return *value;
		}

		IRJson ConvertValue(double value)
		{
			return value;
		}

		IRJson ConvertValue(double* value)
		{
			return *value;
		}

		IRJson ConvertValue(long value)
		{
			return value;
		}

		IRJson ConvertValue(long* value)
		{
			return *value;
		}

		IRJson ConvertValue(const glm::vec2& value)
		{
			IRJson result = IRJson::object();

			result["X"] = value.x;
			result["Y"] = value.y;

			return result;
		}

		IRJson ConvertValue(glm::vec2* value)
		{
			IRJson result = IRJson::object();

			result["X"] = value->x;
			result["Y"] = value->y;

			return result;
		}

		IRJson ConvertValue(const glm::vec3& value)
		{
			IRJson result = IRJson::object();

			result["X"] = value.x;
			result["Y"] = value.y;
			result["Z"] = value.z;

			return result;
		}

		IRJson ConvertValue(glm::vec3* value)
		{
			IRJson result = IRJson::object();

			result["X"] = value->x;
			result["Y"] = value->y;
			result["Z"] = value->z;

			return result;
		}

		IRJson ConvertValue(const glm::vec4& value)
		{
			IRJson result = IRJson::object();

			result["X"] = value.x;
			result["Y"] = value.y;
			result["Z"] = value.z;
			result["W"] = value.w;

			return result;
		}

		IRJson ConvertValue(glm::vec4* value)
		{
			IRJson result = IRJson::object();

			result["X"] = value->x;
			result["Y"] = value->y;
			result["Z"] = value->z;
			result["W"] = value->w;

			return result;
		}


		IRJson ConvertValue(const glm::mat4& value)
		{
			IRJson result = IRJson::array();

			for (int i = 0; i < 4 * 4; i++) {
				result.push_back(ConvertValue(value[i]));
			}

			return result;
		}

		IRJson ConvertValue(glm::mat4* value)
		{
			IRJson result = IRJson::array();

			for (int i = 0; i < 4 * 4; i++) {
				result.push_back(ConvertValue(value[i]));
			}

			return result;
		}

		IRJson ConvertValue(const IRString& value)
		{
			return value;
		}

		IRJson ConvertValue(IRString* value)
		{
			return *value;
		}

		IRJson ConvertValue(const IRUUID& value)
		{
			return value.ToString();
		}

		IRJson ConvertValue(IRUUID* value)
		{
			return value->ToString();
		}

		void ConvertObject(const IRJson& ref, int& value)
		{
			IR_ASSERT(ref.is_number(), "IRJson value " + ref.dump() + " is not a number!");
			if (ref.is_number()) { value = ref.get<int>(); }
		}

		void ConvertObject(const IRJson& ref, int* value)
		{
			IR_ASSERT(ref.is_number(), "IRJson value " + ref.dump() + " is not a number!");
			if (ref.is_number()) { *value = ref.get<int>(); }
		}

		void ConvertObject(const IRJson& ref, u32& value)
		{
			IR_ASSERT(ref.is_number(), "IRJson value " + ref.dump() + " is not a number!");
			if (ref.is_number()) { value = ref.get<u32>(); }
		}

		void ConvertObject(const IRJson& ref, u32* value)
		{
			IR_ASSERT(ref.is_number(), "IRJson value " + ref.dump() + " is not a number!");
			if (ref.is_number()) { *value = ref.get<u32>(); }
		}

		void ConvertObject(const IRJson& ref, float& value)
		{
			IR_ASSERT(ref.is_number(), "IRJson value " + ref.dump() + " is not a number!");
			if (ref.is_number()) { value = ref.get<float>(); }
		}

		void ConvertObject(const IRJson& ref, float* value)
		{
			IR_ASSERT(ref.is_number(), "IRJson value " + ref.dump() + " is not a number!");
			if (ref.is_number()) { *value = ref.get<float>(); }
		}

		void ConvertObject(const IRJson& ref, double& value)
		{
			IR_ASSERT(ref.is_number(), "IRJson value " + ref.dump() + " is not a number!");
			if (ref.is_number()) { value = ref.get<double>(); }
		}

		void ConvertObject(const IRJson& ref, double* value)
		{
			IR_ASSERT(ref.is_number(), "IRJson value " + ref.dump() + " is not a number!");
			if (ref.is_number()) { *value = ref.get<double>(); }
		}

		void ConvertObject(const IRJson& ref, long& value)
		{
			IR_ASSERT(ref.is_number(), "IRJson value " + ref.dump() + " is not a number!");
			if (ref.is_number()) { value = ref.get<long>(); }
		}

		void ConvertObject(const IRJson& ref, long* value)
		{
			IR_ASSERT(ref.is_number(), "IRJson value " + ref.dump() + " is not a number!");
			if (ref.is_number()) { *value = ref.get<long>(); }
		}

		void ConvertObject(const IRJson& ref, glm::vec2& value)
		{
			IR_ASSERT(ref.is_object(), "IRJson value " + ref.dump() + " is not a Object!");
			if (ref.is_object())
			{
				GetParamFloatSafe("X", ref, value.x);
				GetParamFloatSafe("Y", ref, value.y);
			}
		}

		void ConvertObject(const IRJson& ref, glm::vec2* value)
		{
			IR_ASSERT(ref.is_object(), "IRJson value " + ref.dump() + " is not a Object!");
			if (ref.is_object())
			{
				GetParamFloatSafe("X", ref, value->x);
				GetParamFloatSafe("Y", ref, value->y);
			}
		}

		void ConvertObject(const IRJson& ref, glm::vec3& value)
		{
			IR_ASSERT(ref.is_object(), "IRJson value  {0}   is not a Object!");
			if (ref.is_object())
			{
				GetParamFloatSafe("X", ref, value.x);
				GetParamFloatSafe("Y", ref, value.y);
				GetParamFloatSafe("Z", ref, value.z);
			}
		}

		void ConvertObject(const IRJson& ref, glm::vec3* value)
		{
			IR_ASSERT(ref.is_object(), "IRJson value  {0}   is not a Object!");
			if (ref.is_object())
			{
				GetParamFloatSafe("X", ref, value->x);
				GetParamFloatSafe("Y", ref, value->y);
				GetParamFloatSafe("Z", ref, value->z);
			}
		}

		void ConvertObject(const IRJson& ref, glm::vec4& value)
		{
			IR_ASSERT(ref.is_object(), "IRJson value  {0}   is not a Object!");
			if (ref.is_object())
			{
				GetParamFloatSafe("X", ref, value.x);
				GetParamFloatSafe("Y", ref, value.y);
				GetParamFloatSafe("Z", ref, value.z);
				GetParamFloatSafe("W", ref, value.w);
			}
		}

		void ConvertObject(const IRJson& ref, glm::vec4* value)
		{
			IR_ASSERT(ref.is_object(), "IRJson value " + ref.dump() + " is not a Object!");
			if (ref.is_object())
			{
				GetParamFloatSafe("X", ref, value->x);
				GetParamFloatSafe("Y", ref, value->y);
				GetParamFloatSafe("Z", ref, value->z);
				GetParamFloatSafe("W", ref, value->w);
			}
		}

		void ConvertObject(const IRJson& ref, glm::mat4& value)
		{
			IR_ASSERT(ref.is_array(), "IRJson value " + ref.dump() + " is not a Matrix!");
			if (ref.is_array())
			{
				value = glm::mat4(ref[0].get<float>(), ref[1].get<float>(), ref[2].get<float>(), ref[3].get<float>(),
					ref[4].get<float>(), ref[5].get<float>(), ref[6].get<float>(), ref[7].get<float>(),
					ref[8].get<float>(), ref[9].get<float>(), ref[10].get<float>(), ref[11].get<float>(),
					ref[12].get<float>(), ref[13].get<float>(), ref[14].get<float>(), ref[15].get<float>());
			}
		}

		void ConvertObject(const IRJson& ref, glm::mat4* value)
		{
			IR_ASSERT(ref.is_array(), "IRJson value " + ref.dump() + " is not a Matrix!");
			if (ref.is_array())
			{
				*value = glm::mat4(ref[0].get<float>(), ref[1].get<float>(), ref[2].get<float>(), ref[3].get<float>(),
					ref[4].get<float>(), ref[5].get<float>(), ref[6].get<float>(), ref[7].get<float>(),
					ref[8].get<float>(), ref[9].get<float>(), ref[10].get<float>(), ref[11].get<float>(),
					ref[12].get<float>(), ref[13].get<float>(), ref[14].get<float>(), ref[15].get<float>());
			}
		}

		void ConvertObject(const IRJson& ref, IRString& value)
		{
			IR_ASSERT(ref.is_string(), "IRJson value " + ref.dump() + " is not a IRString!");
			if (ref.is_string())
			{
				value = ref.get<IRString>();
			}
		}

		void ConvertObject(const IRJson& ref, IRString* value)
		{
			IR_ASSERT(ref.is_string(), "IRJson value " + ref.dump() + " is not a IRString!");
			if (ref.is_string())
			{
				*value = ref.get<IRString>();
			}
		}

		void ConvertObject(const IRJson& ref, IRUUID& value)
		{
			IR_ASSERT(ref.is_string(), "IRJson value " + ref.dump() + " is not a IRString!");
			if (ref.is_string())
			{
				IRString uuidIRString = ref.get<IRString>();
				(value).FromString(uuidIRString);
			}
		}

		void ConvertObject(const IRJson& ref, IRUUID* value)
		{
			IR_ASSERT(ref.is_string(), "IRJson value " + ref.dump() + " is not a IRString!");
			if (ref.is_string())
			{
				IRString uuidIRString = ref.get<IRString>();
				(*value).FromString(uuidIRString);
			}
		}


#ifdef IR_NAN_SUPPORT
        IRJson GetJsonFromV8(v8::Local<v8::Value> v8_value)
        {
            IRJson retVal = IRJson::object();
            IR_ASSERT(! v8_value->IsNullOrUndefined(), "V8 Value is undefined");
            if ( ! v8_value->IsNullOrUndefined()) 
            {
                Nan::JSON __json;
                v8::MaybeLocal<v8::String> v8_str = __json.Stringify(v8_value.As<v8::Object>());

                IR_ASSERT(! v8_str.IsEmpty(), "v8 string is empty");
                if( ! v8_str.IsEmpty())
                {
                    std::string json = *Nan::Utf8String(v8_str.ToLocalChecked());
                    retVal = IRJson::parse(json);
                }
            }            
            return retVal;
        }

        v8::Local<v8::Value> GetV8FromJson(const IRJson& json_value)
        {
            std::string str = json_value.dump();

            if(json_value.is_null()) 
            { 
                return Nan::Undefined(); 
            }
           
            Nan::JSON __json;
            v8::MaybeLocal<v8::Value> maybe = __json.Parse(Nan::New<v8::String>(str).ToLocalChecked());

            IR_ASSERT( ! maybe.IsEmpty(), "Value is empty");
            if(maybe.IsEmpty())
            {
                return Nan::New<v8::Object>();
            }
            
            v8::Local<v8::Value> out = maybe.ToLocalChecked();
            return out;
        }		

#else
		const IRJson& GetJsonFromV8(const IRJson& json_value)
		{
			return json_value;
		}

#endif
} }