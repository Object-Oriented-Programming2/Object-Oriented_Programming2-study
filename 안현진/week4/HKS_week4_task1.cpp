#include <array>
#include <iostream>
#include <string>
#include<iomanip>
#include<vector>
#include<algorithm>
using namespace std;


class Date {
   friend std::ostream& operator<<(std::ostream&, const Date&);
   friend std::istream& operator>>(std::istream&, Date&);
public:
   Date(int m = 1, int d = 1, int y = 1900);
   void setDate(int, int, int);
   Date& operator++();
   Date operator++(int);
   Date& operator+=(unsigned int);
   static bool leapYear(int);
   bool endOfMonth(int) const;
   bool feb29() const {
      return (month == 2 && day == 29);
   }
   unsigned int getMonth() const{
      return month;
   }
   unsigned int getday() const {
      return day;
   }
   unsigned int getyear() const {
      return year;
   }

private:
   unsigned int month;
   unsigned int day;
   unsigned int year;
   static const std::array<unsigned int, 13> days;
   void helpIncrement();
};

Date::Date(int m, int d, int y) {
   setDate(m, d, y);
}

void Date::setDate(int mm, int dd, int yy) {
   if (mm >= 1 && mm <= 12) month = mm;
   else throw invalid_argument{ "Month must be 1-12" };

   if (yy >= 1900 && yy <= 2100) year = yy;
   else throw invalid_argument{ "Year must be >= 1900 and <= 2100" };

   // test for a leap year
   if ((mm == 2 && leapYear(year) && dd >= 1 && dd <= 29) ||
      (dd >= 1 && dd <= days[mm]))  day = dd;
   else {
      throw invalid_argument{ "Day is out of range for current month and year" };
   }
}
// overloaded prefix increment operator 
Date& Date::operator++() {
   helpIncrement(); // increment date 
   return *this; // reference return to create an lvalue
}

// overloaded postfix increment operator
Date Date::operator++(int) {
   Date temp{ *this }; // hold current state of object 
   helpIncrement();

   // return unincremented, saved, temporary object 
   return temp;  // value return; not a reference return 
}

// add specified number of days to date 
Date& Date::operator+=(unsigned int additionalDays) {
   for (unsigned int i = 0; i < additionalDays; ++i) {
      helpIncrement();
   }
   return *this; // enables cascading 
}

bool Date::leapYear(int testYear) {
   return (testYear % 400 == 0 || (testYear % 100 != 0 && testYear % 4 == 0));
}
bool Date::endOfMonth(int testDay) const {
   if (month == 2 && leapYear(year))
      return testDay == 29; // last day of Feb. in leap year
   else return testDay == days[month];
}
void Date::helpIncrement() {
   if (!endOfMonth(day))
      ++day; // increment day
   else {
      if (month < 12) { // day is end of month and month < 12
         ++month; // increment month
         day = 1; // first day of new month
      }
      else { // last day of year
         ++year; // increment year
         month = 1; // first month of new year
         day = 1; // first day of new month
      }
   }
}

const array<unsigned int, 13>Date::days{
   0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31
};

ostream& operator<<(ostream& output, const Date& d) {
   output << d.month << '/' << d.day << "/" << d.year;
   return output; // enables cascading
}

istream& operator>>(istream& input, Date& d) {
   input >> setw(2) >> d.month;
   input.ignore();
   input >> setw(2) >> d.day;
   input.ignore();
   input >> setw(4) >> d.year;
   return input;
}

class Baby {
public:
   Baby(const string& str, const Date& d) {
      name = str;
      birthDate = d;
   }
   void setName(string& str) {
      name = str;
   }
   void setBirthDate(Date& d) {
      birthDate = d;
   }
   string getName() const {
      return name;
   }
   Date getBirthDate() const {
      return birthDate;
   }
private:
   string name;
   Date birthDate;
};


int main() {
   int N;
   cout << "Enter the number of newborn babies: ";
   cin >> N;
   cout << "\n";
   vector<Baby> v;
   for (int i{ 0 }; i < N; i++) {
      cout << "Enter the baby name: ";
      string name;
      cin.ignore(numeric_limits<streamsize>::max(), '\n');
      getline(cin, name);
      
      cout << "Enter the baby's birth date in the form mm/dd/yyyy: ";
      Date d;
      cin >> d;
      v.emplace_back(Baby(name, d));
      cout << v.back().getName() << " born on " << v.back().getBirthDate() << "\n";
      d += 99;
      cout << "100th day: " << d << "\n";
      d = v.back().getBirthDate();
      if (d.feb29()) {
         d = Date(d.getMonth(), d.getday() - 1, d.getyear() + 1);
      }
      else {
         d = Date(d.getMonth(), d.getday(), d.getyear() + 1);
      }
      cout << "First birthday: " << d << "\n";
      d = Date(3, 1, v.back().getBirthDate().getyear() + 7);
      cout << "First school day: " << d << "\n\n";
   }
   sort(v.begin(), v.end(), [](const Baby& b1, const Baby& b2) {return b1.getName() < b2.getName(); });
   cout << "Newborn babies in the alphabetical order of names:\n";
   for (int i{ 0 }; i < N; i++) {
      cout << v[i].getName() << " (" << v[i].getBirthDate() << ")\n";
   }
}
