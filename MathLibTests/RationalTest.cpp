#include "pch.h"
#define _USE_MATH_DEFINES
#include <math.h>
import Math;

namespace Math::Test
{
	void ExpectRationalHasNominatorAndDenominator(int nominator, int denominator, const Rational& r)
	{
		EXPECT_EQ(nominator, r.Nominator());
		EXPECT_EQ(denominator, r.Denominator());
	}

	void ExpectRationalAreEqual(const Rational& r1, const Rational& r2)
	{
		EXPECT_EQ(r1.Nominator(), r2.Nominator());
		EXPECT_EQ(r1.Denominator(), r2.Denominator());
	}

	void ExpectRationalHaveDifferentSign(const Rational& r1, const Rational& r2)
	{
		ExpectRationalAreEqual({ 0, r1.Denominator() }, r1 + r2);
	}

	void ExpectR2IsReciprocalForR1(const Rational& r1, const Rational& r2)
	{
		ExpectRationalAreEqual(1, r1 * r2);
	}
	TEST(MathAlgorithmsTest, TestGCD) {
		EXPECT_EQ(2, FindGreatestCommonDivisor(2, 4));
		EXPECT_EQ(2, FindGreatestCommonDivisor(4, 2));
		EXPECT_EQ(6, FindGreatestCommonDivisor(6, 12));
		EXPECT_EQ(6, FindGreatestCommonDivisor(-6, 12));
		EXPECT_EQ(6, FindGreatestCommonDivisor(6, -12));
		EXPECT_EQ(6, FindGreatestCommonDivisor(-6, -12));
		EXPECT_EQ(1, FindGreatestCommonDivisor(1, 7));
		EXPECT_EQ(7, FindGreatestCommonDivisor(0, 7));
	}

	TEST(MathAlgorithmsTest, TestLCM) {
		EXPECT_EQ(4, FindLeastCommonMultiple(2, 4));
		EXPECT_EQ(7, FindLeastCommonMultiple(1, 7));
		EXPECT_EQ(21, FindLeastCommonMultiple(3, 7));
		EXPECT_EQ(12, FindLeastCommonMultiple(4, 6));
		EXPECT_EQ(12, FindLeastCommonMultiple(-4, 6));
		EXPECT_EQ(12, FindLeastCommonMultiple(4, -6));
		EXPECT_EQ(12, FindLeastCommonMultiple(-4, -6));
	}
	TEST(RationalTest, TestDefaultInitialization) {
		Rational r;
		ExpectRationalHasNominatorAndDenominator(0, 1, r);
	}

	TEST(RationalTest, TestDirectInitialization) {
		Rational r(1, 4);
		ExpectRationalHasNominatorAndDenominator(1, 4, r);
	}

	TEST(RationalTest, TestListInitialization) {
		Rational r{ 1, 4 };
		ExpectRationalHasNominatorAndDenominator(1, 4, r);
	}
	TEST(RationalTest, TestCopyInitialization) {
		Rational r = 1;
		ExpectRationalHasNominatorAndDenominator(1, 1, r);
	}

	TEST(RationalTest, TestCopyListInitialization) {
		Rational r = { 1, 4 };
		ExpectRationalHasNominatorAndDenominator(1, 4, r);
	}

	TEST(RationalTest, TestSignNormalization) {
		Rational r1 = { -1, 4 };
		Rational r2 = { 1, -4 };
		Rational r3 = { -1, -4 };
		Rational r4 = { 1, 4 };
		ExpectRationalHasNominatorAndDenominator(-1, 4, r1);
		ExpectRationalHasNominatorAndDenominator(-1, 4, r2);
		ExpectRationalHasNominatorAndDenominator(1, 4, r3); 
		ExpectRationalHasNominatorAndDenominator(1, 4, r4);
	}

	TEST(RationalTest, TestNormalization) {
		Rational r1 = { 1, 2 };
		Rational r2 = { 2, -4 };
		Rational r3 = { -3, -6 };
		Rational r4 = { 33, 66 };
		ExpectRationalHasNominatorAndDenominator(1, 2, r1);
		ExpectRationalHasNominatorAndDenominator(-1, 2, r2);
		ExpectRationalHasNominatorAndDenominator(1, 2, r3);
		ExpectRationalHasNominatorAndDenominator(1, 2, r4);
	}

	TEST(RationalTest, TestExplicitCastToDouble) {
		Rational r1(1, 5);
		double x1 = static_cast<double>(r1);
		EXPECT_DOUBLE_EQ(0.2, x1);
	}
	TEST(RationalTest, TestUnaryMinus) {
		Rational r1(1, 2);

		Rational r2 = -r1;

		auto isSame = std::is_same_v<Rational, decltype(-r1)>;
		EXPECT_TRUE(isSame);
		ExpectRationalHasNominatorAndDenominator(1, 2, r1);
		ExpectRationalHasNominatorAndDenominator(-1, 2, r2);
	}

	TEST(RationalTest, TestPrefixIncrement) {
		Rational r1(1, 2);

		Rational r2 = ++r1;

		auto isSame = std::is_same_v<Rational&, decltype(++r1)>;
		EXPECT_TRUE(isSame);
		ExpectRationalHasNominatorAndDenominator(3, 2, r1);
		ExpectRationalHasNominatorAndDenominator(3, 2, r2);
	}

	TEST(RationalTest, TestPostfixIncrement) {
		Rational r1(1, 2);

		Rational r2 = r1++;

		auto isSame = std::is_same_v<Rational, decltype(r1++)>;
		EXPECT_TRUE(isSame);
		ExpectRationalHasNominatorAndDenominator(3, 2, r1);
		ExpectRationalHasNominatorAndDenominator(1, 2, r2);
	}

	TEST(RationalTest, TestPrefixDecrement) {
		Rational r1(3, 2);

		Rational r2 = --r1;

		auto isSame = std::is_same_v<Rational&, decltype(--r1)>;
		EXPECT_TRUE(isSame);
		ExpectRationalHasNominatorAndDenominator(1, 2, r1);
		ExpectRationalHasNominatorAndDenominator(1, 2, r2);
	}

	TEST(RationalTest, TestPostfixDecrement) {
		Rational r1(3, 2);

		Rational r2 = r1--;

		auto isSame = std::is_same_v<Rational, decltype(r1--)>;
		EXPECT_TRUE(isSame);
		ExpectRationalHasNominatorAndDenominator(1, 2, r1);
		ExpectRationalHasNominatorAndDenominator(3, 2, r2);
	}

	TEST(RationalTest, TestAddAndAssign) {
		Rational r1(1, 2);

		Rational r2 = r1 += Rational(1, 4);

		auto isSame = std::is_same_v<Rational&, decltype(r1 += Rational(1, 4))>;
		EXPECT_TRUE(isSame);
		ExpectRationalHasNominatorAndDenominator(3, 4, r1);
		ExpectRationalHasNominatorAndDenominator(3, 4, r2);
	}

	TEST(RationalTest, TestSubAndAssign) {
		Rational r1(3, 4);

		Rational r2 = r1 -= Rational(1, 4);

		auto isSame = std::is_same_v<Rational&, decltype(r1 -= Rational(1, 4))>;
		EXPECT_TRUE(isSame);
		ExpectRationalHasNominatorAndDenominator(1, 2, r1);
		ExpectRationalHasNominatorAndDenominator(1, 2, r2);
	}

	TEST(RationalTest, TestMulAndAssign) {
		Rational r1(1, 2);

		Rational r2 = r1 *= Rational(2, 3);

		auto isSame = std::is_same_v<Rational&, decltype(r1 *= Rational(2, 3))>;
		EXPECT_TRUE(isSame);
		ExpectRationalHasNominatorAndDenominator(1, 3, r1);
		ExpectRationalHasNominatorAndDenominator(1, 3, r2);
	}

	TEST(RationalTest, TestDivAndAssign) {
		Rational r1(5, 6);

		Rational r2 = r1 /= Rational(2, 3);

		auto isSame = std::is_same_v<Rational&, decltype(r1 /= Rational(2, 3))>;
		EXPECT_TRUE(isSame);
		ExpectRationalHasNominatorAndDenominator(5, 4, r1);
		ExpectRationalHasNominatorAndDenominator(5, 4, r2);
	}

	TEST(RationalTest, TestAdd) {
		Rational r1(1, 2);
		Rational r2(1, 4);

		Rational r = r1 + r2;

		auto isSame = std::is_same_v<Rational, decltype(r1 + r2)>;
		EXPECT_TRUE(isSame);
		ExpectRationalHasNominatorAndDenominator(1, 2, r1);
		ExpectRationalHasNominatorAndDenominator(1, 4, r2);
		ExpectRationalHasNominatorAndDenominator(3, 4, r);
	}

	TEST(RationalTest, TestSub) {
		Rational r1(3, 4);
		Rational r2(1, 4);
		Rational r = r1 - r2;

		auto isSame = std::is_same_v<Rational, decltype(r1 - r2)>;
		EXPECT_TRUE(isSame);

		ExpectRationalHasNominatorAndDenominator(3, 4, r1);
		ExpectRationalHasNominatorAndDenominator(1, 4, r2);
		ExpectRationalHasNominatorAndDenominator(1, 2, r);
	}

	TEST(RationalTest, TestMul) {
		Rational r1(1, 2);
		Rational r2(2, 3);

		Rational r = r1 * r2;

		auto isSame = std::is_same_v<Rational, decltype(r1* r2)>;
		EXPECT_TRUE(isSame);
		ExpectRationalHasNominatorAndDenominator(1, 2, r1);
		ExpectRationalHasNominatorAndDenominator(2, 3, r2);
		ExpectRationalHasNominatorAndDenominator(1, 3, r);

	}

	TEST(RationalTest, TestDiv) {
		Rational r1(5, 6);
		Rational r2(2, 3);

		Rational r = r1 / r2;

		auto isSame = std::is_same_v<Rational, decltype(r1 / r2)>;
		EXPECT_TRUE(isSame);
		ExpectRationalHasNominatorAndDenominator(5, 6, r1);
		ExpectRationalHasNominatorAndDenominator(2, 3, r2);
		ExpectRationalHasNominatorAndDenominator(5, 4, r);
	}

	TEST(RationalTest, TestIfAddIsCommutative) {
		Rational r1(8, 4);
		Rational r2(2, 6);

		ExpectRationalAreEqual(r1 + r2, r2 + r1);
	}

	TEST(RationalTest, TestIfMulIsCommutative) {
		Rational r1(8, 4);
		Rational r2(2, 5);

		ExpectRationalAreEqual(r1 * r2, r2 * r1);
	}

	TEST(RationalTest, TestIfSubIsNotCommutative) {
		Rational r1(8, 4);
		Rational r2(2, 5);

		ExpectRationalHaveDifferentSign(r1 - r2, r2 - r1);
		ExpectRationalHaveDifferentSign(r2 - r1, r1 - r2);
	}

	TEST(RationalTest, TestIfDivIsNotCommutative) {
		Rational r1(8, 3);
		Rational r2(2, 5);

		ExpectR2IsReciprocalForR1(r1 / r2, r2 / r1);
		ExpectR2IsReciprocalForR1(r2 / r1, r1 / r2);
	}

	TEST(RationalTest, TestRationalWithIntOperations) {
		int x1 = 2;
		Rational r1 = 2;
		Rational r2(2, 4);

		Rational sum1 = r2 + x1;
		Rational sum2 = x1 + r2;
		Rational sum3 = r1 + r2;
		ExpectRationalAreEqual(sum1, sum2);
		ExpectRationalAreEqual(sum1, sum3);

		Rational mul1 = r2 * x1;
		Rational mul2 = x1 * r2;
		Rational mul3 = r1 * r2;
		ExpectRationalAreEqual(mul1, mul2);
		ExpectRationalAreEqual(mul1, mul3);

		Rational sub1 = r2 - x1;
		Rational sub2 = r2 - r1;
		ExpectRationalAreEqual(sub1, sub2);

		Rational sub3 = x1 - r2;
		Rational sub4 = r1 - r2;
		ExpectRationalAreEqual(sub3, sub4);

		Rational div1 = r2 / x1;
		Rational div2 = r2 / r1;
		ExpectRationalAreEqual(div1, div1);

		Rational div3 = x1 / r2;
		Rational div4 = r1 / r2;
		ExpectRationalAreEqual(div3, div4);
	}

	TEST(RationalTest, TestEqualNumberComparison) {
		Rational r1(1, 2);
		Rational r2(1, 4);

		EXPECT_TRUE(r1 != r2);
		EXPECT_TRUE(r1 > r2);
		EXPECT_TRUE(r1 >= r2);
		EXPECT_FALSE(r1 < r2);
		EXPECT_FALSE(r1 <= r2);
		EXPECT_FALSE(r1 == r2);

		EXPECT_TRUE(r2 != r1);
		EXPECT_FALSE(r2 > r1);
		EXPECT_FALSE(r2 >= r1);
		EXPECT_TRUE(r2 < r1);
		EXPECT_TRUE(r2 <= r1);
		EXPECT_FALSE(r2 == r1);
	}

	TEST(RationalTest, TestEqualNotEqualNumberComparison) {
		Rational r1(1, 2);
		Rational r2(2, 4);

		EXPECT_FALSE(r1 != r2);
		EXPECT_FALSE(r1 > r2);
		EXPECT_TRUE(r1 >= r2);
		EXPECT_FALSE(r1 < r2);
		EXPECT_TRUE(r1 <= r2);
		EXPECT_TRUE(r1 == r2);

		EXPECT_FALSE(r2 != r1);
		EXPECT_FALSE(r2 > r1);
		EXPECT_TRUE(r2 >= r1);
		EXPECT_FALSE(r2 < r1);
		EXPECT_TRUE(r2 <= r1);
		EXPECT_TRUE(r2 == r1);
	}
}