#pragma once

#include "point2d.hpp"
#include "line2d.hpp"
#include "circle2d.hpp"

namespace octdoc
{
	namespace mth
	{
		using Point2Df = Point2D<float>;
		using Point2Dd = Point2D<double>;
		using Line2Df = Line2D<float>;
		using Line2Dd = Line2D<double>;
		using Circle2Df = Circle2D<float>;
		using Circle2Dd = Circle2D<double>;

		template <typename T>
		vec2<T> Intersection2Lines(vec2<T> p1, vec2<T> v1, vec2<T> p2, vec2<T> v2)
		{
			vec2<T> x1 = p1, x2 = p1 + v1, y1 = p2, y2 = p2 + v2;
			vec2<T> r;
			T f1, f2;
			f1 = (x1.x * x2.y - x1.y * x2.x) * (y1.x - y2.x) - (x1.x - x2.x) * (y1.x * y2.y - y1.y * y2.x);
			f2 = (x1.x - x2.x) * (y1.y - y2.y) - (y1.x - y2.x) * (x1.y - x2.y);
			f2 = 1 / f2;
			r.x = f1 * f2;
			f1 = (x1.x * x2.y - x1.y * x2.x) * (y1.y - y2.y) - (x1.y - x2.y) * (y1.x * x2.y - y1.y * y2.x);
			r.y = f1 * f2;
			return r;
		}

		template <typename T>
		int Intersection2Circles(vec2<T> c1, T r1, vec2<T> c2, T r2, vec2<T> out[2])
		{
			vec2<T> p = c2 - c1;
			T f = (p.x * p.x + p.y * p.y + r1 * r1 - r2 * r2) / (2 * p.y);
			T x1, x2;
			int ret = Quadratic((p.x * p.x) / (p.y * p.y) + 1.0f, -2.0f * f * p.x / p.y, f * f - r1 * r1, x1, x2);
			if (ret == 0)
				return 0;

			vec2<T> s1, s2;
			s1.x = x1;
			s1.y = sqrt(r1 * r1 - s1.x * s1.x);
			s2.x = s1.x;
			s2.y = -s1.x;
			out[0] = out[1] = c1 + ((fabs((s1 - p).LengthSquare() - r2 * r2) < fabs((s2 - p).LengthSquare() - r2 * r2)) ? s1 : s2);
			if (ret == 1)
				return 1;

			s1.x = x2;
			s1.y = sqrt(r1 * r1 - s1.x * s1.x);
			s2.x = s1.x;
			s2.y = -s1.y;
			out[1] = c1 + ((fabs((s1 - p).LengthSquare() - r2 * r2) < fabs((s2 - p).LengthSquare() - r2 * r2)) ? s1 : s2);
			return 2;
		}

		template <typename T>
		int IntersectionCircleLine(vec2<T> p, vec2<T> v, vec2<T> c, T r, vec2<T> out[2])
		{
			T sols[2];
			vec2<T> tmp = p - c;
			int ret = Quadratic(v.LengthSquare(), 2 * tmp.Dot(v), tmp.LengthSquare() - r * r, sols[0], sols[1]);
			if (ret == 0)
				return 0;
			out[0] = p + sols[0] * v;
			out[1] = p + sols[1] * v;
			return ret;
		}

		template <typename T>
		bool IsPointOnCircle(vec2<T> p, vec2<T> c, T r, T eps = EPS)
		{
			return fabs((p - c).LengthSquare() - r * r) < eps;
		}
	}
}