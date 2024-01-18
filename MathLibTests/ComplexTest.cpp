#include "pch.h"
#define _USE_MATH_DEFINES
#include <math.h>
import Math;

namespace Math::Test
{
	void ExpectComplexHasReAndIm(double re, double im, const Complex& z)
	{
		EXPECT_DOUBLE_EQ(re, z.Re());
		EXPECT_DOUBLE_EQ(im, z.Im());
		EXPECT_DOUBLE_EQ(sqrt(re*re + im*im), z.Mod());
		EXPECT_DOUBLE_EQ(atan2(im, re), z.Arg());
	}

	void ExpectComplexHasModAndArg(double mod, double arg, const Complex& z)
	{
		EXPECT_DOUBLE_EQ(mod * cos(arg), z.Re());
		EXPECT_DOUBLE_EQ(mod * sin(arg), z.Im());
		EXPECT_DOUBLE_EQ(mod, z.Mod());
		EXPECT_DOUBLE_EQ(arg, z.Arg());
	}

	void ExpectComplexAreEqual(const Complex& z1, const Complex& z2)
	{
		EXPECT_DOUBLE_EQ(z1.Re(), z2.Re());
		EXPECT_DOUBLE_EQ(z1.Im(), z2.Im());
		EXPECT_DOUBLE_EQ(z1.Mod(), z2.Mod());
		EXPECT_DOUBLE_EQ(z1.Arg(), z1.Arg());
	}

	void ExpectComplexHaveDifferentSign(const Complex& z1, const Complex& z2)
	{
		ExpectComplexHasReAndIm(0, 0, z1 + z2);
	}

	void ExpectZ2IsReciprocalForZ1(const Complex& z1, const Complex& z2)
	{
		ExpectComplexHasModAndArg(1, 0, z1 * z2);
	}
	TEST(ComplexTest, TestDefaultConstructor) {
		Complex z;
		ExpectComplexHasReAndIm(0, 0, z);
	}

	TEST(ComplexTest, TestConversionConstructor) {
		Complex z = 1;
		ExpectComplexHasReAndIm(1, 0, z);
	}

	TEST(ComplexTest, TestConversionConstructor2) {
		Complex z = { 1, 1 };
		ExpectComplexHasReAndIm(1, 1, z);
	}

	TEST(ComplexTest, TestCreateFromAlgebraicForm) {
		Complex z1 = Complex::FromAlgebraicForm(1, 5);
		ExpectComplexHasReAndIm(1, 5, z1);
	}

	TEST(ComplexTest, TestCreateFromExponentialForm) {
		Complex z1 = Complex::FromExponentialForm(2, M_PI_4);
		ExpectComplexHasModAndArg(2, M_PI_4, z1);
	}

	TEST(ComplexTest, TestExplicitCastToDouble) {
		Complex z1 = Complex::FromAlgebraicForm(1, 5);
		double x1 = static_cast<double>(z1);
		EXPECT_DOUBLE_EQ(1, x1);
	}
	TEST(ComplexTest, TestUnaryMinus) {
		Complex z1 = Complex::FromAlgebraicForm(1, 1);

		Complex z2 = -z1;

		auto isSame = std::is_same_v<Complex, decltype(-z1)>;
		EXPECT_TRUE(isSame);
		ExpectComplexHasReAndIm(1, 1, z1);
		ExpectComplexHasReAndIm(-1, -1, z2);
	}
	TEST(ComplexTest, TestPrefixIncrement) {
		Complex z1 = Complex::FromAlgebraicForm( 1, 1 );
		
		Complex z2 = ++z1;

		auto isSame = std::is_same_v<Complex&, decltype(++z1)>;
		EXPECT_TRUE(isSame);
		ExpectComplexHasReAndIm(2, 1, z1);
		ExpectComplexHasReAndIm(2, 1, z2);
	}

	TEST(ComplexTest, TestPostfixIncrement) {
		Complex z1 = Complex::FromAlgebraicForm( 1, 1 );
		
		Complex z2 = z1++;

		auto isSame = std::is_same_v<Complex, decltype(z1++)>;
		EXPECT_TRUE(isSame);
		ExpectComplexHasReAndIm(2, 1, z1);
		ExpectComplexHasReAndIm(1, 1, z2);
	}

	TEST(ComplexTest, TestPrefixDecrement) {
		Complex z1 = Complex::FromAlgebraicForm( 2, 1 );
		
		Complex& z2 = --z1;

		auto isSame = std::is_same_v<Complex&, decltype(--z1)>;
		EXPECT_TRUE(isSame);
		ExpectComplexHasReAndIm(1, 1, z1);
		ExpectComplexHasReAndIm(1, 1, z2);
	}

	TEST(ComplexTest, TestPostfixDecrement) {
		Complex z1 = Complex::FromAlgebraicForm( 2, 1 );
		
		Complex z2 = z1--;

		auto isSame = std::is_same_v<Complex, decltype(z1--)>;
		EXPECT_TRUE(isSame);
		ExpectComplexHasReAndIm(1, 1, z1);
		ExpectComplexHasReAndIm(2, 1, z2);
	}

	TEST(ComplexTest, TestAddAndAssign) {
		Complex z1 = Complex::FromAlgebraicForm( 1, 1 );
		
		Complex z2 = z1 += Complex::FromAlgebraicForm( 1, 1 );

		auto isSame = std::is_same_v<Complex&, decltype(z1 += Complex::FromAlgebraicForm(1, 1))>;
		EXPECT_TRUE(isSame);
		ExpectComplexHasReAndIm(2, 2, z1);
		ExpectComplexHasReAndIm(2, 2, z2);
	}

	TEST(ComplexTest, TestSubAndAssign) {
		Complex z1 = Complex::FromAlgebraicForm( 2, 2 );
		
		Complex z2 = z1 -= Complex::FromAlgebraicForm( 1, 1 );

		auto isSame = std::is_same_v<Complex&, decltype(z1 -= Complex::FromAlgebraicForm(1, 1))> ;
		EXPECT_TRUE(isSame);
		ExpectComplexHasReAndIm(1, 1, z1);
		ExpectComplexHasReAndIm(1, 1, z2);
	}

	TEST(ComplexTest, TestMulAndAssign) {
		Complex z1 = Complex::FromExponentialForm(2,0);
		
		Complex z2 = z1 *= Complex::FromExponentialForm(2, M_PI_4);

		auto isSame = std::is_same_v<Complex&, decltype(z1 *= Complex::FromExponentialForm(2, M_PI_4))>;
		EXPECT_TRUE(isSame);
		ExpectComplexHasModAndArg(4, M_PI_4, z1);
		ExpectComplexHasModAndArg(4, M_PI_4, z2);
	}

	TEST(ComplexTest, TestDivAndAssign) {
		Complex z1 = Complex::FromExponentialForm(8, M_PI_2);
		
		Complex z2 = z1 /= Complex::FromExponentialForm(2, M_PI_4);

		auto isSame = std::is_same_v<Complex&, decltype(z1 /= Complex::FromExponentialForm(2, M_PI_4))>;
		EXPECT_TRUE(isSame);
		ExpectComplexHasModAndArg(4, M_PI_4, z1);
		ExpectComplexHasModAndArg(4, M_PI_4, z2);
	}

	TEST(ComplexTest, TestAdd) {
		Complex z1 = Complex::FromAlgebraicForm(1, 1);
		Complex z2 = Complex::FromAlgebraicForm(1, 1);
		
		Complex z = z1 + z2;

		auto isSame = std::is_same_v<Complex, decltype(z1 + z2)>;
		EXPECT_TRUE(isSame);
		ExpectComplexHasReAndIm(1, 1, z1);
		ExpectComplexHasReAndIm(1, 1, z2);
		ExpectComplexHasReAndIm(2, 2, z);
	}

	TEST(ComplexTest, TestSub) {
		Complex z1 = Complex::FromAlgebraicForm( 2, 2 );
		Complex z2 = Complex::FromAlgebraicForm( 1, 1 );
		Complex z = z1 - z2;

		auto isSame = std::is_same_v<Complex, decltype(z1 - z2)>;
		EXPECT_TRUE(isSame);

		ExpectComplexHasReAndIm(2, 2, z1);
		ExpectComplexHasReAndIm(1, 1, z2);
		ExpectComplexHasReAndIm(1, 1, z);
	}
	TEST(ComplexTest, TestMul) {
		Complex z1 = Complex::FromExponentialForm(2, 0);
		Complex z2 = Complex::FromExponentialForm(2, M_PI_4);
		
		Complex z = z1 * z2;
		
		auto isSame = std::is_same_v<Complex, decltype(z1 * z2)>;
		EXPECT_TRUE(isSame);
		ExpectComplexHasModAndArg(2, 0, z1);
		ExpectComplexHasModAndArg(2, M_PI_4, z2);
		ExpectComplexHasModAndArg(4, M_PI_4, z);

	}
	TEST(ComplexTest, TestDiv) {
		Complex z1 = Complex::FromExponentialForm(8, M_PI_2);
		Complex z2 = Complex::FromExponentialForm(2, M_PI_4);
		
		Complex z = z1 / z2;
		
		auto isSame = std::is_same_v<Complex, decltype(z1 / z2)>;
		EXPECT_TRUE(isSame);
		ExpectComplexHasModAndArg(8, M_PI_2, z1);
		ExpectComplexHasModAndArg(2, M_PI_4, z2);
		ExpectComplexHasModAndArg(4, M_PI_4, z);
	}

	TEST(ComplexTest, TestIfAddIsCommutative) {
		Complex z1 = Complex::FromAlgebraicForm(8, 4);
		Complex z2 = Complex::FromAlgebraicForm(2, 6);

		ExpectComplexAreEqual(z1 + z2, z2 + z1);
	}

	TEST(ComplexTest, TestIfMulIsCommutative) {
		Complex z1 = Complex::FromExponentialForm(8, M_PI_2);
		Complex z2 = Complex::FromExponentialForm(2, M_PI_4);

		ExpectComplexAreEqual(z1 * z2, z2 * z1);
	}

	TEST(ComplexTest, TestIfSubIsNotCommutative) {
		Complex z1 = Complex::FromExponentialForm(8, M_PI_2);
		Complex z2 = Complex::FromExponentialForm(2, M_PI_4);

		ExpectComplexHaveDifferentSign(z1 - z2, z2 - z1);
		ExpectComplexHaveDifferentSign(z2 - z1, z1 - z2);
	}

	TEST(ComplexTest, TestIfDivIsNotCommutative) {
		Complex z1 = Complex::FromExponentialForm(8, M_PI_2);
		Complex z2 = Complex::FromExponentialForm(2, M_PI_4);

		ExpectZ2IsReciprocalForZ1(z1 / z2, z2 / z1);
		ExpectZ2IsReciprocalForZ1(z2 / z1, z1 / z2);
	}
	TEST(ComplexTest, TestComplexWithDoubleOperations) {
		double x1 = 2;
		Complex z1 = Complex::FromAlgebraicForm(2, 0);
		Complex z2 = Complex::FromAlgebraicForm(2, 4);
		Complex z3 = Complex::FromExponentialForm(8, M_PI_2);

		Complex sum1 = z2 + x1;
		Complex sum2 = x1 + z2;
		Complex sum3 = z1 + z2;
		ExpectComplexAreEqual(sum1, sum2);
		ExpectComplexAreEqual(sum1, sum3);

		Complex mul1 = z3 * x1;
		Complex mul2 = x1 * z3;
		Complex mul3 = z1 * z3;
		ExpectComplexAreEqual(mul1, mul2);
		ExpectComplexAreEqual(mul1, mul3);

		Complex sub1 = z2 - x1;
		Complex sub2 = z2 - z1;
		ExpectComplexAreEqual(sub1, sub2);

		Complex sub3 = x1 - z2;
		Complex sub4 = z1 - z2;
		ExpectComplexAreEqual(sub3, sub4);

		Complex div1 = z3 / x1;
		Complex div2 = z3 / z1;
		ExpectComplexAreEqual(div1, div1);

		Complex div3 = x1 / z3;
		Complex div4 = z1 / z3;
		ExpectComplexAreEqual(div3, div4);
	}

	TEST(ComplexTest, TestUserDefinedLiterals) {
		Complex z1 = 5 + 3.0i;
		ExpectComplexHasReAndIm(5, 3, z1);
	}
}