#pragma once

#include "position.h"

namespace octdoc
{
	namespace mth
	{
		class Point3D
		{
		public:
			double3 p;

		public:
			Point3D();
			Point3D(double3 point);

			double Distance(double3 point);
			double DistanceSquare(double3 point);
			double TimeToGetClose(double3 position, double3 direction, double distance);
		};

		class Line3D
		{
		public:
			double3 p;
			double3 v;

		public:
			Line3D();
			Line3D(double3 point, double3 direction);

			double Distance(double3 point);
			double DistanceSquare(double3 point);
			double TimeToGetClose(double3 position, double3 direction, double distance);
		};

		class Plain3D
		{
		public:
			double3 n;
			double d;

		public:
			Plain3D();
			Plain3D(double3 normal, double distance);

			bool IsPointOn(double3 point, double eps = EPS);
			bool IsPointBelow(double3 point);
			bool IsPointOver(double3 point);
			double Distance(double3 point);
			double DirectionalDistance(Position<double>& ray);
			// return: how many raydirs are necessary to reach the plain
			double DirectionalDistance(double3 raypos, double3 raydir);
			double TimeToGetClose(double3 position, double3 direction, double distance);
		};

		class Triangle3D
		{
			Plain3D m_plain;
			double3 m_vertices[3];

		public:
			Triangle3D();
			Triangle3D(double3 tri[3]);
			Triangle3D(double3 v1, double3 v2, double3 v3);
			Triangle3D(double3 tri[3], double3 plainNormal, double plainDistance);

			bool IsPointOver(double3 point);
			bool IsPointOn(double3 point, double eps = EPS);

			inline Plain3D& getPlain() { return m_plain; }
			inline double3 getPlainNormal() { return m_plain.n; }
			inline double getPlainDistance() { return m_plain.d; }
			inline double3* getVertices(unsigned index) { return m_vertices; }
			inline double3 getVertex(unsigned index) { return m_vertices[index]; }
		};

		bool IsPointOverTriangle(double3 tri[3], double3 point);

		double DistanceLinePoint(double3 linePoint, double3 lineDirection, double3 point);
		double DistanceSquareLinePoint(double3 linePoint, double3 lineDirection, double3 point);

		// Points on the lines that are closest to the other line
		void MinDistancePoints2Lines(double3 p1, double3 v1, double3 p2, double3 v2, double3& out1, double3& out2);

		double3 LMSLineIntersection(Line3D lines[], int count);
		double3 LMSLineIntersection(double3 linePoints[], double3 lineDirections[], int count);
	}
}