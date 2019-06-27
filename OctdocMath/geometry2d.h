#pragma once

#include "linalg.h"

namespace octdoc
{
	namespace mth
	{
		class Point2D
		{
		public:
			double2 p;

		public:
			Point2D();
			Point2D(double2 point);
		};

		class Line2D
		{
		public:
			double2 p;
			double2 v;

		public:
			Line2D();
			Line2D(double2 point, double angle);
			Line2D(double2 point, double2 direction);
			static Line2D From2Points(double2 point1, double2 point2);

			inline double Angle() { return v.Angle(); }
			double2 Intersection(Line2D line);
		};

		class Circle2D
		{
		public:
			double2 c;
			double r;

		public:
			Circle2D();
			Circle2D(double2 centre, double radius);
			static Circle2D SameAngleCircle(double2 p1, double2 p2, double a);

			bool IsOnArea(double2 p);
			bool IsOnPerimeter(double2 p, double eps = EPS);
			double DistanceFromPerimeter(double2 p);
			int Intersection(Line2D line, double2 out[2]);
			int Intersection(Circle2D circle, double2 out[2]);
		};

		double2 Intersection2Lines(double2 p1, double2 v1, double2 p2, double2 v2);
		int Intersection2Circles(double2 c1, double r1, double2 c2, double r2, double2 out[2]);
		int IntersectionCircleLine(double2 p, double2 v, double2 c, double r, double2 out[2]);
		bool IsPointOnCircle(double2 p, double2 c, double r, double eps = EPS);
	}
}