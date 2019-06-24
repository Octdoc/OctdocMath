#pragma once

#include <cmath>
#include <iostream>

namespace octdoc
{
	namespace mth
	{
		constexpr float PI = 3.1415926536f;
		constexpr float EPS = 1e-6f;

		class float2;
		class float3;
		class float4;

		class quaternion;

		class float2x2;
		class float3x3;
		class float4x4;
		typedef float4x4 matrix;

		class float2
		{
		public:
			float x;
			float y;

		public:
			explicit float2();
			explicit float2(const float f);
			explicit float2(const float* const v);
			explicit float2(const float x, const float y);
			float2(const float2& v);
			explicit float2(const float3& v);
			explicit float2(const float4& v);
			bool isZeroVector() const;
			float Dot(const float2 v) const;
			float LengthSquare() const;
			float Length() const;
			float Angle() const;
			void Abs();
			float Max() const;
			float Min() const;
			float Sum() const;
			void Normalize();
			float2 Normalized() const;
			float2 operator+(const float2 v) const;
			float2 operator-(const float2 v) const;
			float2 operator*(const float2 v) const;
			float2 operator/(const float2 v) const;
			float2 operator+(const float f) const;
			float2 operator-(const float f) const;
			float2 operator*(const float f) const;
			float2 operator/(const float f) const;
			float2 operator-() const;
			float2& operator+=(const float2 v);
			float2& operator-=(const float2 v);
			float2& operator*=(const float2 v);
			float2& operator/=(const float2 v);
			float2& operator=(const float2 v);
			float2& operator+=(const float f);
			float2& operator-=(const float f);
			float2& operator*=(const float f);
			float2& operator/=(const float f);
			float2& operator=(const float f);
			float2 operator*(const float2x2& m) const;
			bool operator==(float2 v);
			bool operator!=(float2 v);
			bool isNear(float2 v, float eps);
			float operator()(const int i) const;
			float& operator()(const int i);
			explicit operator float3() const;
			explicit operator float4() const;
			explicit operator float* () const;
		};

		class float3
		{
		public:
			float x;
			float y;
			float z;

		public:
			explicit float3();
			explicit float3(const float f);
			explicit float3(const float* const v);
			explicit float3(const float x, const float y, const float z);
			explicit float3(const float2& v);
			float3(const float3& v);
			explicit float3(const float4& v);
			bool isZeroVector() const;
			float Dot(const float3 v) const;
			float3 Cross(const float3 v) const;
			float LengthSquare() const;
			float Length() const;
			void Abs();
			float Max() const;
			float Min() const;
			float Sum() const;
			void Normalize();
			float3 Normalized() const;
			float3 operator+(const float3 v) const;
			float3 operator-(const float3 v) const;
			float3 operator*(const float3 v) const;
			float3 operator/(const float3 v) const;
			float3 operator+(const float f) const;
			float3 operator-(const float f) const;
			float3 operator*(const float f) const;
			float3 operator/(const float f) const;
			float3 operator-() const;
			float3& operator+=(const float3 v);
			float3& operator-=(const float3 v);
			float3& operator*=(const float3 v);
			float3& operator/=(const float3 v);
			float3& operator=(const float3 v);
			float3& operator+=(const float f);
			float3& operator-=(const float f);
			float3& operator*=(const float f);
			float3& operator/=(const float f);
			float3& operator=(const float f);
			float3 operator*(const float3x3& m) const;
			bool operator==(float3 v);
			bool operator!=(float3 v);
			bool isNear(float3 v, float eps);
			float operator()(const int i) const;
			float& operator()(const int i);
			explicit operator float2() const;
			explicit operator float4() const;
			explicit operator float* () const;
		};

		class float4
		{
		public:
			float x;
			float y;
			float z;
			float w;

		public:
			explicit float4();
			explicit float4(const float f);
			explicit float4(const float* const v);
			explicit float4(const float x, const float y, const float z, const float w);
			explicit float4(const float2& v);
			explicit float4(const float3& v);
			float4(const float4& v);
			bool isZeroVector() const;
			float Dot(const float4 v) const;
			float LengthSquare() const;
			float Length() const;
			void Abs();
			float Max() const;
			float Min() const;
			float Sum() const;
			void Normalize();
			float4 Normalized() const;
			float4 operator+(const float4 v) const;
			float4 operator-(const float4 v) const;
			float4 operator*(const float4 v) const;
			float4 operator/(const float4 v) const;
			float4 operator+(const float f) const;
			float4 operator-(const float f) const;
			float4 operator*(const float f) const;
			float4 operator/(const float f) const;
			float4 operator-() const;
			float4& operator+=(const float4 v);
			float4& operator-=(const float4 v);
			float4& operator*=(const float4 v);
			float4& operator/=(const float4 v);
			float4& operator=(const float4 v);
			float4& operator+=(const float f);
			float4& operator-=(const float f);
			float4& operator*=(const float f);
			float4& operator/=(const float f);
			float4& operator=(const float f);
			float4 operator*(const float4x4& m) const;
			bool operator==(float4 v);
			bool operator!=(float4 v);
			bool isNear(float4 v, float eps);
			float operator()(const int i) const;
			float& operator()(const int i);
			explicit operator float2() const;
			explicit operator float3() const;
			explicit operator float* () const;
		};

		class quaternion
		{
		public:
			float x;
			float y;
			float z;
			float w;

		public:
			quaternion();
			quaternion(const float f);
			quaternion(const float* const q);
			quaternion(const float x, const float y, const float z, const float w);
			quaternion(const quaternion& q);
			bool isZeroVector() const;
			quaternion Conjugate() const;
			quaternion Inverse();
			float LengthSquare() const;
			float Length() const;
			quaternion operator+(const quaternion q) const;
			quaternion operator-(const quaternion q) const;
			quaternion operator*(const quaternion q) const;
			quaternion operator+(const float f) const;
			quaternion operator-(const float f) const;
			quaternion operator*(const float f) const;
			quaternion operator/(const float f) const;
			quaternion operator-() const;
			quaternion& operator+=(const quaternion q);
			quaternion& operator-=(const quaternion q);
			quaternion& operator*=(const quaternion q);
			quaternion& operator=(const quaternion q);
			quaternion& operator+=(const float f);
			quaternion& operator-=(const float f);
			quaternion& operator*=(const float f);
			quaternion& operator/=(const float f);
			quaternion& operator=(const float f);
			bool operator==(quaternion q);
			bool operator==(float f);
			bool isNear(quaternion q, float eps);
			float operator()(const int i) const;
			float& operator()(const int i);
			explicit operator float* () const;
		};

		class float2x2
		{
			float mat[2][2];

		public:
			explicit float2x2();
			explicit float2x2(const float f);
			explicit float2x2(const float* const m);
			explicit float2x2(const float _00, const float _01, const float _10, const float _11);
			float2x2(const float2x2& m);
			explicit float2x2(const float3x3& m);
			explicit float2x2(const float4x4& m);
			static float2x2 Identity();
			static float2x2 Rotation(const float a);
			static float2x2 Scaling(const float x, const float y);
			static float2x2 Scaling(const float2 s);
			static float2x2 RotationScaling(const float a, const float x, const float y);
			static float2x2 RotationScaling(const float a, const float2 s);

			float operator()(const int row, const int column) const;
			float& operator()(const int row, const int column);
			float2 operator*(const float2 v) const;
			explicit operator float3x3() const;
			explicit operator float4x4() const;
			float Determinant() const;
			void Invert();
			float2x2 Inverse() const;
			void Transpose();
			float2x2 Trasposed() const;
			float2x2 operator*(const float2x2& m) const;
			float2x2& operator*=(const float2x2& m);
			float2x2 operator+(const float2x2& m) const;
			float2x2& operator+=(const float2x2& m);
			float2x2 operator-(const float2x2& m) const;
			float2x2& operator-=(const float2x2& m);
			float2x2& operator=(const float2x2& m);
			float2x2 operator+(const float f) const;
			float2x2& operator+=(const float f);
			float2x2 operator-(const float f) const;
			float2x2& operator-=(const float f);
			float2x2 operator*(const float f) const;
			float2x2& operator*=(const float f);
			float2x2 operator/(const float f) const;
			float2x2& operator/=(const float f);
			float2x2& operator=(const float f);
			float2x2 operator-() const;
			bool operator==(float2x2& m);
			bool operator!=(float2x2& m);
			bool isNear(float2x2& m, float eps);
		};

		class float3x3
		{
			float mat[3][3];

		public:
			explicit float3x3();
			explicit float3x3(const float f);
			explicit float3x3(const float* const m);
			explicit float3x3(const float _00, const float _01, const float _02,
				const float _10, const float _11, const float _12,
				const float _20, const float _21, const float _22);
			explicit float3x3(const float2x2& m);
			float3x3(const float3x3& m);
			explicit float3x3(const float4x4& m);
			static float3x3 Identity();
			static float3x3 Scaling2D(const float x, const float y);
			static float3x3 Scaling2D(const float2 s);
			static float3x3 Translation2D(const float x, const float y);
			static float3x3 Translation2D(const float2 t);
			static float3x3 Rotation2D(const float a);
			static float3x3 Scaling(const float x, const float y, const float z);
			static float3x3 Scaling(const float3 s);
			static float3x3 RotationX(const float a);
			static float3x3 RotationY(const float a);
			static float3x3 RotationZ(const float a);
			static float3x3 Rotation(const float pitch, const float yaw, const float roll);
			static float3x3 Rotation(const float3 r);
			static float3x3 RotationAxis(const float3 axis, const float a);
			static float3x3 RotationNormal(const float3 n, const float a);
			static float3x3 RotationCamera(const float x, const float y, const float z);
			static float3x3 RotationCamera(const float3 r);

			static float3x3 RotateUnitVector(const float3 from, const float3 to);
			mth::float3 ToRotationAngles() const;
			mth::float3 ToCameraRotation() const;

			float operator()(const int row, const int column) const;
			float& operator()(const int row, const int column);
			float3 operator*(const float3 v) const;
			explicit operator float2x2() const;
			explicit operator float4x4() const;
			float Determinant() const;
			void Invert();
			float3x3 Inverse() const;
			void Transpose();
			float3x3 Transposed() const;
			float3x3 operator*(const float3x3& m) const;
			float3x3& operator*=(const float3x3& m);
			float3x3 operator+(const float3x3& m) const;
			float3x3& operator+=(const float3x3& m);
			float3x3 operator-(const float3x3& m) const;
			float3x3& operator-=(const float3x3& m);
			float3x3& operator=(const float3x3& m);
			float3x3 operator+(const float f) const;
			float3x3& operator+=(const float f);
			float3x3 operator-(const float f) const;
			float3x3& operator-=(const float f);
			float3x3 operator*(const float f) const;
			float3x3& operator*=(const float f);
			float3x3 operator/(const float f) const;
			float3x3& operator/=(const float f);
			float3x3& operator=(const float f);
			float3x3 operator-() const;
			bool operator==(float3x3& m);
			bool operator!=(float3x3& m);
			bool isNear(float3x3& m, float eps);
		};

		class float4x4
		{
			float mat[4][4];

		public:
			explicit float4x4();
			explicit float4x4(const float f);
			explicit float4x4(const float* const m);
			explicit float4x4(const float _00, const float _01, const float _02, const float _03,
				const float _10, const float _11, const float _12, const float _13,
				const float _20, const float _21, const float _22, const float _23,
				const float _30, const float _31, const float _32, const float _33);
			explicit float4x4(const float2x2& m);
			explicit float4x4(const float3x3& m);
			float4x4(const float4x4& m);
			static float4x4 Identity();
			static float4x4 Scaling(const float x, const float y, const float z);
			static float4x4 Scaling(const float3 s);
			static float4x4 Translation(const float x, const float y, const float z);
			static float4x4 Translation(const float3 t);
			static float4x4 RotationX(const float a);
			static float4x4 RotationY(const float a);
			static float4x4 RotationZ(const float a);
			static float4x4 Rotation(const float pitch, const float yaw, const float roll);
			static float4x4 Rotation(const float3 r);
			static float4x4 RotationAxis(const float3 axis, const float a);
			static float4x4 RotationNormal(const float3 n, const float a);
			static float4x4 RotationCamera(const float px, const float py, const float pz, const float rx, const float ry, const float rz);
			static float4x4 RotationCamera(const float3 p, const float3 r);
			static float4x4 ScalingRotationTranslation(const float sx, const float sy, const float sz,
				const float pitch, const float yaw, const float roll,
				const float tx, const float ty, const float tz);
			static float4x4 ScalingRotationTranslation(const float3 s, const float3 r, const float3 t);
			static float4x4 RotationTranslation(const float pitch, const float yaw, const float roll,
				const float tx, const float ty, const float tz);
			static float4x4 RotationTranslation(const float3 r, const float3 t);
			static float4x4 ScalingTranslation(const float sx, const float sy, const float sz,
				const float tx, const float ty, const float tz);
			static float4x4 ScalingTranslation(const float3 s, const float3 t);
			static float4x4 ScalingRotation(const float sx, const float sy, const float sz,
				const float pitch, const float yaw, const float roll);
			static float4x4 ScalingRotation(const float3 s, const float3 r);
			static float4x4 PerspectiveFOV(const float fov, const float screenAspect, const float screenNear, const float screenDepth);
			static float4x4 Orthographic(const float viewWidth, const float viewHeight, const float screenNear, const float screenDepth);
			static float4x4 LookTo(const float3 eye, const float3 direction, const float3 up);
			static float4x4 LookAt(const float3 eye, const float3 focus, const float3 up);

			float operator()(const int row, const int column) const;
			float& operator()(const int row, const int column);
			float4 operator*(const float4 v) const;
			explicit operator float2x2() const;
			explicit operator float3x3() const;
			float Determinant() const;
			void Invert();
			float4x4 Inverse() const;
			void Transpose();
			float4x4 Transposed() const;
			float4x4 operator*(const float4x4& m)const;
			float4x4& operator*=(const float4x4& m);
			float4x4 operator+(const float4x4& m) const;
			float4x4& operator+=(const float4x4& m);
			float4x4 operator-(const float4x4& m) const;
			float4x4& operator-=(const float4x4& m);
			float4x4& operator=(const float4x4& m);
			float4x4 operator+(const float f) const;
			float4x4& operator+=(const float f);
			float4x4 operator-(const float f) const;
			float4x4& operator-=(const float f);
			float4x4 operator*(const float f) const;
			float4x4& operator*=(const float f);
			float4x4 operator/(const float f) const;
			float4x4& operator/=(const float f);
			float4x4& operator=(const float f);
			float4x4 operator-() const;
			bool operator==(float4x4& m);
			bool operator!=(float4x4& m);
			bool isNear(float4x4& m, float eps);
		};

		bool isNear(float a, float b, float eps = EPS);
		float3 Transform(float4x4& m, float3 v);
		float3x3 NormalToRotationMatrix(float3 n);

		float2 operator+(const float f, const float2 v);
		float3 operator+(const float f, const float3 v);
		float4 operator+(const float f, const float4 v);
		quaternion operator+(const float f, const quaternion v);
		float2x2 operator+(const float f, const float2x2& m);
		float3x3 operator+(const float f, const float3x3& m);
		float4x4 operator+(const float f, const float4x4& m);

		float2 operator-(const float f, const float2 v);
		float3 operator-(const float f, const float3 v);
		float4 operator-(const float f, const float4 v);
		quaternion operator-(const float f, const quaternion q);
		float2x2 operator-(const float f, const float2x2& m);
		float3x3 operator-(const float f, const float3x3& m);
		float4x4 operator-(const float f, const float4x4& m);

		float2 operator*(const float f, const float2 v);
		float3 operator*(const float f, const float3 v);
		float4 operator*(const float f, const float4 v);
		quaternion operator*(const float f, const quaternion q);
		float2x2 operator*(const float f, const float2x2& m);
		float3x3 operator*(const float f, const float3x3& m);
		float4x4 operator*(const float f, const float4x4& m);

		std::ostream& operator<<(std::ostream& os, const float2& v);
		std::ostream& operator<<(std::ostream& os, const float3& v);
		std::ostream& operator<<(std::ostream& os, const float4& v);
		std::ostream& operator<<(std::ostream& os, const float2x2& m);
		std::ostream& operator<<(std::ostream& os, const float3x3& m);
		std::ostream& operator<<(std::ostream& os, const float4x4& m);

		std::istream& operator>>(std::istream& is, float2& v);
		std::istream& operator>>(std::istream& is, float3& v);
		std::istream& operator>>(std::istream& is, float4& v);
		std::istream& operator>>(std::istream& is, float2x2& m);
		std::istream& operator>>(std::istream& is, float3x3& m);
		std::istream& operator>>(std::istream& is, float4x4& m);

		std::wostream& operator<<(std::wostream& os, const float2& v);
		std::wostream& operator<<(std::wostream& os, const float3& v);
		std::wostream& operator<<(std::wostream& os, const float4& v);
		std::wostream& operator<<(std::wostream& os, const float2x2& m);
		std::wostream& operator<<(std::wostream& os, const float3x3& m);
		std::wostream& operator<<(std::wostream& os, const float4x4& m);

		std::wistream& operator>>(std::wistream& is, float2& v);
		std::wistream& operator>>(std::wistream& is, float3& v);
		std::wistream& operator>>(std::wistream& is, float4& v);
		std::wistream& operator>>(std::wistream& is, float2x2& m);
		std::wistream& operator>>(std::wistream& is, float3x3& m);
		std::wistream& operator>>(std::wistream& is, float4x4& m);
	}
}