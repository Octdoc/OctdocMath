#pragma once

#include "position.h"

namespace octdoc
{
	namespace mth
	{
		class Line3D
		{
		public:
			float3 p;
			float3 v;

		public:
			Line3D();
			Line3D(float3 point, float3 direction);
		};

		class Triangle3D
		{
			float3 m_vertices[3];
			float3 m_plainNormal;
			float m_plainDistance;

		public:
			Triangle3D();
			Triangle3D(float3 tri[3]);
			Triangle3D(float3 v1, float3 v2, float3 v3);
			Triangle3D(float3 tri[3], float3 plainNormal, float plainDistance);

			bool isPointOver(float3 point);
			float DirectionalDistance(Position ray);
			float DirectionalDistance(float3 raypos, float3 raydir);

			inline float3* getVertices(unsigned index) { return m_vertices; }
			inline float3 getVertex(unsigned index) { return m_vertices[index]; }
			inline float3 getPlainNormal() { return m_plainNormal; }
			inline float getPlainDistance() { return m_plainDistance; }
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