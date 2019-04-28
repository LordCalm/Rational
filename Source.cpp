#include <iostream>
#include <vector>
#include <sstream>
#include <set>
#include <map>
#include <algorithm>
#include <exception>

using namespace std;

class Rational {
public:
	Rational();
	Rational(long long numerator, long long denominator);

	long long Numerator() const {
		return _numerator;
	};
	long long Denominator() const {
		return _denominator;
	};

	friend istream& operator>> (istream& is, Rational& x);

private:
	long long _numerator, _denominator;
};

Rational::Rational() {
	_numerator = 0, _denominator = 1;
}

int NOD(int a, int b) {
	while (a > 0 && b > 0) {
		if (a > b)
			a %= b;
		else
			b %= a;
	}
	return a + b;
}

Rational::Rational(long long numerator, long long denominator) {
	if(denominator == 0)
		throw invalid_argument("Invalid argument");
	else if (numerator == 0) {
		_numerator = 0;
		_denominator = 1;
	}
	else {
		long long nod = NOD(abs(numerator), abs(denominator));
		long long sign = (numerator / abs(numerator)) * (denominator / abs(denominator));
		_numerator = sign * abs(numerator) / nod;
		_denominator = abs(denominator) / nod;
	}
}

bool operator== (const Rational & l, const Rational & r) {
	if (l.Numerator() == r.Numerator() && l.Denominator() == r.Denominator())
		return true;
	return false;
}

bool operator< (const Rational & l, const Rational & r) {
	if (l.Numerator() * r.Denominator() < l.Denominator() * r.Numerator())
		return true;
	return false;
}

const Rational operator+ (const Rational & l, const Rational & r) {
	return Rational(l.Numerator() * r.Denominator() + l.Denominator() * r.Numerator(),
		l.Denominator() * r.Denominator());
}

const Rational operator- (const Rational & l, const Rational & r) {
	return Rational(l.Numerator() * r.Denominator() - l.Denominator() * r.Numerator(),
		l.Denominator() * r.Denominator());
}

const Rational operator* (const Rational & l, const Rational & r) {
	return Rational(l.Numerator() * r.Numerator(),
		l.Denominator() * r.Denominator());
}

const Rational operator/ (const Rational & l, const Rational & r) {
	if (r.Numerator() == 0)
		throw domain_error("Division by zero");
	return Rational(l.Numerator() * r.Denominator(),
		l.Denominator() * r.Numerator());
}

ostream& operator<< (ostream & os, const Rational & x) {
	os << x.Numerator() << "/" << x.Denominator();
	return os;
}

istream& operator>> (istream & is, Rational & x) {
	if (!is)
		return is;
	int n, d;
	is >> n;
	is.ignore();
	if (!is)
		return is;
	is >> d;
	x = Rational(n, d);
	return is;
}

Rational Calc(const Rational& l, const Rational& r, char operation) {
	if (operation == '+')
		return l + r;
	else if (operation == '-')
		return l - r;
	else if (operation == '*')
		return l * r;
	else if (operation == '/')
		return l / r;
}

int main() {
	
	try {
		Rational a, b;
		char operation;
		cin >> a >> operation >> b;;
		cout << Calc(a, b, operation) << endl;
	}
	catch (exception& e) {
		cout << e.what() << endl;
	}

	return 0;
}