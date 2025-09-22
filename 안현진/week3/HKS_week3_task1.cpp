#include<iostream>
#include<sstream>
#include<cmath>
#include<stdexcept>
using namespace std;

class Quadratic {
	friend Quadratic add(Quadratic& q1, Quadratic& q2);
	friend Quadratic subtract(Quadratic& q1, Quadratic& q2);
private:
	double a{ 1 };
	double b{ 0 };
	double c{ 0 };

public:
	Quadratic(double a, double b, double c) {
		if (a == 0) {
			throw invalid_argument("The coefficient of the quadratic term must be non-zero. Enter again.");
		}
		this->a = a;
		this->b = b;
		this->c = c;
	}

	string toString() const {
		ostringstream output;
		output << a << "x^2";
		if (b >= 0) {
			output << "+" << b << "x";
		}
		else {
			output << b << "x";
		}

		if (c >= 0) {
			output << "+" << c;
		}
		else {
			output << c;
		}

		output << "=0";
		return output.str();
	}

	void solve() {
		double D;
		D = (b * b) - 4 * a * c;
		cout.precision(2);
		cout << fixed;
		if (D < 0) {
			cout << "No real roots\n";
		}
		else if (D == 0) {
			cout << "x=" << -b / (2 * a)<<"\n";
		}
		else {
			D = sqrt(D);
			cout << "x=" << (-b + D) / (2 * a) << " or " << (-b - D) / (2 * a)<<"\n";
		}
	}
};

Quadratic add(Quadratic& q1, Quadratic& q2) {
	double a, b, c;
	a = q1.a + q2.a;
	b = q1.b + q2.b;
	c = q1.c + q2.c;
	Quadratic q3 = Quadratic(a, b, c);

	return q3;
}

Quadratic subtract(Quadratic& q1, Quadratic& q2) {
	double a, b, c;
	a = q1.a - q2.a;
	b = q1.b - q2.b;
	c = q1.c - q2.c;
	Quadratic q3 = Quadratic(a, b, c);

	return q3;
}

int main() {
	Quadratic q1(1, 0, 0), q2(1, 0, 0);
	while (true) {
		try {
			cout << "Enter 3 coefficients of the first quadratic equation: ";
			double a, b, c;
			cin >> a >> b >> c;
			Quadratic q(a, b, c);
			q1 = q;
			cout << "First equation: " << q1.toString() << "\n";
			break;
		}
		catch (invalid_argument& e) {
			cout << e.what() << "\n";
		}

	}
	while (true) {
		try {
			cout << "Enter 3 coefficients of the second quadratic equation: ";
			double a, b, c;
			cin >> a >> b >> c;
			Quadratic q(a, b, c);
			q2 = q;
			cout << "Second equation: " << q2.toString() << "\n";
			break;
		}
		catch (invalid_argument& e) {
			cout << e.what() << "\n";
		}

	}
	cout << "\n";

	cout << "Solution of " << q1.toString() << ": ";
	q1.solve();
	cout << "Solution of " << q2.toString() << ": ";
	q2.solve();
	cout << "\n";

	cout << "(" << q1.toString() << ")+(" << q2.toString() << ")=" << add(q1, q2).toString() << "\n";
	cout << "(" << q1.toString() << ")-(" << q2.toString() << ")=" << subtract(q1, q2).toString() << "\n";

}
