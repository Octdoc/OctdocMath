#include "CppUnitTest.h"
#include "geometry3d.h"
#include <string>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace octdoc::mth;

namespace UnitTest
{
	TEST_CLASS(PointTest)
	{
	public:
		TEST_METHOD(CTor_Tests)
		{
			{
				Point3D point;
				Assert::IsTrue(point.p.isZeroVector(), L"empty ctor");
			} {
				float3 p(1.0f, 2.0f, 3.0f);
				Point3D point(p);
				Assert::IsTrue(point.p == p, L"float3, float ctor");
			}
		}	
		TEST_METHOD(Distance_Tests)
		{
			float3x3 rotation = float3x3::Rotation(1.0f, 2.0f, 3.0f);
			Point3D point(rotation * float3(3.0f, 0.0f, 0.0f));
			float3 p = rotation * float3(1.0f, 0.0f, 0.0f);
			Assert::IsTrue(isNear(point.Distance(p), 2.0f), L"Distance");
		}
		TEST_METHOD(DistanceSquare_Tests)
		{
			float3x3 rotation = float3x3::Rotation(1.0f, 2.0f, 3.0f);
			Point3D point(rotation * float3(3.0f, 0.0f, 0.0f));
			float3 p = rotation * float3(1.0f, 0.0f, 0.0f);
			Assert::IsTrue(isNear(point.DistanceSquare(p), 2.0f * 2.0f), L"Distance");
		}
		TEST_METHOD(TimeToGetClose_Tests)
		{
			float3x3 rotation = float3x3::Rotation(1.0f, 2.0f, 3.0f);
			rotation = float3x3::Identity();
			Point3D point(rotation * float3(4.0f, 0.0f, 0.0f));
			float3 p = rotation * float3(-2.0f, -4.0f, 0.0f);
			float3 d = rotation * float3(1.0f, 0.0f, 0.0f);
			Assert::IsTrue(isNear(point.TimeToGetClose(p, d, 5.0f), 3.0f), L"Positive");

			d = -d;
			Assert::IsTrue(isNear(point.TimeToGetClose(p, d, 5.0f), -3.0f), L"Negative");

			Assert::IsTrue(isnan(point.TimeToGetClose(p, d, 2.0f)), L"Misses");
		}
	};
}
