#pragma once

namespace MuSeoun
{
	struct vec2
	{
		float x;
		float y;

		vec2(int x_, int y_)
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
}
