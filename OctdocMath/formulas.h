#pragma once

#include <cmath>

namespace octdoc
{
	namespace mth
	{
		template<typename T>
		int Quadratic(T a, T b, T c, T& s1, T& s2)
		{
			T dis = b * b - 4 * a * c;
			if (dis < 0)
				return 0;
			if (dis == 0)
			{
				s1 = s2 = -b / (2 * a);
				return 1;
			}
			a = 0.5 / a;
			b *= a;
			dis = sqrt(dis) * a;
			s1 = -b - dis;
			s2 = -b + dis;
			return 2;
		}
	}
}