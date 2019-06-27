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
				double3 p(1.0, 2.0, 3.0);
				Point3D point(p);
				Assert::IsTrue(point.p == p, L"double3, double ctor");
			}
		}	
		TEST_METHOD(Distance_Tests)
		{
			double3x3 rotation = double3x3::Rotation(1.0, 2.0, 3.0);
			Point3D point(rotation * double3(3.0, 0.0, 0.0));
			double3 p = rotation * double3(1.0, 0.0, 0.0);
			Assert::IsTrue(isNear(point.Distance(p), 2.0), L"Distance");
		}
		TEST_METHOD(DistanceSquare_Tests)
		{
			double3x3 rotation = double3x3::Rotation(1.0, 2.0, 3.0);
			Point3D point(rotation * double3(3.0, 0.0, 0.0));
			double3 p = rotation * double3(1.0, 0.0, 0.0);
			Assert::IsTrue(isNear(point.DistanceSquare(p), 2.0 * 2.0), L"Distance");
		}
		TEST_METHOD(TimeToGetClose_Tests)
		{
			double3x3 rotation = double3x3::Rotation(1.0, 2.0, 3.0);
			rotation = double3x3::Identity();
			Point3D point(rotation * double3(4.0, 0.0, 0.0));
			double3 p = rotation * double3(-2.0, -4.0, 0.0);
			double3 d = rotation * double3(1.0, 0.0, 0.0);
			Assert::IsTrue(isNear(point.TimeToGetClose(p, d, 5.0), 3.0), L"Positive");

			d = -d;
			Assert::IsTrue(isNear(point.TimeToGetClose(p, d, 5.0), -3.0), L"Negative");

			Assert::IsTrue(isnan(point.TimeToGetClose(p, d, 2.0)), L"Misses");
		}
	};
}
