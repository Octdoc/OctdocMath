#pragma once

#include "linalg.hpp"

namespace octdoc
{
	namespace mth
	{
		template <typename T>
		class Point3D
		{
			vec3<T> m_point;

		public:
			Point3D() : m_point() {}
			Point3D(vec3<T> point) : m_point(point) {}

			inline vec3<T> getPoint() { return m_point; }
			inline void setPoint(vec3<T> point) { m_point = point; }

			double Distance(vec3<T> point)
			{
				return (m_point - point).Length();
			}
			double DistanceSquare(vec3<T> point)
			{
				return (m_point - point).LengthSquare();
			}
			double TimeToGetClose(vec3<T> position, vec3<T> direction, T distance)
			{
				position -= m_point;
				T a = direction.LengthSquare();
				T b = 2 * position.Dot(direction);
				T c = position.LengthSquare() - distance * distance;
				T s1, s2;
				return (Quadratic(a, b, c, s1, s2) == 0) ? NAN : (s2 < 0 ? s2 : s1);
			}
		};
	}
}