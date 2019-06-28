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
				Assert::IsTrue(plain.getNormal().isZeroVector() && plain.getDistance() == 0.0, L"empty ctor");
			} {
				double3 n(1.0, 2.0, 3.0);
				double d = 4.0;
				n.Normalize();
				Plain3D plain(n, d);
				Assert::IsTrue(plain.getNormal() == n && plain.getDistance() == d, L"double3, double ctor");
			}
		}
		TEST_METHOD(IsPointOn_Test)
		{
			double3x3 rotation = double3x3::Rotation(1.0, 2.0, 3.0);
			Plain3D plain(rotation * double3(1.0, 0.0, 0.0), 1.0);
			double3 p_on = rotation * double3(1.0, 3.0, 2.0);
			double3 p_off = rotation * double3(2.0, 3.0, 2.0);

			Assert::IsTrue(plain.IsPointOn(p_on), L"Point on plain");
			Assert::IsFalse(plain.IsPointOn(p_off), L"Point not on plain");
		}
		TEST_METHOD(IsPointBelow_Test)
		{
			double3x3 rotation = double3x3::Rotation(1.0, 2.0, 3.0);
			Plain3D plain(rotation * double3(1.0, 0.0, 0.0), 1.0);
			double3 p_below = rotation * double3(0.5f, 3.0, 2.0);
			double3 p_over = rotation * double3(2.0, 3.0, 2.0);

			Assert::IsTrue(plain.IsPointBelow(p_below), L"Point below plain");
			Assert::IsFalse(plain.IsPointBelow(p_over), L"Point not below plain");
		}
		TEST_METHOD(IsPointOver_Test)
		{
			double3x3 rotation = double3x3::Rotation(1.0, 2.0, 3.0);
			Plain3D plain(rotation * double3(1.0, 0.0, 0.0), 1.0);
			double3 p_below = rotation * double3(0.5f, 3.0, 2.0);
			double3 p_over = rotation * double3(2.0, 3.0, 2.0);

			Assert::IsTrue(plain.IsPointOver(p_over), L"Point over plain");
			Assert::IsFalse(plain.IsPointOver(p_below), L"Point not over plain");
		}
		TEST_METHOD(Distance_Test)
		{
			double3x3 rotation = double3x3::Rotation(1.0, 2.0, 3.0);
			Plain3D plain(rotation * double3(1.0, 0.0, 0.0), 1.0);
			double3 p1 = rotation * double3(0.5, 3.0, 2.0);
			double3 p2 = rotation * double3(2.0, 3.0, 2.0);

			Assert::IsTrue(isNear(plain.Distance(p1), -0.5), L"Negative");
			Assert::IsTrue(isNear(plain.Distance(p2), 1.0), L"Positive");
		}
		TEST_METHOD(DirectionalDistance_Test)
		{
			double3x3 rotation = double3x3::Rotation(1.0, 2.0, 3.0);
			Plain3D plain(rotation * double3(1.0, 0.0, 0.0), 2.0);
			double3 d = rotation * double3(-1.1f, 1.3f, -0.9f);
			double3 p = rotation * double3(0.5f, 3.0, 2.0);
			Assert::IsTrue(isNear(plain.DirectionalDistance(p, d), (0.5f - 2.0) / 1.1f), L"Below, negative distance");

			p = rotation * double3(2.4f, 3.0, 2.0);
			Assert::IsTrue(isNear(plain.DirectionalDistance(p, d), (2.4f - 2.0) / 1.1f), L"Above, positive distance");

			d = rotation * double3(1.1f, 1.3f, -0.9f);
			p = rotation * double3(0.5f, 3.0, 2.0);
			Assert::IsTrue(isNear(plain.DirectionalDistance(p, d), (0.5f - 2.0) / -1.1f), L"Below, positive distance");

			p = rotation * double3(2.4f, 3.0, 2.0);
			Assert::IsTrue(isNear(plain.DirectionalDistance(p, d), (2.4f - 2.0) / -1.1f), L"Above, negative distance");
		}
		TEST_METHOD(TimeToGetClose)
		{
			double3x3 rotation = double3x3::Rotation(1.0, 2.0, 3.0);
			Plain3D plain(rotation * double3(1.0, 0.0, 0.0), 2.0);
			double3 d = rotation * double3(-1.1f, 1.3f, -0.9f);
			double3 p = rotation * double3(0.5f, 3.0, 2.0);
			Assert::IsTrue(isNear(plain.TimeToGetClose(p, d, 1.0), (0.5f - 1.0) / 1.1f), L"Below, negative distance");

			p = rotation * double3(3.4f, 3.0, 2.0);
			Assert::IsTrue(isNear(plain.TimeToGetClose(p, d, 1.0), (3.4f - 3.0) / 1.1f), L"Above, positive distance");

			d = rotation * double3(1.1f, 1.3f, -0.9f);
			p = rotation * double3(0.5f, 3.0, 2.0);
			Assert::IsTrue(isNear(plain.TimeToGetClose(p, d, 1.0), (0.5f - 1.0) / -1.1f), L"Below, positive distance");

			p = rotation * double3(3.4f, 3.0, 2.0);
			Assert::IsTrue(isNear(plain.TimeToGetClose(p, d, 1.0), (3.4f - 3.0) / -1.1f), L"Above, negative distance");
		}
	};
}
