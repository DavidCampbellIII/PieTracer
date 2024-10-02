#pragma once

struct Utilities
{
public:
    static float Clamp01(const float value)
    {
        if (value < 0)
        {
            return 0;
        }
        
        if (value > 1)
        {
            return 1;
        }
        return value;
    }

	static float DegreesToRadians(const float degrees)
	{
		return degrees * PI / 180.f;
	}
};