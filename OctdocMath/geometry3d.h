#pragma once

#include "position.h"

namespace octdoc
{
	namespace mth
	{
		class Point3D
		{
			double3 m_point;

		public:
			Point3D();
			Point3D(double3 point);

			inline double3 getPoint() { return m_point; }
			inline void setPoint(double3 point) { m_point = point; }

			double Distance(double3 point);
			double DistanceSquare(double3 point);
			double TimeToGetClose(double3 position, double3 direction, double distance);
		};

		class Line3D
		{
			double3 m_point;
			double3 m_direction;

		public:
			Line3D();
			Line3D(double3 point, double3 unitDirection);

			static Line3D From2Points(double3 p1, double3 p2) { return Line3D(p1, (p2 - p1).Normalized()); }

			inline double3 getPoint() { return m_point; }
			inline void setPoint(double3 point) { m_point = point; }
			inline double3 getDirection() { return m_direction; }
			inline void setDirection(double3 unitDirection) { m_direction = unitDirection; }

			double Distance(double3 point);
			double DistanceSquare(double3 point);
			double TimeToGetClose(double3 position, double3 direction, double distance);
		};

		class Plain3D
		{
			double3 m_normal;
			double m_distance;

		public:
			Plain3D();
			Plain3D(double3 unitNormal, double distance);

			inline double3 getNormal() { return m_normal; }
			inline void setNormal(double3 unitNormal) { m_normal = unitNormal; }
			inline double getDistance() { return m_distance; }
			inline void setDistance(double distance) { m_distance = distance; }

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
			inline double3 getPlainNormal() { return m_plain.getNormal(); }
			inline double getPlainDistance() { return m_plain.getDistance(); }
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