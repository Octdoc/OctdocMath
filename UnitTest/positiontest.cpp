#include "CppUnitTest.h"
#include "position.h"
#include <string>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace octdoc::mth;

namespace UnitTest
{
	TEST_CLASS(PositionTest)
	{
	public:
		TEST_METHOD(CTor_Test)
		{
			Position<float> p;
			Assert::IsTrue(p.position.isZeroVector() && p.rotation.isZeroVector() && (p.scale - float3(1)).isZeroVector());
		}
		TEST_METHOD(InverseTests)
		{
			Position<float> p;
			p.position = float3(1, 2, 3);
			p.rotation = float3(0.4, 0.2, 1.3);
			p.scale = float3(1.2, 0.2, 0.5);
			float4x4 m1, m2;

			m1 = p.GetPositionMatrix();
			m2 = p.GetPositionMatrixInv();
			Assert::IsTrue((m1 * m2).isNear(float4x4::Identity()), L"Position");

			m1 = p.GetRotationMatrix();
			m2 = p.GetRotationMatrixInv();
			Assert::IsTrue((m1 * m2).isNear(float4x4::Identity()), L"Rotation");

			m1 = p.GetScaleMatrix();
			m2 = p.GetScaleMatrixInv();
			Assert::IsTrue((m1 * m2).isNear(float4x4::Identity()), L"Scale");

			m1 = p.GetWorldMatrix();
			m2 = p.GetWorldMatrixInv();
			Assert::IsTrue((m1 * m2).isNear(float4x4::Identity()), L"World");
		}
	};
}