#pragma once

#include "plain3d.hpp"

namespace octdoc
{
	namespace mth
	{
		template <typename T>
		class Triangle3D
		{
			Plain3D<T> m_plain;
			vec3<T> m_vertices[3];

		public:
			Triangle3D() {}
			Triangle3D(vec3<T> tri[3]) : Triangle3D(tri[0], tri[1], tri[2]) {}
			Triangle3D(vec3<T> v1, vec3<T> v2, vec3<T> v3)
			{
				m_vertices[0] = v1;
				m_vertices[1] = v2;
				m_vertices[2] = v3;
				m_plain.setNormal((m_vertices[1] - m_vertices[2]).Cross(m_vertices[1] - m_vertices[0]).Normalized());
				m_plain.setDistance(m_plain.getNormal().Dot(m_vertices[0]));
			}
			Triangle3D(vec3<T> tri[3], vec3<T> plainNormal, T plainDistance)
			{
				m_vertices[0] = tri[0];
				m_vertices[1] = tri[1];
				m_vertices[2] = tri[2];
				m_plain.setNormal(plainNormal);
				m_plain.setDistance(plainDistance);
			}

			bool IsPointOver(vec3<T> point)
			{
				return IsPointOverTriangle(m_vertices, point);
			}
			bool IsPointOn(vec3<T> point, T eps = EPS)
			{
				return m_plain.IsPointOn(point, eps) && IsPointOverTriangle(m_vertices, point);
			}

			inline Plain3D<T>& getPlain() { return m_plain; }
			inline vec3<T> getPlainNormal() { return m_plain.getNormal(); }
			inline T getPlainDistance() { return m_plain.getDistance(); }
			inline vec3<T>* getVertices(unsigned index) { return m_vertices; }
			inline vec3<T> getVertex(unsigned index) { return m_vertices[index]; }
		};
	}
}