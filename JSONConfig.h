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
	~JSONConfig();

	void AddFloat3(float3 value, const char* name);
	void AddFloat2(float2 value, const char* name);
	void AddFloat(float value, const char* name);
	void AddBool(bool value, const char* name);

	void AddQuaternion(Quat value, const char* name);

private:
	JSON_Object* object = nullptr;
	JSON_Array* array = nullptr;
	JSON_Value* value = nullptr;


};

