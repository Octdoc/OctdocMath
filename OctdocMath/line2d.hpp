#pragma once

#include "linalg.hpp"

namespace octdoc
{
	namespace mth
	{
		template <typename T>
		class Line2D
		{
		public:
			vec2<T> p;
			vec2<T> v;

		public:
			Line2D() :p(), v() {}
			Line2D(vec2<T> point, T angle) : p(point), v(cos(angle), sin(angle)) {}
			Line2D(vec2<T> point, vec2<T> direction) : p(point), v(direction) {}
			static Line2D From2Points(vec2<T> point1, vec2<T> point2)
			{
				return Line2D(point1, point2 - point1);
			}

			inline T Angle() { return v.Angle(); }
			vec2<T> Intersection(Line2D line)
			{
				return Intersection2Lines(p, v, line.p, line.v);
			}
		};
	}
}