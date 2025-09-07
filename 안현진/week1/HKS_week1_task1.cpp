#include<iostream>
#include<string>
#include<vector>
using namespace std;

class Point {
private:
   string pname;
   int x, y;
public:
   Point(string pname = NULL, int x = 0, int y = 0) {
      this->pname = pname;
      this->x = x;
      this->y = y;
   }

   void setName(string str) {
      this->pname = str;
   }

   void setX(int x) {
      this->x = x;
   }

   void setY(int y) {
      this->y = y;
   }

   string getName() {
      return pname;
   }

   int getX() {
      return x;
   }

   int getY() {
      return y;
   }
};

int main() {
   int N;
   cout << "Number of points: ";
   cin >> N;
   vector<Point> v;
   for (int i{ 0 }; i < N; i++) {
      cin.ignore(100, '\n');
      string str;
      int x, y;
      cout << "Name of a point: ";
      getline(cin, str);
      cout << "Position of a point: ";
      cin >> x >> y;
      Point p = Point(str, x, y);
      p.setName(str);
      p.setX(x);
      p.setY(y);
      v.push_back(p);
      cout << p.getName() << " (" << p.getX() << ", " << p.getY() << ")\n\n";
   }
   cout << fixed;
   cout.precision(1);
   int finalX = 0, finalY = 0;
   for (int i{ 0 }; i < N; i++) {
      finalX += v[i].getX();
      finalY += v[i].getY();
   }
   cout << "Center of " << N << " points: (" << (double)finalX / N << ", " << (double)finalY / N << ")";
}
