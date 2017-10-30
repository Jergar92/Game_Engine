#include "JSONConfig.h"
#include "Parson\parson.h"


JSONConfig::JSONConfig()
{
}

JSONConfig::JSONConfig(JSON_Object * object):object(object)
{
}


JSONConfig::~JSONConfig()
{
	json_value_free((JSON_Value *)value);
}

bool JSONConfig::ParseFile(const char * name)
{
	bool ret = true;
	value = json_parse_file("config.json");
	if (value == NULL)
	{
		ret = false;
	}
	object = json_value_get_object(value);

	return ret;
}

bool JSONConfig::SerializeFile(const char * name)
{
	return json_serialize_to_file(value, name)== JSONSuccess;
	
}

JSONConfig JSONConfig::GetFocus(const char * name)
{
	return json_object_dotget_object(object, name);
}

float3 JSONConfig::GetFloat3(const char * name)const
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

float2 JSONConfig::GetFloat2(const char * name)const
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

float JSONConfig::GetFloat(const char * name)const
{
	JSON_Value* value = json_object_get_value(object, name);

	return (float)json_value_get_number(value);
}

int JSONConfig::GetInt(const char * name)const
{
	JSON_Value* value = json_object_get_value(object, name);

	return (int)json_value_get_number(value);
}

bool JSONConfig::GetBool(const char * name)const
{
	JSON_Value* value = json_object_get_value(object, name);

	return json_value_get_boolean(value);
}

const char * JSONConfig::GetString(const char * name)const
{
	JSON_Value* value = json_object_get_value(object, name);

	return json_value_get_string(value);
}

Quat JSONConfig::GetQuaternion(const char * name)const
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
	json_array_append_number(array, value.x);
	json_array_append_number(array, value.y);
	json_array_append_number(array, value.z);
}

void JSONConfig::SetFloat2(float2 value, const char * name)
{
	JSON_Value* va = json_value_init_array();
	array = json_value_get_array(va);
	json_object_set_value(object, name, va);
	json_array_append_number(array, value.x);
	json_array_append_number(array, value.y);
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

void JSONConfig::SetString(std::string value, const char * name)
{
	json_object_set_string(object, name, value.c_str());

}

void JSONConfig::OpenArray(const char * name)
{
	JSON_Value* new_array = json_value_init_array();
	array = json_value_get_array(new_array);
	json_object_set_value(object, name, new_array);
}

void JSONConfig::CloseArray(const JSONConfig & child)
{
	if (array != nullptr)
	{
		json_array_append_value(array, child.value);
	}
	else
	{
		LOG("Array nullptr, open Array");
	}
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
