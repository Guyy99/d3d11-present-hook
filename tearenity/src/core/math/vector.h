#pragma once

struct vec2
{
	float x, y;
};

struct vec3
{
	float x, y, z;

	vec3 operator-(vec3 other)
	{
		return vec3{ this->x - other.x, this->y - other.y, this->z - other.z };
	}

	float Dot(vec3 other)
	{
		return this->x * other.x + this->y * other.y + this->z * other.z;
	}

};

struct color
{
	float r, g, b, a;
};
