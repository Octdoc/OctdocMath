#include "geometry2d.h"
#include "formulas.h"

namespace octdoc
{
	namespace mth
	{
		Point2D::Point2D() :p() {}
		Point2D::Point2D(float2 point) : p(point) {}

		Line2D::Line2D() : p(), v() {}
		Line2D::Line2D(float2 point, float angle) : p(point), v(cosf(angle), sinf(angle)) {}
		Line2D::Line2D(float2 point, float2 direction) : p(point), v(direction) {}
		Line2D Line2D::From2Points(float2 point1, float2 point2)
		{
			return Line2D(point1, point2 - point1);
		}
		float2 Line2D::Intersection(Line2D line)
		{
			return Intersection2Lines(p, v, line.p, line.v);
		}

		Circle2D::Circle2D() :c(), r(0.0f) {}
		Circle2D::Circle2D(float2 centre, float radius) : c(centre), r(radius) {}
		Circle2D Circle2D::SameAngleCircle(float2 p1, float2 p2, float a)
		{
			float2 pm = (p1 + p2) * 0.5f;
			float angle = PI * 0.5f + atanf((p2.y - p1.y) / (p2.x - p1.x));
			float2 d0(cosf(angle), sinf(angle));
			float2 d1(cosf(angle + a), sinf(angle + a));
			float2 c = Intersection2Lines(pm, d0, p1, d1);
			return Circle2D(c, (c - p1).Length());
		}
		bool Circle2D::IsOnArea(float2 p)
		{
			return (c - p).LengthSquare() <= r * r;
		}
		bool Circle2D::IsOnPerimeter(float2 p, float eps)
		{
			return IsPointOnCircle(p, c, r, eps);
		}
		float Circle2D::DistanceFromPerimeter(float2 p)
		{
			return fabsf((c - p).Length() - r);
		}
		int Circle2D::Intersection(Line2D line, float2 out[2])
		{
			return IntersectionCircleLine(line.p, line.v, c, r, out);
		}
		int Circle2D::Intersection(Circle2D circle, float2 out[2])
		{
			return Intersection2Circles(c, r, circle.c, circle.r, out);
		}

		float2 Intersection2Lines(float2 p1, float2 v1, float2 p2, float2 v2)
		{
			float2 x1 = p1, x2 = p1 + v1, y1 = p2, y2 = p2 + v2;
			float2 r;
			float f1, f2;
			f1 = (x1.x * x2.y - x1.y * x2.x) * (y1.x - y2.x) - (x1.x - x2.x) * (y1.x * y2.y - y1.y * y2.x);
			f2 = (x1.x - x2.x) * (y1.y - y2.y) - (y1.x - y2.x) * (x1.y - x2.y);
			f2 = 1.0f / f2;
			r.x = f1 * f2;
			f1 = (x1.x * x2.y - x1.y * x2.x) * (y1.y - y2.y) - (x1.y - x2.y) * (y1.x * x2.y - y1.y * y2.x);
			r.y = f1 * f2;
			return r;
		}
		int Intersection2Circles(float2 c1, float r1, float2 c2, float r2, float2 out[2])
		{
			float2 p = c2 - c1;
			float f = (p.x * p.x + p.y * p.y + r1 * r1 - r2 * r2) / (2.0f * p.y);
			float x1, x2;
			int ret = Quadratic((p.x * p.x) / (p.y * p.y) + 1.0f, -2.0f * f * p.x / p.y, f * f - r1 * r1, x1, x2);
			if (ret == 0)
				return 0;

			float2 s1, s2;
			s1.x = x1;
			s1.y = sqrtf(r1 * r1 - s1.x * s1.x);
			s2.x = s1.x;
			s2.y = -s1.x;
			out[0] = out[1] = c1 + ((fabsf((s1 - p).LengthSquare() - r2 * r2) < fabsf((s2 - p).LengthSquare() - r2 * r2)) ? s1 : s2);
			if (ret == 1)
				return 1;

			s1.x = x2;
			s1.y = sqrtf(r1 * r1 - s1.x * s1.x);
			s2.x = s1.x;
			s2.y = -s1.y;
			out[1] = c1 + ((fabsf((s1 - p).LengthSquare() - r2 * r2) < fabsf((s2 - p).LengthSquare() - r2 * r2)) ? s1 : s2);
			return 2;
		}
		int IntersectionCircleLine(float2 p, float2 v, float2 c, float r, float2 out[2])
		{
			float sols[2];
			float2 tmp = p - c;
			int ret = Quadratic(v.LengthSquare(), 2.0f * tmp.Dot(v), tmp.LengthSquare() - r * r, sols[0], sols[1]);
			if (ret == 0)
				return 0;
			out[0] = p + sols[0] * v;
			out[1] = p + sols[1] * v;
			return ret;
		}
		bool IsPointOnCircle(float2 p, float2 c, float r, float eps)
		{
			return fabsf((p - c).LengthSquare() - r * r) < eps;
		}
	}
}