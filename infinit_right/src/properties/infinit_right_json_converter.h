#pragma once

namespace IR {

	namespace JS_CON {

		bool HasObjectProperty(const IRString& paramName, const IRJson& js_object);
		bool HasObjectProperty(const char* paramName, const IRJson& js_object);
		i32 GetParamInt(const char* paramName, const IRJson& js_object);
		bool GetParamIntSafe(const char* paramName, const IRJson& js_object, i32& outValue);
		u32 GetParamUint(const char* paramName, const IRJson& js_object);
		bool GetParamUintSafe(const char* paramName, const IRJson& js_object, u32& outValue);
		float GetParamFloat(const char* paramName, const IRJson& js_object);
		bool GetParamFloatSafe(const char* paramName, const IRJson& js_object, float& outValue);
		double GetParamDouble(const char* paramName, const IRJson& js_object);
		bool GetParamDoubleSafe(const char* paramName, const IRJson& js_object, double& outValue);
		long GetParamLong(const char* paramName, const IRJson& js_object);
		bool GetParamLongSafe(const char* paramName, const IRJson& js_object, long& outValue);
		glm::vec2 GetParamVec2(const char* paramName, const IRJson& js_object);
		bool GetParamVec2Safe(const char* paramName, const IRJson& js_object, glm::vec2& outValue);
		glm::vec3 GetParamVec3(const char* paramName, const IRJson& js_object);
		bool GetParamVec3Safe(const char* paramName, const IRJson& js_object, glm::vec3& outValue);
		glm::vec4 GetParamVec4(const char* paramName, const IRJson& js_object);
		bool GetParamVec4Safe(const char* paramName, const IRJson& js_object, glm::vec4& outValue);
		glm::mat4 GetParamMat4(const char* paramName, const IRJson& js_object);
		bool GetParamMat4Safe(const char* paramName, const IRJson& js_object, glm::mat4& outValue);
		IRUUID GetParamUUID(const char* paramName, const IRJson& js_object);
		bool GetParamUUIDSafe(const char* paramName, const IRJson& js_object, IRUUID& outValue);
		IRString GetParamString(const char* paramName, const IRJson& js_object);
		bool GetParamStringSafe(const char* paramName, const IRJson& js_object, IRString& outValue);

		IRJson ConvertValue(int value);
		IRJson ConvertValue(int* value);
		IRJson ConvertValue(u32 value);
		IRJson ConvertValue(u32* value);
		IRJson ConvertValue(float value);
		IRJson ConvertValue(float* value);
		IRJson ConvertValue(double value);
		IRJson ConvertValue(double* value);
		IRJson ConvertValue(long value);
		IRJson ConvertValue(long* value);
		IRJson ConvertValue(const glm::vec2& value);
		IRJson ConvertValue(glm::vec2* value);
		IRJson ConvertValue(const glm::vec3& value);
		IRJson ConvertValue(glm::vec3* value);
		IRJson ConvertValue(const glm::vec4& value);
		IRJson ConvertValue(glm::vec4* value);
		IRJson ConvertValue(const glm::mat4& value);
		IRJson ConvertValue(glm::mat4* value);
		IRJson ConvertValue(const IRString& value);
		IRJson ConvertValue(IRString* value);
		IRJson ConvertValue(const IRUUID& value);
		IRJson ConvertValue(IRUUID* value);


		void ConvertObject(const IRJson& ref, int& value);
		void ConvertObject(const IRJson& ref, int* value);
		void ConvertObject(const IRJson& ref, u32& value);
		void ConvertObject(const IRJson& ref, u32* value);
		void ConvertObject(const IRJson& ref, float& value);
		void ConvertObject(const IRJson& ref, float* value);
		void ConvertObject(const IRJson& ref, double& value);
		void ConvertObject(const IRJson& ref, double* value);
		void ConvertObject(const IRJson& ref, long& value);
		void ConvertObject(const IRJson& ref, long* value);
		void ConvertObject(const IRJson& ref, glm::vec2& value);
		void ConvertObject(const IRJson& ref, glm::vec2* value);
		void ConvertObject(const IRJson& ref, glm::vec3& value);
		void ConvertObject(const IRJson& ref, glm::vec3* value);
		void ConvertObject(const IRJson& ref, glm::vec4& value);
		void ConvertObject(const IRJson& ref, glm::vec4* value);
		void ConvertObject(const IRJson& ref, glm::mat4& value);
		void ConvertObject(const IRJson& ref, glm::mat4* value);
		void ConvertObject(const IRJson& ref, IRString& value);
		void ConvertObject(const IRJson& ref, IRString* value);
		void ConvertObject(const IRJson& ref, IRUUID& value);
		void ConvertObject(const IRJson& ref, IRUUID* value);


		template <typename T>
		IRJson ConvertValue(const IRVector<T>& value)
		{
			IRJson result = IRJson::array();
			for (const T& v : value)
			{
				result.push_back(ConvertValue(v));
			}
			return result;
		}

		template <typename T>
		IRJson ConvertValue(const IRVector<T>* value)
		{
			IRJson result = IRJson::array();
			for (const T& v : value)
			{
				result.push_back(ConvertValue(v));
			}
			return result;
		}

		template <typename T>
		void ConvertObject(const IRJson& ref, IRVector<T>& outValues)
		{
			if (!ref.is_array()) { IR_WARN("Could not convert IRJson to IRVector. IRJson is not a array: \n" + ref.dump()); return; }
			outValues.clear();
			outValues.resize(ref.size());
			int index = 0;
			for (const IRJson& js : ref)
			{
				ConvertObject(js, &outValues[index++]);
			}
		}

		template <typename T>
		void ConvertObject(const IRJson& ref, IRVector<T>* outValues)
		{
			if (!ref.is_array()) { IR_WARN("Could not convert IRJson to IRVector. IRJson is not a array: \n" + ref.dump()); return; }
			outValues->clear();
			outValues->resize(ref.size());
			int index = 0;
			for (const IRJson& js : ref)
			{
				ConvertObject(js, &outValues[index++]);
			}
		}


		
#ifdef IR_NAN_SUPPORT
        IRJson                  GetJsonFromV8(v8::Local<v8::Value> v8_value);
        v8::Local<v8::Value>    GetV8FromJson(const IRJson& json_value);
#else
		const IRJson&           GetJsonFromV8(const IRJson& json_value);
#endif
	}

}