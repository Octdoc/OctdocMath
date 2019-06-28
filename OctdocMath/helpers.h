#pragma once

#include <cmath>
#include <iostream>

namespace octdoc
{
	namespace mth
	{
		constexpr double PI = 3.1415926535897932;
		constexpr double EPS = 1e-6;

		template <typename T>
		class vec2;

		template <typename T>
		class vec3;

		template <typename T>
		class vec4;

		template <typename T>
		class mat2x2;

		template <typename T>
		class mat3x3;

		template <typename T>
		class mat4x4;

		template <typename T>
		bool isNear(T a, T b, T eps = EPS)
		{
			return fabs(a - b) < eps;
		}
	}
}