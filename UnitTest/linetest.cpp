#include "CppUnitTest.h"
#include "geometry3d.h"
#include <string>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace octdoc::mth;

namespace UnitTest
{
	TEST_CLASS(LineTest)
	{
	public:
		TEST_METHOD(CTor_Tests)
		{
			{
				Line3D line;
				Assert::IsTrue(line.p.isZeroVector() && line.v.isZeroVector(), L"empty ctor");
			} {
				float3 p(1.0f, 2.0f, 3.0f);
				float3 v(4.0f, 5.0f, 6.0f);
				Line3D line(p, v);
				Assert::IsTrue(line.p == p && line.v == v, L"float3, float ctor");
			}
		}
		TEST_METHOD(Distance_Tests)
		{
			float3x3 rotation = float3x3::Rotation(1.0f, 2.0f, 3.0f);
			Line3D line(rotation * float3(3.0f, -1.0f, 0.0f), rotation * float3(0.0f, 1.0f, 0.0f));
			float3 p = rotation * float3(1.0f, 0.0f, 0.0f);
			Assert::IsTrue(isNear(line.Distance(p), 2.0f), L"Distance");
		}
		TEST_METHOD(DistanceSquare_Tests)
		{
			float3x3 rotation = float3x3::Rotation(1.0f, 2.0f, 3.0f);
			Line3D line(rotation * float3(3.0f, -1.0f, 0.0f), rotation * float3(0.0f, 1.0f, 0.0f));
			float3 p = rotation * float3(1.0f, 0.0f, 0.0f);
			Assert::IsTrue(isNear(line.DistanceSquare(p), 2.0f * 2.0f), L"DistanceSquare");
		}
		TEST_METHOD(TimeToGetClose_Tests)
		{
			float3x3 rotation = float3x3::Rotation(1.0f, 2.0f, 3.0f);
			rotation = float3x3::Identity();
			Line3D line(rotation * float3(4.0f, -1.0f, 0.0f), rotation * float3(0.0f, 0.0f, 1.0f));
			float3 p = rotation * float3(-2.0f, -4.0f, 0.0f);
			float3 d = rotation * float3(1.0f, 0.0f, -0.8f);
			Assert::IsTrue(isNear(line.TimeToGetClose(p, d, 5.0f), 2.0f), L"TimeToGetClose");

			d = -d;
			Assert::IsTrue(isNear(line.TimeToGetClose(p, d, 5.0f), -2.0f), L"Negative");

			Assert::IsTrue(isnan(line.TimeToGetClose(p, d, 2.0f)), L"Misses");
		}
	};
}
