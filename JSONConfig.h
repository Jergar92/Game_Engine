#pragma once
#include "Globals.h"
#include "MathGeoLib-1.5\src\Math\float3.h"
#include "MathGeoLib-1.5\src\Math\float2.h"
#include "MathGeoLib-1.5\src\Math\Quat.h"
struct json_object_t;
struct json_array_t;
struct json_value_t;

typedef struct json_object_t JSON_Object;
typedef struct json_array_t JSON_Array;
typedef struct json_value_t  JSON_Value;

class JSONConfig
{
public:
	JSONConfig();
	JSONConfig(JSON_Object * object);

	~JSONConfig();

	bool ParseFile(const char* name);
	JSONConfig GetFocus(const char* name);
	float3 GetFloat3(const char* name);
	float2 GetFloat2(const char* name);
	float GetFloat(const char* name);
	int GetInt(const char* name);
	bool GetBool(const char* name);
	Quat GetQuaternion(const char* name);
	
	//Set Functions
	void SetFloat3(float3 value, const char* name);
	void SetFloat2(float2 value, const char* name);
	void SetFloat(float value, const char* name);
	void SetInt(int value, const char* name);
	void SetBool(bool value, const char* name);
	void SetQuaternion(Quat value, const char* name);
	//TODO Array floats for ModuleRender
private:
	JSON_Object* object = nullptr;
	JSON_Array* array = nullptr;
	JSON_Value* value = nullptr;


};

