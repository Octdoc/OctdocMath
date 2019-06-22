#include "formulas.h"
#include <cmath>

int octdoc::mth::Quadratic(float a, float b, float c, float& s1, float& s2)
{
	float dis = b * b - 4.0f * a * c;
	if (dis < 0.0f)
		return 0;
	if (dis == 0.0f)
	{
		s1 = s2 = -b / (2.0f * a);
		return 1;
	}
	a = 0.5f / a;
	b *= a;
	dis = sqrtf(dis) * a;
	s1 = b + dis;
	s2 = b - dis;
	return 2;
}
