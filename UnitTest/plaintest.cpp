#include "CppUnitTest.h"
#include "geometry3d.h"
#include <string>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace octdoc::mth;

namespace UnitTest
{
	TEST_CLASS(PlainTest)
	{
	public:
		TEST_METHOD(CTor_Tests)
		{
			{
				Plain3D plain;
				Assert::IsTrue(plain.n.isZeroVector() && plain.d == 0.0f, L"empty ctor");
			} {
				float3 n(1.0f, 2.0f, 3.0f);
				float d = 4.0f;
				Plain3D plain(n, d);
				Assert::IsTrue(plain.n == n && plain.d == d, L"float3, float ctor");
			}
		}
		TEST_METHOD(IsPointOn_Test)
		{
			float3x3 rotation = float3x3::Rotation(1.0f, 2.0f, 3.0f);
			Plain3D plain(rotation * float3(1.0f, 0.0f, 0.0f), 1.0f);
			float3 p_on = rotation * float3(1.0f, 3.0f, 2.0f);
			float3 p_off = rotation * float3(2.0f, 3.0f, 2.0f);

			Assert::IsTrue(plain.IsPointOn(p_on), L"Point on plain");
			Assert::IsFalse(plain.IsPointOn(p_off), L"Point not on plain");
		}
		TEST_METHOD(IsPointBelow_Test)
		{
			float3x3 rotation = float3x3::Rotation(1.0f, 2.0f, 3.0f);
			Plain3D plain(rotation * float3(1.0f, 0.0f, 0.0f), 1.0f);
			float3 p_below = rotation * float3(0.5f, 3.0f, 2.0f);
			float3 p_over = rotation * float3(2.0f, 3.0f, 2.0f);

			Assert::IsTrue(plain.IsPointBelow(p_below), L"Point below plain");
			Assert::IsFalse(plain.IsPointBelow(p_over), L"Point not below plain");
		}
		TEST_METHOD(IsPointOver_Test)
		{
			float3x3 rotation = float3x3::Rotation(1.0f, 2.0f, 3.0f);
			Plain3D plain(rotation * float3(1.0f, 0.0f, 0.0f), 1.0f);
			float3 p_below = rotation * float3(0.5f, 3.0f, 2.0f);
			float3 p_over = rotation * float3(2.0f, 3.0f, 2.0f);

			Assert::IsTrue(plain.IsPointOver(p_over), L"Point over plain");
			Assert::IsFalse(plain.IsPointOver(p_below), L"Point not over plain");
		}
		TEST_METHOD(Distance_Test)
		{
			float3x3 rotation = float3x3::Rotation(1.0f, 2.0f, 3.0f);
			Plain3D plain(rotation * float3(1.0f, 0.0f, 0.0f), 1.0f);
			float3 p1 = rotation * float3(0.5f, 3.0f, 2.0f);
			float3 p2 = rotation * float3(2.0f, 3.0f, 2.0f);

			Assert::IsTrue(isNear(plain.Distance(p1), -0.5f), L"Negative");
			Assert::IsTrue(isNear(plain.Distance(p2), 1.0f), L"Positive");
		}
		TEST_METHOD(DirectionalDistance_Test)
		{
			float3x3 rotation = float3x3::Rotation(1.0f, 2.0f, 3.0f);
			Plain3D plain(rotation * float3(1.0f, 0.0f, 0.0f), 2.0f);
			float3 d = rotation * float3(-1.1f, 1.3f, -0.9f);
			float3 p = rotation * float3(0.5f, 3.0f, 2.0f);
			Assert::IsTrue(isNear(plain.DirectionalDistance(p, d), (0.5f - 2.0f) / 1.1f), L"Below, negative distance");

			p = rotation * float3(2.4f, 3.0f, 2.0f);
			Assert::IsTrue(isNear(plain.DirectionalDistance(p, d), (2.4f - 2.0f) / 1.1f), L"Above, positive distance");

			d = rotation * float3(1.1f, 1.3f, -0.9f);
			p = rotation * float3(0.5f, 3.0f, 2.0f);
			Assert::IsTrue(isNear(plain.DirectionalDistance(p, d), (0.5f - 2.0f) / -1.1f), L"Below, positive distance");

			p = rotation * float3(2.4f, 3.0f, 2.0f);
			Assert::IsTrue(isNear(plain.DirectionalDistance(p, d), (2.4f - 2.0f) / -1.1f), L"Above, negative distance");
		}
		TEST_METHOD(TimeToGetClose)
		{
			float3x3 rotation = float3x3::Rotation(1.0f, 2.0f, 3.0f);
			Plain3D plain(rotation * float3(1.0f, 0.0f, 0.0f), 2.0f);
			float3 d = rotation * float3(-1.1f, 1.3f, -0.9f);
			float3 p = rotation * float3(0.5f, 3.0f, 2.0f);
			Assert::IsTrue(isNear(plain.TimeToGetClose(p, d, 1.0f), (0.5f - 1.0f) / 1.1f), L"Below, negative distance");

			p = rotation * float3(3.4f, 3.0f, 2.0f);
			Assert::IsTrue(isNear(plain.TimeToGetClose(p, d, 1.0f), (3.4f - 3.0f) / 1.1f), L"Above, positive distance");

			d = rotation * float3(1.1f, 1.3f, -0.9f);
			p = rotation * float3(0.5f, 3.0f, 2.0f);
			Assert::IsTrue(isNear(plain.TimeToGetClose(p, d, 1.0f), (0.5f - 1.0f) / -1.1f), L"Below, positive distance");

			p = rotation * float3(3.4f, 3.0f, 2.0f);
			Assert::IsTrue(isNear(plain.TimeToGetClose(p, d, 1.0f), (3.4f - 3.0f) / -1.1f), L"Above, negative distance");
		}
	};
}
