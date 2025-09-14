#include<iostream>
#include<iomanip>
#include<sstream>
using namespace std;

class Rational {
private:
   int numerator;
   int denominator;
   void reduce() {
      int son = numerator;
      int mother = denominator;
      if (son < 0) {
         son *= -1;
      }
      if (mother < 0) {
         mother *= -1;
      }
      while (mother != 0) {
         int temp = son % mother;
         son = mother;
         mother = temp;
      }
      numerator /= son;
      denominator /= son;
   }

public:
   Rational(int numerator = 0, int denominator = 1) {
      if (denominator < 0) {
         numerator *= -1;
         denominator *= -1;
      }
      this->numerator = numerator;
      this->denominator = denominator;
      reduce();
   }

   Rational add(const Rational& r) const {
      int son1, son2, son, mother;
      son1 = this->numerator * r.denominator;
      son2 = r.numerator * this->denominator;
      mother = this->denominator * r.denominator;
      son = son1 + son2;
      Rational rr = Rational(son, mother);
      return rr;

   }

   Rational subtract(const Rational& r) const {
      int son1, son2, son, mother;
      son1 = this->numerator * r.denominator;
      son2 = r.numerator * this->denominator;
      mother = this->denominator * r.denominator;
      son = son1 - son2;
      Rational rr = Rational(son, mother);
      return rr;
   }

   Rational multiply(const Rational& r) const {
      int son, mother;
      son = this->numerator * r.numerator;
      mother = this->denominator * r.denominator;
      Rational rr = Rational(son, mother);
      return rr;
   }

   Rational divide(const Rational& r) const {
      int son, mother;
      son = this->numerator * r.denominator;
      mother = this->denominator * r.numerator;
      Rational rr = Rational(son, mother);
      return rr;
   }

   string toRationalString() const {
      ostringstream output;
      output << this->numerator << "/" << this->denominator;
      return output.str();
   }

   double toDouble() const {
      return (double)this->numerator / (double)this->denominator;
   }
};

int main() {
   int a, b, c, d;
   cout << "Enter the first rational: ";
   cin >> a >> b;
   Rational r1 = Rational(a, b);
   cout << "First rational: " << r1.toRationalString() << "\n";
   cout << "Enter the second rational: ";
   cin >> c >> d;
   Rational r2 = Rational(c, d);
   cout << "Second rational: " << r2.toRationalString() << "\n";

   cout << r1.toRationalString() << " + " << r2.toRationalString() << " = " << r1.add(r2).toRationalString() << " = " << fixed << setprecision(2) << r1.add(r2).toDouble()<<"\n";
   cout << r1.toRationalString() << " - " << r2.toRationalString() << " = " << r1.subtract(r2).toRationalString() << " = " << fixed << setprecision(2) << r1.subtract(r2).toDouble() << "\n";
   cout << r1.toRationalString() << " * " << r2.toRationalString() << " = " << r1.multiply(r2).toRationalString() << " = " << fixed << setprecision(2) << r1.multiply(r2).toDouble() << "\n";
   cout << r1.toRationalString() << " / " << r2.toRationalString() << " = " << r1.divide(r2).toRationalString() << " = " << fixed << setprecision(2) << r1.divide(r2).toDouble();

}
