#include "geometry3d.h"
#include "formulas.h"

namespace octdoc
{
	namespace mth
	{
		Point3D::Point3D() :p() {}
		Point3D::Point3D(double3 point) : p(point) {}

		double Point3D::Distance(double3 point)
		{
			return (p - point).Length();
		}
		double Point3D::DistanceSquare(double3 point)
		{
			return (p - point).LengthSquare();
		}
		double Point3D::TimeToGetClose(double3 position, double3 direction, double distance)
		{
			position -= p;
			double a = direction.LengthSquare();
			double b = 2 * position.Dot(direction);
			double c = position.LengthSquare() - distance * distance;
			double s1, s2;
			return (Quadratic(a, b, c, s1, s2) == 0) ? NAN : (s2 < 0 ? s2 : s1);
		}

		Line3D::Line3D() :p(), v() {}
		Line3D::Line3D(double3 point, double3 direction) : p(point), v(direction) {}
		double Line3D::Distance(double3 point)
		{
			return DistanceLinePoint(p, v, point);
		}
		double Line3D::DistanceSquare(double3 point)
		{
			return DistanceSquareLinePoint(p, v, point);
		}
		double Line3D::TimeToGetClose(double3 position, double3 direction, double distance)
		{
			position -= p;
			double a = v.Cross(direction).LengthSquare();
			double b = 2 * v.Cross(position).Dot(v.Cross(direction));
			double c = v.Cross(position).LengthSquare() - distance * distance;
			double s1, s2;
			return (Quadratic(a, b, c, s1, s2) == 0) ? NAN : (s2 < 0 ? s2 : s1);
		}

		Plain3D::Plain3D() : n(), d(0) {}
		Plain3D::Plain3D(double3 normal, double distance) : n(normal), d(distance) {}
		bool Plain3D::IsPointOn(double3 point, double eps)
		{
			return fabs(point.Dot(n) - d) < eps;
		}
		bool Plain3D::IsPointBelow(double3 point)
		{
			return point.Dot(n) < d;
		}
		bool Plain3D::IsPointOver(double3 point)
		{
			return point.Dot(n) > d;
		}
		double Plain3D::Distance(double3 point)
		{
			return n.Dot(point) - d;
		}
		double Plain3D::DirectionalDistance(Position<double>& ray)
		{
			return DirectionalDistance((double3)ray.position, (double3)ray.GetLookDirection());
		}
		double Plain3D::DirectionalDistance(double3 raypos, double3 raydir)
		{
			double distTowardPlain = -n.Dot(raydir);
			double distFromPlain = n.Dot(raypos) - d;
			return distFromPlain / distTowardPlain;
		}

		double Plain3D::TimeToGetClose(double3 position, double3 direction, double distance)
		{
			double distTowardPlain = -n.Dot(direction);
			double distFromPlain = n.Dot(position) - d;
			if (distFromPlain < 0)
				distFromPlain += distance;
			else
				distFromPlain -= distance;
			return distFromPlain / distTowardPlain;
		}

		Triangle3D::Triangle3D() {}
		Triangle3D::Triangle3D(double3 tri[3]) : Triangle3D(tri[0], tri[1], tri[2]) {}
		Triangle3D::Triangle3D(double3 v1, double3 v2, double3 v3)
		{
			m_vertices[0] = v1;
			m_vertices[1] = v2;
			m_vertices[2] = v3;
			m_plain.n = (m_vertices[1] - m_vertices[2]).Cross(m_vertices[1] - m_vertices[0]).Normalized();
			m_plain.d = m_plain.n.Dot(m_vertices[0]);
		}
		Triangle3D::Triangle3D(double3 tri[3], double3 plainNormal, double plainDistance)
		{
			m_vertices[0] = tri[0];
			m_vertices[1] = tri[1];
			m_vertices[2] = tri[2];
			m_plain.n = plainNormal;
			m_plain.n = plainDistance;
		}
		bool Triangle3D::IsPointOver(double3 point)
		{
			return IsPointOverTriangle(m_vertices, point);
		}
		bool Triangle3D::IsPointOn(double3 point, double eps)
		{
			return m_plain.IsPointOn(point, eps) && IsPointOverTriangle(m_vertices, point);
		}

		bool IsPointOverTriangle(double3 tri[3], double3 point)
		{
			double3 vecs[3] = { tri[1] - tri[0],
				tri[2] - tri[0],
				point - tri[0] };
			double dot00 = vecs[0].Dot(vecs[0]);
			double dot01 = vecs[0].Dot(vecs[1]);
			double dot02 = vecs[0].Dot(vecs[2]);
			double dot11 = vecs[1].Dot(vecs[1]);
			double dot12 = vecs[1].Dot(vecs[2]);
			double denom = dot00 * dot11 - dot01 * dot01;
			double u = (dot11 * dot02 - dot01 * dot12) / denom;
			double v = (dot00 * dot12 - dot01 * dot02) / denom;
			return u >= 0 && v >= 0.0f && u + v <= 1;
		}
		double DistanceLinePoint(double3 linePoint, double3 lineDirection, double3 point)
		{
			return sqrtf(DistanceSquareLinePoint(linePoint, lineDirection, point));
		}
		double DistanceSquareLinePoint(double3 linePoint, double3 lineDirection, double3 point)
		{
			return lineDirection.Cross(point - linePoint).LengthSquare() / lineDirection.LengthSquare();
			//return (point - linePoint).LengthSquare() - (lineDirection.Dot(point - linePoint)) * (lineDirection.Dot(point - linePoint)) / lineDirection.LengthSquare();
		}
		void MinDistancePoints2Lines(double3 p1, double3 v1, double3 p2, double3 v2, double3& out1, double3& out2)
		{
			double3x3 rot = NormalToRotationMatrix(v1.Cross(v2).Normalized());
			double3 p1p = rot * p1;
			double3 p2p = rot * p2;
			double3 v1p = rot * v1;
			double3 v2p = rot * v2;
			double2 t = double2x2(v1p.x, -v2p.x, v1p.x, -v2p.y).Inverse() * double2(p2p.x - p1p.x, p2p.y - p1p.y);
			out1 = p1 + v1 * t.x;
			out2 = p2 + v2 * t.y;
		}
		double3 LMSLineIntersection(Line3D lines[], int count)
		{
			double3x3 mat;
			double3 vec;
			for (int i = 0; i < count; i++)
			{
				double3 p = lines[i].p;
				double3 v = lines[i].v;
				double oneovervls = 1 / v.LengthSquare();
				double3x3 tmp = double3x3::Identity() - double3x3(
					v.x * v.x, v.x * v.y, v.x * v.z,
					v.y * v.x, v.y * v.y, v.y * v.z,
					v.z * v.x, v.z * v.y, v.z * v.z
				) * oneovervls;
				mat += tmp;
				vec += tmp * p;
			}
			return mat.Inverse() * vec;
		}
		double3 LMSLineIntersection(double3 linePoints[], double3 lineDirections[], int count)
		{
			double3x3 mat;
			double3 vec;
			for (int i = 0; i < count; i++)
			{
				double3 p = linePoints[i];
				double3 v = lineDirections[i];
				double oneovervls = 1.0f / v.LengthSquare();
				double3x3 tmp = double3x3::Identity() - double3x3(
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