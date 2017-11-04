#pragma once
#include "Globals.h"
#include "MathGeoLib-1.5\src\Math\float4.h"

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
	void CleanUp();
	bool ParseFile(const char* name, const char* directory);
	bool SerializeFile(const char* name);
	int Serialize(char** buffer);
	JSONConfig SetFocus(const char* name);

	JSONConfig SetFocusArray(const char* name,uint index)const;

	float4 GetFloat4(const char* name)const;

	float3 GetFloat3(const char* name)const;
	float2 GetFloat2(const char* name)const;
	float GetFloat(const char* name)const;
	int GetInt(const char* name)const;
	bool GetBool(const char* name)const;
	const char* GetString(const char* name)const;
	Quat GetQuaternion(const char* name)const;
	uint GetArraySize(const char* name)const;

	//Set Functions
	void SetFloat4(float4 value, const char* name);

	void SetFloat3(float3 value, const char* name);
	void SetFloat2(float2 value, const char* name);
	void SetFloat(float value, const char* name);
	void SetInt(int value, const char* name);
	void SetBool(bool value, const char* name);
	void SetString(std::string value, const char* name);

	void OpenArray(const char* name);
	void CloseArray(const JSONConfig& child);

	void SetQuaternion(Quat value, const char* name);

	bool Save(const char* name, const char* path);
	//TODO Array floats for ModuleRender
private:
	JSON_Object* object = nullptr;
	JSON_Array* array = nullptr;
	JSON_Value* value = nullptr;


};

