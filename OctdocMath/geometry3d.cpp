#include "geometry3d.h"
#include "formulas.h"

namespace octdoc
{
	namespace mth
	{
		Point3D::Point3D() :p() {}
		Point3D::Point3D(float3 point) : p(point) {}

		float Point3D::Distance(float3 point)
		{
			return (p - point).Length();
		}
		float Point3D::DistanceSquare(float3 point)
		{
			return (p - point).LengthSquare();
		}
		float Point3D::TimeToGetClose(float3 position, float3 direction, float distance)
		{
			position -= p;
			float a = direction.LengthSquare();
			float b = 2.0f * position.Dot(direction);
			float c = position.LengthSquare() - distance * distance;
			float s1, s2;
			return (Quadratic(a, b, c, s1, s2) == 0) ? NAN : (s2 < 0.0f ? s2 : s1);
		}

		Line3D::Line3D() :p(), v() {}
		Line3D::Line3D(float3 point, float3 direction) : p(point), v(direction) {}
		float Line3D::Distance(float3 point)
		{
			return DistanceLinePoint(p, v, point);
		}
		float Line3D::DistanceSquare(float3 point)
		{
			return DistanceSquareLinePoint(p, v, point);
		}
		float Line3D::TimeToGetClose(float3 position, float3 direction, float distance)
		{
			position -= p;
			float a = v.Cross(direction).LengthSquare();
			float b = 2.0f * v.Cross(position).Dot(v.Cross(direction));
			float c = v.Cross(position).LengthSquare() - distance * distance;
			float s1, s2;
			return (Quadratic(a, b, c, s1, s2) == 0) ? NAN : (s2 < 0.0f ? s2 : s1);
		}

		Plain3D::Plain3D() : n(), d(0.0f) {}
		Plain3D::Plain3D(float3 normal, float distance) : n(normal), d(distance) {}
		bool Plain3D::IsPointOn(float3 point, float eps)
		{
			return fabsf(point.Dot(n) - d) < eps;
		}
		bool Plain3D::IsPointBelow(float3 point)
		{
			return point.Dot(n) < d;
		}
		bool Plain3D::IsPointOver(float3 point)
		{
			return point.Dot(n) > d;
		}
		float Plain3D::Distance(float3 point)
		{
			return n.Dot(point) - d;
		}
		float Plain3D::DirectionalDistance(Position& ray)
		{
			return DirectionalDistance(ray.position, ray.GetLookDirection());
		}
		float Plain3D::DirectionalDistance(float3 raypos, float3 raydir)
		{
			float distTowardPlain = -n.Dot(raydir);
			float distFromPlain = n.Dot(raypos) - d;
			return distFromPlain / distTowardPlain;
		}

		float Plain3D::TimeToGetClose(float3 position, float3 direction, float distance)
		{
			float distTowardPlain = -n.Dot(direction);
			float distFromPlain = n.Dot(position) - d;
			if (distFromPlain < 0)
				distFromPlain += distance;
			else
				distFromPlain -= distance;
			return distFromPlain / distTowardPlain;
		}

		Triangle3D::Triangle3D() {}
		Triangle3D::Triangle3D(float3 tri[3]) : Triangle3D(tri[0], tri[1], tri[2]) {}
		Triangle3D::Triangle3D(float3 v1, float3 v2, float3 v3)
		{
			m_vertices[0] = v1;
			m_vertices[1] = v2;
			m_vertices[2] = v3;
			m_plain.n = (m_vertices[1] - m_vertices[2]).Cross(m_vertices[1] - m_vertices[0]).Normalized();
			m_plain.d = m_plain.n.Dot(m_vertices[0]);
		}
		Triangle3D::Triangle3D(float3 tri[3], float3 plainNormal, float plainDistance)
		{
			m_vertices[0] = tri[0];
			m_vertices[1] = tri[1];
			m_vertices[2] = tri[2];
			m_plain.n = plainNormal;
			m_plain.n = plainDistance;
		}
		bool Triangle3D::IsPointOver(float3 point)
		{
			return IsPointOverTriangle(m_vertices, point);
		}
		bool Triangle3D::IsPointOn(float3 point, float eps)
		{
			return m_plain.IsPointOn(point, eps) && IsPointOverTriangle(m_vertices, point);
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
			//return (point - linePoint).LengthSquare() - (lineDirection.Dot(point - linePoint)) * (lineDirection.Dot(point - linePoint)) / lineDirection.LengthSquare();
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