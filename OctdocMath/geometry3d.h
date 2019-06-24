#pragma once

#include "position.h"

namespace octdoc
{
	namespace mth
	{
		class Point3D
		{
		public:
			float3 p;

		public:
			Point3D();
			Point3D(float3 point);

			float Distance(float3 point);
			float DistanceSquare(float3 point);
			float TimeToGetClose(float3 position, float3 direction, float distance);
		};

		class Line3D
		{
		public:
			float3 p;
			float3 v;

		public:
			Line3D();
			Line3D(float3 point, float3 direction);

			float Distance(float3 point);
			float DistanceSquare(float3 point);
			float TimeToGetClose(float3 position, float3 direction, float distance);
		};

		class Plain3D
		{
		public:
			float3 n;
			float d;

		public:
			Plain3D();
			Plain3D(float3 normal, float distance);

			bool IsPointOn(float3 point, float eps = EPS);
			bool IsPointBelow(float3 point);
			bool IsPointOver(float3 point);
			float Distance(float3 point);
			float DirectionalDistance(Position& ray);
			// return: how many raydirs are necessary to reach the plain
			float DirectionalDistance(float3 raypos, float3 raydir);
			float TimeToGetClose(float3 position, float3 direction, float distance);
		};

		class Triangle3D
		{
			Plain3D m_plain;
			float3 m_vertices[3];

		public:
			Triangle3D();
			Triangle3D(float3 tri[3]);
			Triangle3D(float3 v1, float3 v2, float3 v3);
			Triangle3D(float3 tri[3], float3 plainNormal, float plainDistance);

			bool IsPointOver(float3 point);
			bool IsPointOn(float3 point, float eps = EPS);

			inline Plain3D& getPlain() { return m_plain; }
			inline float3 getPlainNormal() { return m_plain.n; }
			inline float getPlainDistance() { return m_plain.d; }
			inline float3* getVertices(unsigned index) { return m_vertices; }
			inline float3 getVertex(unsigned index) { return m_vertices[index]; }
		};

		bool IsPointOverTriangle(float3 tri[3], float3 point);

		float DistanceLinePoint(float3 linePoint, float3 lineDirection, float3 point);
		float DistanceSquareLinePoint(float3 linePoint, float3 lineDirection, float3 point);

		// Points on the lines that are closest to the other line
		void MinDistancePoints2Lines(float3 p1, float3 v1, float3 p2, float3 v2, float3& out1, float3& out2);

		float3 LMSLineIntersection(Line3D lines[], int count);
		float3 LMSLineIntersection(float3 linePoints[], float3 lineDirections[], int count);
	}
}