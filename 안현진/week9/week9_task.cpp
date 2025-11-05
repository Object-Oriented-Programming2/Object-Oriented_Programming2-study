#include<iostream>
#include<sstream>
#include<cmath>
#include<iomanip>
#include<cstdlib>
using namespace std;

class Point {
public:
	Point(int x = 0, int y = 0, int z = 0) {
		this->x = x;
		this->y = y;
		this->z = z;
	}
	virtual ~Point() = default;
	int getX() const {
		return x;
	}
	int getY() const {
		return y;
	}
	int getZ() const {
		return z;
	}
	void setX(int x) {
		this->x = x;
	}
	void setY(int y) {
		this->y = y;
	}
	void setZ(int z) {
		this->z = z;
	}
	virtual string toString() const {
		ostringstream output;
		output << "(" << x << ", " << y << ", " << z << ")";
		return output.str();
	}
private:
	int x, y, z;
};

class Bubble : public Point {
public:
	Bubble(int x, int y, int z, int r = 0) : Point(x, y, z) {
		this->radius = r;
		this->volume = (4.0 / 3.0) * 3.14 * r * r * r;
	}
	virtual ~Bubble() = default;
	int getRadius() const {
		return radius;
	}
	void setRadius(int r) {
		this->radius = r;
	}
	double getVolume() const {
		return volume;
	}
	void setVolume(int v) {
		this->volume = v;
	}
	virtual string toString() const {
		ostringstream output;
		output << Point::toString() << " R=" << radius;
		return output.str();
	}
private:
	int radius{ 0 };
	double volume;
};

int main() {
	Bubble* arr[100];
	int x, y, z, r;
	int i = 0;
	cout << "Enter the center (x, y, z) and radius of a bubble (EOF to end): ";
	if (!(cin >> x >> y >> z >> r)) {
		return 0;
	}
	arr[i] = new Bubble(x, y, z, r);
	Bubble biggest = *arr[i];
	while (cin >> x >> y >> z >> r) {
		arr[i + 1] = new Bubble(x, y, z, r);
		int r1 = arr[i]->getRadius(), r2 = arr[i + 1]->getRadius();
		double d = sqrt((arr[i]->getX() - arr[i + 1]->getX()) * (arr[i]->getX() - arr[i + 1]->getX()) + (arr[i]->getY() - arr[i + 1]->getY()) * (arr[i]->getY() - arr[i + 1]->getY()) + (arr[i]->getZ() - arr[i + 1]->getZ()) * (arr[i]->getZ() - arr[i + 1]->getZ()));
		if (d > r1 + r2) {
			cout << "bubble " << arr[i]->toString() << " and bubble " << arr[i + 1]->toString() << " are disjoint\n";
		}
		else if (d > abs(r1 - r2) && d <= r1 + r2) {
			cout << "bubble " << arr[i]->toString() << " and bubble " << arr[i + 1]->toString() << " partially overlap\n";
		}
		else if (d <= r1 - r2) {
			cout << "bubble " << arr[i]->toString() << " includes bubble " << arr[i + 1]->toString() << "\n";
		}
		else {
			cout << "bubble " << arr[i]->toString() << " is included in bubble " << arr[i + 1]->toString() << "\n";
		}
		if (biggest.getVolume() < arr[i + 1]->getVolume()) {
			biggest = *arr[i + 1];
		}
		++i;
	}
	cout << fixed << setprecision(2);
	cout << "bubble with the largest volume: bubble " << biggest.toString() << ", V=" << biggest.getVolume() << "\n";

}
