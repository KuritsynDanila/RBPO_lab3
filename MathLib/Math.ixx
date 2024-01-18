
#include <cmath>;
#include<iostream>;
export module Math;


export namespace Math {
	class Complex
	{
	public:
		Complex()
		{
			m_re = m_im = 0;
		}
		Complex(double a)
		{
			m_re = a;
			m_im = 0.0;
		}
		Complex(double a, double b)
		{
			m_re = a;
			m_im = b;
		}
		static Complex FromExponentialForm(double m_mod, double m_arg)
		{
			double m_re = m_mod * (cos(m_arg));
			double m_im = m_mod * sin(m_arg);
			return Complex(m_re, m_im);

		}
		static Complex FromAlgebraicForm(double m_re, double m_im)
		{
			return Complex(m_re, m_im);
		}
		double Re() const { return(m_re); }
		double Im() const { return(m_im); }
		double Mod() const { return(sqrt(m_re * m_re + m_im * m_im)); }
		double Arg() const { return(std::atan2(m_im, m_re)); }

		explicit operator double()
		{
			return m_re;
		}

		Complex operator-() { return Complex(-this->m_re, -this->m_im); }
		Complex& operator++() { this->m_re = this->m_re + 1; return *this; }
		Complex operator++(int peregruz) { Complex copy = *this; this->m_re = this->m_re + 1; return copy; }
		Complex& operator--() { this->m_re = this->m_re - 1; return *this; }
		Complex operator--(int peregruz) { Complex copy = *this; this->m_re = this->m_re - 1; return copy; }
		Complex& operator+=(Complex complex) 
		{ 
			this->m_re += complex.m_re;
			this->m_im += complex.m_im;
			return *this;
		}
		Complex& operator-=(Complex complex) 
		{
			this->m_re -= complex.m_re; 
			this->m_im -= complex.m_im;
			return *this;
		}
		Complex& operator*= (Complex x)
		{
			double pred_re = this->m_re * x.m_re - this->m_im * x.m_im;
			double pred_im = this->m_re * x.m_im + this->m_im * x.m_re;
			this->m_re = pred_re;
			this->m_im = pred_im;
			return *this;
		}
		Complex& operator/= (Complex x)
		{
			double pred_re = (this->m_re * x.m_re + this->m_im * x.m_im) / (x.m_re * x.m_re + x.m_im * x.m_im);
			double pred_im = (this->m_im * x.m_re - this->m_re * x.m_im) / (x.m_re * x.m_re + x.m_im * x.m_im);
			this->m_re = pred_re;
			this->m_im = pred_im;
			return *this;
		}
		friend Complex operator+(Complex lhs, Complex rhs);
		friend Complex operator-(Complex lhs, Complex rhs);
		friend Complex operator*(Complex lhs, Complex rhs);
		friend Complex operator/(Complex lhs, Complex rhs);
		friend Complex operator""i(long double Im);
		friend Complex operator""i(unsigned long long Im);
		friend std::ostream& operator<< (std::ostream& stream, const Complex complex);


	private:
		double m_re;
		double m_im;

	};
	Complex operator+(Complex lhs, Complex rhs)
	{
		double re = lhs.m_re + rhs.m_re;
		double im = lhs.m_im + rhs.m_im;
		return Complex(re, im);
	}
	Complex operator-(Complex lhs, Complex rhs)
	{
		double re = lhs.m_re - rhs.m_re;
		double im = lhs.m_im - rhs.m_im;
		return Complex(re, im);
	}
	Complex operator*(Complex lhs, Complex rhs)
	{
		double re = lhs.m_re * rhs.m_re - lhs.m_im * rhs.m_im;
		double im = lhs.m_re * rhs.m_im + lhs.m_im * rhs.m_re;
		return Complex(re, im);
	}
	Complex operator/(Complex lhs, Complex rhs)
	{
		double re = (lhs.m_re * rhs.m_re + lhs.m_im * rhs.m_im) / (rhs.m_re * rhs.m_re + rhs.m_im * rhs.m_im);
		double im = (lhs.m_im * rhs.m_re - lhs.m_re * rhs.m_im) / (rhs.m_re * rhs.m_re + rhs.m_im * rhs.m_im);
		return Complex(re, im);
	}
	Complex operator""i(long double Im) { return Complex(0, Im); }
	Complex operator""i(unsigned long long Im) { return Complex(0, Im); }

	std::ostream& operator<< (std::ostream& stream, const Complex complex)
	{
		if (complex.m_im >= 0) { return stream << complex.m_re << "+" << complex.m_im << "i"; }
		return stream << complex.m_re << complex.m_im << "i";
	}

	int FindGreatestCommonDivisor(int a, int b)
	{
		if (a < b)
		{
			int swap = a;
			a = b;
			b = swap;
		}
		int r;
		while (b != 0)
		{
			r = a % b;
			a = b;
			b = r;
		}
		return abs(a);
	}
	int FindLeastCommonMultiple(int x, int y)
	{
		return abs(x * y) / FindGreatestCommonDivisor(x, y);
	}

	class Rational
	{

	public:
		void fun()
		{


			int nod = FindGreatestCommonDivisor(m_nominator, m_denominator);
			m_nominator = m_nominator / nod;
			m_denominator = m_denominator / nod;
			if (m_denominator < 0)
			{
				m_nominator = -m_nominator;
				m_denominator = -m_denominator;
			}
		}
		Rational() { m_nominator = 0; m_denominator = 1; }
		Rational(int x, int y)
		{
			m_nominator = x;
			m_denominator = y;
			this->fun();
		}
		Rational(int x) { m_nominator = x; m_denominator = 1; }

		int Nominator() const { return m_nominator; }
		int Denominator() const { return m_denominator; }
		explicit  operator double() {
			return ((double)Nominator() / Denominator());
		}
		Rational operator- () { return Rational(-this->m_nominator, this->m_denominator); }
		Rational& operator++ () 
		{
			this->m_nominator += m_denominator;
			this->fun(); return *this;
		}
		Rational operator++ (int x) { 
			Rational star = *this;
			m_nominator += m_denominator; 
			this->fun(); 
			return star;
		}
		Rational& operator-- () { this->m_nominator -= m_denominator; this->fun(); return *this; }
		Rational operator-- (int x) { Rational star = *this; m_nominator -= m_denominator; this->fun(); return star; }
		Rational& operator+= (Rational x)
		{
			int no = m_nominator * x.m_denominator + m_denominator * x.m_nominator;
			int de = m_denominator * x.m_denominator;
			m_nominator = no;
			m_denominator = de;
			fun();
			return *this;
		}
		Rational& operator-= (Rational x)
		{
			int no = m_nominator * x.m_denominator - m_denominator * x.m_nominator;
			int de = m_denominator * x.m_denominator;
			m_nominator = no;
			m_denominator = de;
			fun();
			return *this;
		}
		Rational& operator*= (Rational x)
		{
			int no = m_nominator * x.m_nominator;
			int de = m_denominator * x.m_denominator;
			m_nominator = no;
			m_denominator = de;
			fun();
			return *this;
		}
		Rational& operator/= (Rational x)
		{
			int no = m_nominator * x.m_denominator;
			int de = m_denominator * x.m_nominator;
			m_nominator = no;
			m_denominator = de;
			fun();
			return *this;
		}
		friend Rational operator+ (Rational lhs, Rational rhs);
		friend Rational operator- (Rational lhs, Rational rhs);
		friend Rational operator* (Rational lhs, Rational rhs);
		friend Rational operator/ (Rational lhs, Rational rhs);
		friend bool operator== (Rational lhs, Rational rhs);
		friend bool operator<(Rational lhs, Rational rhs);
		friend bool operator>(Rational lhs, Rational rhs);
		friend bool operator<=(Rational lhs, Rational rhs);
		friend bool operator<=(Rational lhs, Rational rhs);

		friend std::ostream& operator<< (std::ostream& os, const Rational& rational);
	private:
		int m_nominator;
		int m_denominator;
	};
	Rational operator+ (Rational lhs, Rational rhs)
	{
		int no = lhs.m_nominator * rhs.m_denominator + lhs.m_denominator * rhs.m_nominator;
		int de = lhs.m_denominator * rhs.m_denominator;
		Rational now = Rational(no, de);
		now.fun();
		return now;
	}
	Rational operator- (Rational lhs, Rational rhs)
	{
		int no = lhs.m_nominator * rhs.m_denominator - lhs.m_denominator * rhs.m_nominator;
		int de = lhs.m_denominator * rhs.m_denominator;
		Rational now = Rational(no, de);
		now.fun();
		return now;
	}
	Rational operator* (Rational lhs, Rational rhs)
	{
		int no = lhs.m_nominator * rhs.m_nominator;
		int de = lhs.m_denominator * rhs.m_denominator;
		Rational now = Rational(no, de);
		now.fun();
		return now;
	}
	Rational operator/ (Rational lhs, Rational rhs)
	{
		int no = lhs.m_nominator * rhs.m_denominator;
		int de = lhs.m_denominator * rhs.m_nominator;
		Rational now = Rational(no, de);
		now.fun();
		return now;
	}
	bool operator== (Rational lhs, Rational rhs)
	{
		if (lhs.m_nominator == rhs.m_nominator && lhs.m_denominator == rhs.m_denominator)
			return true;
		else
			return false;
	}

	bool operator< (Rational lhs, Rational rhs)
	{
		return (double)lhs < (double)rhs;
	}
	bool operator> (Rational lhs, Rational rhs)
	{
		return (double)lhs > (double)rhs;
	}
	bool operator>= (Rational lhs, Rational rhs)
	{
		return (double)lhs >= (double)rhs;
	}

	bool operator<= (Rational lhs, Rational rhs)
	{
		return (double)lhs <= (double)rhs;
	}


	std::ostream& operator<< (std::ostream& os, const Rational& rational)
	{
		return os << rational.m_nominator << "/" << rational.m_denominator;
	}


	Complex tg(Complex x) {
		double a = x.Re();
		double b = x.Im();
		return Complex(((sin(2 * a)) / (cos(2 * a) + cosh(2 * b))), (sinh(2 * b) / (cos(2 * a) + cosh(2 * b))));
	}

	Complex f(const Complex& z) {
		Complex a = 2 + 0i;
		return a + z * tg(z);
	}

	Rational tg(Rational x) {
		return std::tan((double)x);
	}

	Rational f(const Rational& r) {
		Rational a = 2 / 1;
		return a + r * tg(r);
	}

	double f(double x) {
		double a = 2.0;
		return a + x * tan(x);
	}


}
