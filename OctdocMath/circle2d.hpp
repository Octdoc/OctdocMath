#pragma once

#include "linalg.hpp"

namespace octdoc
{
	namespace mth
	{
		template <typename T>
		class Circle2D
		{
		public:
			vec2<T> c;
			T r;

		public:
			Circle2D() :c(), r(0) {}
			Circle2D(vec2<T> centre, T radius) : c(centre), r(radius) {}
			static Circle2D SameAngleCircle(vec2<T> p1, vec2<T> p2, T a)
			{
				vec2<T> pm = (p1 + p2) * 0.5;
				T angle = PI * 0.5 + atan((p2.y - p1.y) / (p2.x - p1.x));
				vec2<T> d0(cos(angle), sin(angle));
				vec2<T> d1(cos(angle + a), sin(angle + a));
				vec2<T> c = Intersection2Lines(pm, d0, p1, d1);
				return Circle2D(c, (c - p1).Length());
			}

			bool IsOnArea(vec2<T> p)
			{
				return (c - p).LengthSquare() <= r * r;
			}
			bool IsOnPerimeter(vec2<T> p, T eps = EPS)
			{
				return IsPointOnCircle(p, c, r, eps);
			}
			double DistanceFromPerimeter(vec2<T> p)
			{
				return fabs((c - p).Length() - r);
			}
			int Intersection(Line2D line, vec2<T> out[2])
			{
				return IntersectionCircleLine(line.p, line.v, c, r, out);
			}
			int Intersection(Circle2D circle, vec2<T> out[2])
			{
				return Intersection2Circles(c, r, circle.c, circle.r, out);
			}
		};
	}
}