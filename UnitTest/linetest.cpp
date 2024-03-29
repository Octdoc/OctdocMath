#include "CppUnitTest.h"
#include "geometry3d.hpp"
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
				Line3Dd line;
				Assert::IsTrue(line.getPoint().isZeroVector() && line.getDirection().isZeroVector(), L"empty ctor");
			} {
				double3 p(1.0, 2.0, 3.0);
				double3 v(4.0, 5.0, 6.0);
				v.Normalize();
				Line3Dd line(p, v);
				Assert::IsTrue(line.getPoint() == p && line.getDirection() == v, L"double3, double ctor");
			} {
				double3 p(1.0, 2.0, 3.0);
				double3 v(4.0, 5.0, 6.0);
				Line3Dd line = Line3Dd::From2Points(p, p + v);
				v.Normalize();
				Assert::IsTrue(line.getPoint() == p && line.getDirection() == v, L"From2Points");
			}
		}
		TEST_METHOD(Distance_Tests)
		{
			double3x3 rotation = double3x3::Rotation(1.0, 2.0, 3.0);
			Line3Dd line(rotation * double3(3.0, -1.0, 0.0), rotation * double3(0.0, 1.0, 0.0));
			double3 p = rotation * double3(1.0, 0.0, 0.0);
			Assert::IsTrue(isNear(line.Distance(p), 2.0), L"Distance");
		}
		TEST_METHOD(DistanceSquare_Tests)
		{
			double3x3 rotation = double3x3::Rotation(1.0, 2.0, 3.0);
			Line3Dd line(rotation * double3(3.0, -1.0, 0.0), rotation * double3(0.0, 1.0, 0.0));
			double3 p = rotation * double3(1.0, 0.0, 0.0);
			Assert::IsTrue(isNear(line.DistanceSquare(p), 2.0 * 2.0), L"DistanceSquare");
		}
		TEST_METHOD(TimeToGetClose_Tests)
		{
			double3x3 rotation = double3x3::Rotation(1.0, 2.0, 3.0);
			rotation = double3x3::Identity();
			Line3Dd line(rotation * double3(4.0, -1.0, 0.0), rotation * double3(0.0, 0.0, 1.0));
			double3 p = rotation * double3(-2.0, -4.0, 0.0);
			double3 d = rotation * double3(1.0, 0.0, -0.8f);
			Assert::IsTrue(isNear(line.TimeToGetClose(p, d, 5.0), 2.0), L"TimeToGetClose");

			d = -d;
			Assert::IsTrue(isNear(line.TimeToGetClose(p, d, 5.0), -2.0), L"Negative");

			Assert::IsTrue(isnan(line.TimeToGetClose(p, d, 2.0)), L"Misses");
		}
	};
}
