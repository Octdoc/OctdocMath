#pragma once

#include "point3d.hpp"
#include "line3d.hpp"
#include "triangle3d.hpp"

namespace octdoc
{
	namespace mth
	{
		using Point3Df = Point3D<float>;
		using Point3Dd = Point3D<double>;
		using Line3Df = Line3D<float>;
		using Line3Dd = Line3D<double>;
		using Plain3Df = Plain3D<float>;
		using Plain3Dd = Plain3D<double>;
		using Triangle3Df = Triangle3D<float>;
		using Triangle3Dd = Triangle3D<double>;

		template <typename T>
		bool IsPointOverTriangle(vec3<T> tri[3], vec3<T> point)
		{
			vec3<T> vecs[3] = { tri[1] - tri[0],
				tri[2] - tri[0],
				point - tri[0] };
			T dot00 = vecs[0].Dot(vecs[0]);
			T dot01 = vecs[0].Dot(vecs[1]);
			T dot02 = vecs[0].Dot(vecs[2]);
			T dot11 = vecs[1].Dot(vecs[1]);
			T dot12 = vecs[1].Dot(vecs[2]);
			T denom = dot00 * dot11 - dot01 * dot01;
			T u = (dot11 * dot02 - dot01 * dot12) / denom;
			T v = (dot00 * dot12 - dot01 * dot02) / denom;
			return u >= 0 && v >= 0.0f && u + v <= 1;
		}

		template <typename T>
		double DistanceLinePoint(vec3<T> linePoint, vec3<T> lineDirection, vec3<T> point)
		{
			return sqrt(DistanceSquareLinePoint(linePoint, lineDirection, point));
		}

		template <typename T>
		double DistanceSquareLinePoint(vec3<T> linePoint, vec3<T> lineDirection, vec3<T> point)
		{
			return lineDirection.Cross(point - linePoint).LengthSquare() / lineDirection.LengthSquare();
		}

		// Points on the lines that are closest to the other line
		template <typename T>
		void MinDistancePoints2Lines(vec3<T> p1, vec3<T> v1, vec3<T> p2, vec3<T> v2, vec3<T>& out1, vec3<T>& out2)
		{
			mat3x3<T> rot = NormalToRotationMatrix(v1.Cross(v2).Normalized());
			vec3<T> p1p = rot * p1;
			vec3<T> p2p = rot * p2;
			vec3<T> v1p = rot * v1;
			vec3<T> v2p = rot * v2;
			vec2<T> t = mat2x2<T>(v1p.x, -v2p.x, v1p.x, -v2p.y).Inverse() * vec2<T>(p2p.x - p1p.x, p2p.y - p1p.y);
			out1 = p1 + v1 * t.x;
			out2 = p2 + v2 * t.y;
		}

		template <typename T>
		vec3<T> LMSLineIntersection(vec3<T> linePoints[], vec3<T> lineDirections[], int count)
		{
			mat3x3<T> mat;
			vec3<T> vec;
			for (int i = 0; i < count; i++)
			{
				vec3<T> p = linePoints[i];
				vec3<T> v = lineDirections[i];
				double oneovervls = 1.0f / v.LengthSquare();
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