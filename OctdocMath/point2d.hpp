#pragma once

#include "linalg.hpp"

namespace octdoc
{
	namespace mth
	{
		template <typename T>
		class Point2D
		{
		public:
			vec2<T> p;

		public:
			Point2D() :p() {}
			Point2D(vec2<T> point) :p(point) {}
		};
	}
}