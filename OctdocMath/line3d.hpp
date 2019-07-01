#pragma once

#include "linalg.hpp"

namespace octdoc
{
	namespace mth
	{
		template <typename T>
		class Line3D
		{
			vec3<T> m_point;
			vec3<T> m_direction;

		public:
			Line3D() : m_point(), m_direction() {}
			Line3D(vec3<T> point, vec3<T> unitDirection) : m_point(point), m_direction(unitDirection) {}

			static Line3D From2Points(vec3<T> p1, vec3<T> p2) { return Line3D(p1, (p2 - p1).Normalized()); }

			inline vec3<T> getPoint() { return m_point; }
			inline void setPoint(vec3<T> point) { m_point = point; }
			inline vec3<T> getDirection() { return m_direction; }
			inline void setDirection(vec3<T> unitDirection) { m_direction = unitDirection; }

			double Distance(vec3<T> point)
			{
				return DistanceLinePoint(m_point, m_direction, point);
			}
			double DistanceSquare(vec3<T> point)
			{
				return DistanceSquareLinePoint(m_point, m_direction, point);
			}
			double TimeToGetClose(vec3<T> position, vec3<T> direction, T distance)
			{
				position -= m_point;
				vec3<T> vxd = m_direction.Cross(direction);
				vec3<T> vxp = m_direction.Cross(position);
				T a = vxd.LengthSquare();
				T b = 2 * vxp.Dot(vxd);
				T c = vxp.LengthSquare() - distance * distance;
				T s1, s2;
				return (Quadratic(a, b, c, s1, s2) == 0) ? NAN : (s2 < 0 ? s2 : s1);
			}
		};

		template <typename T>
		vec3<T> LMSLineIntersection(Line3D<T> lines[], int count)
		{
			mat3x3<T> mat;
			vec3<T> vec;
			for (int i = 0; i < count; i++)
			{
				vec3<T> p = lines[i].getPoint();
				vec3<T> v = lines[i].getDirection();
				T oneovervls = 1 / v.LengthSquare();
				mat3x3<T> tmp = mat3x3<T>::Identity() - mat3x3<T>(
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