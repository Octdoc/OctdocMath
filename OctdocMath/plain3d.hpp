#pragma once

#include "position.hpp"

namespace octdoc
{
	namespace mth
	{
		template <typename T>
		class Plain3D
		{
			vec3<T> m_normal;
			T m_distance;

		public:
			Plain3D() : m_normal(), m_distance(0) {}
			Plain3D(vec3<T> unitNormal, T distance) : m_normal(unitNormal), m_distance(distance) {}

			inline vec3<T> getNormal() { return m_normal; }
			inline void setNormal(vec3<T> unitNormal) { m_normal = unitNormal; }
			inline T getDistance() { return m_distance; }
			inline void setDistance(T distance) { m_distance = distance; }

			bool IsPointOn(vec3<T> point, T eps = EPS)
			{
				return fabs(point.Dot(m_normal) - m_distance) < eps;
			}
			bool IsPointBelow(vec3<T> point)
			{
				return point.Dot(m_normal) < m_distance;
			}
			bool IsPointOver(vec3<T> point)
			{
				return point.Dot(m_normal) > m_distance;
			}
			T Distance(vec3<T> point)
			{
				return m_normal.Dot(point) - m_distance;
			}
			T DirectionalDistance(Position<T>& ray)
			{
				return DirectionalDistance(ray.position, ray.GetLookDirection());
			}
			// return: how many raydirs are necessary to reach the plain
			T DirectionalDistance(vec3<T> raypos, vec3<T> raydir)
			{
				T distTowardPlain = -m_normal.Dot(raydir);
				T distFromPlain = m_normal.Dot(raypos) - m_distance;
				return distFromPlain / distTowardPlain;
			}
			T TimeToGetClose(vec3<T> position, vec3<T> direction, T distance)
			{
				T distTowardPlain = -m_normal.Dot(direction);
				T distFromPlain = m_normal.Dot(position) - m_distance;
				if (distFromPlain < 0)
					distFromPlain += distance;
				else
					distFromPlain -= distance;
				return distFromPlain / distTowardPlain;
			}
		};
	}
}