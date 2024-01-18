
#include<iostream>
#include<cmath>

import Math;
using namespace Math;

void funC()
{

	Complex ob0;
	std::cout << ob0 << std::endl;
	Complex ob1(1);
	std::cout << ob1 << std::endl;
	Complex ob3(1, 4);
	std::cout << ob3 << std::endl;
	ob0 = Complex::FromExponentialForm(4.47214, 1.10715);
	std::cout << ob0 << std::endl;
	ob0 = Complex::FromAlgebraicForm(2, 4);
	std::cout << ob0 << std::endl;
	std::cout << ob0.Re() << " " << ob0.Im() << " " << ob0.Mod() << " " << ob0.Arg() << std::endl;
	std::cout << (double)ob0 << std::endl;
	std::cout << -ob0 << std::endl;
	std::cout << ++ob0 << std::endl;
	std::cout << ob0++ << std::endl;
	std::cout << --ob0 << std::endl;
	std::cout << ob0-- << std::endl;
	std::cout << (ob0 -= ob3) << std::endl;
	std::cout << (ob0 += ob3) << std::endl;
	std::cout << (ob0 *= ob3) << std::endl;
	std::cout << (ob0 /= ob3) << std::endl;
	std::cout << (ob0 - ob1 + ob0 * ob3 / ob1) << std::endl;
	std::cout << FindGreatestCommonDivisor(1, 5) << std::endl;
	std::cout << FindLeastCommonMultiple(2, 7) << std::endl;
}

void funR()
{
	Rational ob0;
	std::cout << ob0 << std::endl;
	Rational ob1(1);
	std::cout << ob1 << std::endl;
	Rational ob3(1, 4);
	std::cout << ob3 << std::endl;
	std::cout << ob3.Nominator() << " " << ob3.Denominator() << std::endl;
	std::cout << (double)ob3 << std::endl;
	std::cout << -ob0 << std::endl;
	std::cout << ++ob0 << std::endl;
	std::cout << ob0++ << std::endl;
	std::cout << --ob0 << std::endl;
	std::cout << ob0-- << std::endl;
	std::cout << (ob0 -= ob3) << std::endl;
	std::cout << (ob0 += ob3) << std::endl;
	std::cout << (ob0 *= ob3) << std::endl;
	std::cout << (ob0 /= ob3) << std::endl;
	std::cout << (ob0 - ob1 + ob0 * ob3 / ob1) << std::endl;
	std::cout << (ob1 == ob3) << std::endl;
	std::cout << ob1 << " " << ob3 << std::endl;

	std::cout << (ob1 < ob3) << std::endl;
	std::cout << (ob1 > ob3) << std::endl;
	std::cout << (ob1 <= ob3) << std::endl;
	std::cout << (ob1 >= ob3) << std::endl;


}

int main()
{
	funC();
	funR();
	int u = 14;

	Complex num1 = f((Complex)u);
	Rational num2 = f((Rational)u);
	double num3 = f(u);
	std::cout << num1 << std::endl;
	std::cout << num2 << std::endl;
	std::cout << num3 << std::endl;
	return 0;



}