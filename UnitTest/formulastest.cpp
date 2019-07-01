#include "CppUnitTest.h"
#include "linalg.hpp"
#include "formulas.hpp"
#include <string>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace octdoc::mth;

namespace UnitTest
{
	TEST_CLASS(FormulasTest)
	{
	public:
		TEST_METHOD(Quadratic_Tests)
		{
			float a = 2.0f;
			float b = 1.0f;
			float c = -6.0f;
			float s1, s2;
			Assert::IsTrue(Quadratic(a, b, c, s1, s2) == 2, L"2 solutions");
			Assert::IsTrue(isNear(s1, -2.0f), L"1/2 solution");
			Assert::IsTrue(isNear(s2, 1.5f), L"2/2 solution");

			a = 2.25f;
			b = -9.0f;
			c = 9.0f;
			Assert::IsTrue(Quadratic(a, b, c, s1, s2) == 1, L"1 solution");
			Assert::IsTrue(s1 == s2, L"Equal solutions");
			Assert::IsTrue(isNear(s1, 2.0f), L"1/1 solution");

			a = 2.25f;
			b = 1.0f;
			c = 3.0f;
			Assert::IsTrue(Quadratic(a, b, c, s1, s2) == 0, L"0 solution");
		}
	};
}
