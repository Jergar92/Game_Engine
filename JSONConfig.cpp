#include "JSONConfig.h"
#include "Parson\parson.h"


JSONConfig::JSONConfig()
{
}


JSONConfig::~JSONConfig()
{
}

void JSONConfig::AddFloat3(float3 value, const char * name)
{
	JSON_Value* va = json_value_init_array();
	array = json_value_get_array(va);
	json_object_set_value(object, name, va);
	json_array_append_boolean(array, value.x);
	json_array_append_boolean(array, value.y);
	json_array_append_boolean(array, value.z);
}

void JSONConfig::AddFloat2(float2 value, const char * name)
{
	JSON_Value* va = json_value_init_array();
	array = json_value_get_array(va);
	json_object_set_value(object, name, va);
	json_array_append_boolean(array, value.x);
	json_array_append_boolean(array, value.y);
}

void JSONConfig::AddFloat(float value, const char * name)
{
	json_object_set_number(object, name, (float)value);
}

void JSONConfig::AddBool(bool value, const char * name)
{
	json_object_set_boolean(object, name, value);

}

void JSONConfig::AddQuaternion(Quat value, const char * name)
{
	
	JSON_Value* va = json_value_init_array();
	array = json_value_get_array(va);
	json_object_set_value(object, name, va);
	json_array_append_boolean(array, value.w);
	json_array_append_boolean(array, value.x);
	json_array_append_boolean(array, value.y);
	json_array_append_boolean(array, value.z);

}
