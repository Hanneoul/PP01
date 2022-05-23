#pragma once

namespace MuSeoun
{
	struct vec2
	{
		float x;
		float y;

		vec2()
		{
			x = 0;
			y = 0;
		}
		vec2(float x_, float y_)
		{
			x = x_;
			y = y_;
		}
	};
	vec2 operator+(vec2 a, vec2 b)
	{
		vec2 result(a.x + b.x, a.y + b.y);
		return result;
	}


	struct vec3
	{
		float x;
		float y;
		float z;

		vec3()
		{
			x = 0;
			y = 0;
			z = 0;
		}
		vec3(float x_, float y_, float z_)
		{
			x = x_;
			y = y_;
			z = z_;
		}
	};

}
