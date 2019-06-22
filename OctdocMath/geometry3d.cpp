#include "geometry3d.h"

namespace octdoc
{
	namespace mth
	{
		Line3D::Line3D() :p(), v() {}
		Line3D::Line3D(float3 point, float3 direction) : p(point), v(direction) {}

		Triangle3D::Triangle3D() : m_plainDistance(0.0f) {}
		Triangle3D::Triangle3D(float3 tri[3]) : Triangle3D(tri[0], tri[1], tri[2]) {}
		Triangle3D::Triangle3D(float3 v1, float3 v2, float3 v3)
		{
			m_vertices[0] = v1;
			m_vertices[1] = v2;
			m_vertices[2] = v3;
			m_plainNormal = (m_vertices[1] - m_vertices[2]).Cross(m_vertices[1] - m_vertices[0]).Normalized();
			m_plainDistance = m_plainNormal.Dot(m_vertices[0]);
		}
		Triangle3D::Triangle3D(float3 tri[3], float3 plainNormal, float plainDistance)
		{
			m_vertices[0] = tri[0];
			m_vertices[1] = tri[1];
			m_vertices[2] = tri[2];
			m_plainNormal = plainNormal;
			m_plainDistance = plainDistance;
		}
		bool Triangle3D::isPointOver(float3 point)
		{
			return IsPointOverTriangle(m_vertices, point);
		}
		float Triangle3D::DirectionalDistance(Position ray)
		{
			return DirectionalDistance(ray.position, ray.GetLookDirection());
		}
		float Triangle3D::DirectionalDistance(float3 raypos, float3 raydir)
		{
			float distfromtriplain = m_plainNormal.Dot(raypos) - m_plainDistance;
			float disttowardplain = -m_plainNormal.Dot(raydir);
			if (disttowardplain < 0.0f)
				return NAN;
			float dist = distfromtriplain / disttowardplain;
			float3 point = dist * raydir + raypos;
			return IsPointOverTriangle(m_vertices, point) ? dist : NAN;
		}

		bool IsPointOverTriangle(float3 tri[3], float3 point)
		{
			float3 vecs[3] = { tri[1] - tri[0],
				tri[2] - tri[0],
				point - tri[0] };
			float dot00 = vecs[0].Dot(vecs[0]);
			float dot01 = vecs[0].Dot(vecs[1]);
			float dot02 = vecs[0].Dot(vecs[2]);
			float dot11 = vecs[1].Dot(vecs[1]);
			float dot12 = vecs[1].Dot(vecs[2]);
			float denom = dot00 * dot11 - dot01 * dot01;
			float u = (dot11 * dot02 - dot01 * dot12) / denom;
			float v = (dot00 * dot12 - dot01 * dot02) / denom;
			return u >= 0.0f && v >= 0.0f && u + v <= 1.0f;
		}
		float DistanceLinePoint(float3 linePoint, float3 lineDirection, float3 point)
		{
			return sqrtf(DistanceSquareLinePoint(linePoint, lineDirection, point));
		}
		float DistanceSquareLinePoint(float3 linePoint, float3 lineDirection, float3 point)
		{
			return lineDirection.Cross(point - linePoint).LengthSquare() / lineDirection.LengthSquare();
		}
		void MinDistancePoints2Lines(float3 p1, float3 v1, float3 p2, float3 v2, float3& out1, float3& out2)
		{
			float3x3 rot = NormalToRotationMatrix(v1.Cross(v2).Normalized());
			float3 p1p = rot * p1;
			float3 p2p = rot * p2;
			float3 v1p = rot * v1;
			float3 v2p = rot * v2;
			float2 t = float2x2(v1p.x, -v2p.x, v1p.x, -v2p.y).Inverse() * float2(p2p.x - p1p.x, p2p.y - p1p.y);
			out1 = p1 + v1 * t.x;
			out2 = p2 + v2 * t.y;
		}
		float3 LMSLineIntersection(Line3D lines[], int count)
		{
			float3x3 mat;
			float3 vec;
			for (int i = 0; i < count; i++)
			{
				float3 p = lines[i].p;
				float3 v = lines[i].v;
				float oneovervls = 1.0f / v.LengthSquare();
				float3x3 tmp = float3x3::Identity() - float3x3(
					v.x * v.x, v.x * v.y, v.x * v.z,
					v.y * v.x, v.y * v.y, v.y * v.z,
					v.z * v.x, v.z * v.y, v.z * v.z
				) * oneovervls;
				mat += tmp;
				vec += tmp * p;
			}
			return mat.Inverse() * vec;
		}
		float3 LMSLineIntersection(float3 linePoints[], float3 lineDirections[], int count)
		{
			float3x3 mat;
			float3 vec;
			for (int i = 0; i < count; i++)
			{
				float3 p = linePoints[i];
				float3 v = lineDirections[i];
				float oneovervls = 1.0f / v.LengthSquare();
				float3x3 tmp = float3x3::Identity() - float3x3(
					v.x * v.x, v.x * v.y, v.x * v.z,
					v.y * v.x, v.y * v.y, v.y * v.z,
					v.z * v.x, v.z * v.y, v.z * v.z
				) * oneovervls;
				mat += tmp;
				vec += tmp * p;
			}
			return mat.Inverse() * vec;
		}
	}
}