
#pragma once

struct Color
{
	float vec4[4] = { 0,0,0,0 };
	
	Color() : vec4 { 0,0,0,0 }
	{}

	Color(float r, float g, float b, float a = 1.0f) : vec4{ r,g,b,a }
	{}

	void Set(float r, float g, float b, float a = 1.0f)
	{
		vec4[0] = r;
		vec4[1] = g;
		vec4[2] = b;
		vec4[3] = a;
	}

	float* operator & ()
	{
		return (float*)this;
	}
};

extern Color Red;
extern Color Green;
extern Color Blue;
extern Color Black;
extern Color White;