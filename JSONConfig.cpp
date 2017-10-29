#include "JSONConfig.h"
#include "Parson\parson.h"


JSONConfig::JSONConfig()
{
}


JSONConfig::~JSONConfig()
{
}

float3 JSONConfig::GetFloat3(const char * name)
{
	JSON_Array* array = json_object_get_array(object, name);
	float set[3];
	for (int i = 0; i < 3; i++)
	{
		JSON_Value* value = json_array_get_value(array, i);

		set[i] = (float)json_value_get_number(value);
	}
	float3 ret;
	ret.x = set[0];
	ret.y = set[1];
	ret.z = set[2];

	return ret;
}

float2 JSONConfig::GetFloat2(const char * name)
{
	JSON_Array* array = json_object_get_array(object, name);
	float set[2];
	for (int i = 0; i < 2; i++)
	{
		JSON_Value* value = json_array_get_value(array, i);

		set[i] = (float)json_value_get_number(value);
	}
	float2 ret;
	ret.x = set[0];
	ret.y = set[1];

	return ret;
}

float JSONConfig::GetFloat(const char * name)
{
	JSON_Value* value = json_object_get_value(object, name);

	return (float)json_value_get_number(value);
}

int JSONConfig::GetInt(const char * name)
{
	JSON_Value* value = json_object_get_value(object, name);

	return (int)json_value_get_number(value);
}

bool JSONConfig::GetBool(const char * name)
{
	JSON_Value* value = json_object_get_value(object, name);

	return json_value_get_boolean(value);
}

Quat JSONConfig::GetQuaternion(const char * name)
{
	JSON_Array* array = json_object_get_array(object, name);
	float set[4];
	for (int i = 0; i < 4; i++)
	{
		JSON_Value* value = json_array_get_value(array, i);

		set[i] = (float)json_value_get_number(value);
	}
	Quat ret;

	ret.w = set[0];
	ret.x = set[1];
	ret.y = set[2];
	ret.z = set[3];

	return ret;
}

void JSONConfig::SetFloat3(float3 value, const char * name)
{
	JSON_Value* va = json_value_init_array();
	array = json_value_get_array(va);
	json_object_set_value(object, name, va);
	json_array_append_boolean(array, value.x);
	json_array_append_boolean(array, value.y);
	json_array_append_boolean(array, value.z);
}

void JSONConfig::SetFloat2(float2 value, const char * name)
{
	JSON_Value* va = json_value_init_array();
	array = json_value_get_array(va);
	json_object_set_value(object, name, va);
	json_array_append_boolean(array, value.x);
	json_array_append_boolean(array, value.y);
}

void JSONConfig::SetFloat(float value, const char * name)
{
	json_object_set_number(object, name, (float)value);
}

void JSONConfig::SetInt(int value, const char * name)
{
	json_object_set_number(object, name, value);
}
void JSONConfig::SetBool(bool value, const char * name)
{
	json_object_set_boolean(object, name, value);

}


void JSONConfig::SetQuaternion(Quat value, const char * name)
{
	
	JSON_Value* va = json_value_init_array();
	array = json_value_get_array(va);
	json_object_set_value(object, name, va);
	json_array_append_boolean(array, value.w);
	json_array_append_boolean(array, value.x);
	json_array_append_boolean(array, value.y);
	json_array_append_boolean(array, value.z);

}
