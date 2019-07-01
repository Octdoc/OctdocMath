#include "CppUnitTest.h"
#include "linalg.hpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace octdoc::mth;

namespace UnitTest
{
	TEST_CLASS(Float2_Test)
	{
	public:
		TEST_METHOD(CTor_Tests)
		{
			{
				float2 v;
				Assert::IsTrue(v.x == 0.0f && v.y == 0.0f, L"empty ctor");
			} {
				float f = 213.0f;
				float2 v(f);
				Assert::IsTrue(v.x == f && v.y == f, L"float ctor");
			} {
				float fa[]{ 213.0f,  5.0f };
				float2 v(fa);
				Assert::IsTrue(v.x == fa[0] && v.y == fa[1], L"array ctor");
			} {
				float f1 = 213.0f, f2 = 5.0f;
				float2 v(f1, f2);
				Assert::IsTrue(v.x == f1 && v.y == f2, L"float float ctor");
			} {
				float2 c(2.0f, 3.0f);
				float2 v(c);
				Assert::IsTrue(v.x == c.x && v.y == c.y, L"copy ctor");
			} {
				float3 c(2.0f, 3.0f, 4.0f);
				float2 v(c);
				Assert::IsTrue(v.x == c.x && v.y == c.y, L"float3 ctor");
			} {
				float4 c(2.0f, 3.0f, 4.0f, 5.0f);
				float2 v(c);
				Assert::IsTrue(v.x == c.x && v.y == c.y, L"float4 ctor");
			}
		}
	};
}
