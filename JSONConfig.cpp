#include "JSONConfig.h"
#include "Parson\parson.h"


JSONConfig::JSONConfig()
{
	value = json_value_init_object();
	object = json_value_get_object(value);
}

JSONConfig::JSONConfig(JSON_Object * object):object(object)
{
}


JSONConfig::~JSONConfig()
{
	//json_value_free(value);
}

void JSONConfig::CleanUp()
{
	json_value_free(value);
}

bool JSONConfig::ParseFile(const char * name)
{
	bool ret = true;
	value = json_parse_file(name);
	if (value == nullptr)
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

int JSONConfig::Serialize(char ** buffer)
{
	*(buffer)=json_serialize_to_string_pretty(json_value_deep_copy(value));

	return strlen(*(buffer));
}

JSONConfig JSONConfig::SetFocus(const char * name)
{
	return json_object_dotget_object(object, name);
}

JSONConfig JSONConfig::SetFocusArray(const char * name, uint index)
{
	JSONConfig ret=nullptr;
	JSON_Array* array = json_object_get_array(object, name);
	if (array != nullptr)
	{
		ret.object = json_array_get_object(array, index);
	}
	return ret;
}

float3 JSONConfig::GetFloat3(const char * name)const
{
	JSON_Array* array = json_object_get_array(object, name);
	float3 ret;
	ret.x = (float)json_value_get_number(json_array_get_value(array, 0));
	ret.y = (float)json_value_get_number(json_array_get_value(array, 1));
	ret.z = (float)json_value_get_number(json_array_get_value(array, 2));

	return ret;
}

float2 JSONConfig::GetFloat2(const char * name)const
{
	JSON_Array* array = json_object_get_array(object, name);
	float2 ret;
	ret.x = (float)json_value_get_number(json_array_get_value(array, 0));
	ret.y = (float)json_value_get_number(json_array_get_value(array, 1));

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
	Quat ret;
	ret.w = (float)json_value_get_number(json_array_get_value(array, 0));
	ret.x = (float)json_value_get_number(json_array_get_value(array, 1));
	ret.y = (float)json_value_get_number(json_array_get_value(array, 2));
	ret.z = (float)json_value_get_number(json_array_get_value(array, 3));

	return ret;
}

uint JSONConfig::GetArraySize(const char * name) const
{
	return json_array_get_count(array);
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
		json_array_append_value(array, json_value_deep_copy(child.value));
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
	json_array_append_number(array, value.w);
	json_array_append_number(array, value.x);
	json_array_append_number(array, value.y);
	json_array_append_number(array, value.z);

}
