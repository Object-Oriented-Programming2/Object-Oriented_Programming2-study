#객체지향프로그래밍 3주차 복습하기2
##클래스

---

###friend
클래스 외부의 함수를 선언 하였을 때 클래스 내부의 pirvate에 접근하기 위한 문법.
friend를 붙이고 함수를 선언한다.

사용법
```cpp
class Tmp{
  friend void addValue(Tmp& t, int value);
private:
  int number{2};
public:
  int getValue() const { return number;}
};

void addValue(Tmp& t, int value){
  t.numver += value;
}
//생략
```
위와 같이 접근할 멤버 변수의 클래스 스코프 내에서 friend를 리턴형 앞에 붙여서 사용한다.

클래스 B의 모든 멤버 함수를 클래스 A의 friend로 선언: 클래스 A 정의에 "friend class B" 명시

---

###Cascaded Function Calls
종속 함수 호출
연속으로 함수를 호출할 수 있는 연산자 존재

ex)
```cpp
#include<iostream>

int main(){
  std::cout << "Hello" << endl << "World";
}
```

위의 cout함수는 단순히 오른쪽에 있는 모든 <<연산자를 한 번에 수행하는 것이 아닌 
첫 번째 <<연산자 수행 후 그 자리에 cout을 리턴하여 이어서 cout함수를 시행하는 방식이다.

마찬가지로 .연산자에도 활용할 수 있다.

ex)
```cpp
#include<iostream>
using namespace std;

class Tmp{
private:
  int _id;
  string _name;
public:
  Tmp& setId(int id){
    _id = id;
    return *this;
}
  Tmp& setName(string name){
    _name = name;
    return *this;
}
};

int main(){
  Tmp t;
  t.setId(1225).setName("none");

}
```

위와 같이 setter을 void형식이 아닌 클래스 포인터 형식을 반환하여
값을 설정 후 곧바로 다른 값을 설정할 수 있게 한다.

---

###static Member
클래스 선언 시 생성되는 멤버로 객체의 생성과 상관없이 사용이 가능하다.

기본적으로 static을 자료형 앞에 붙여 선언한다.
```cpp
class Tmp{
pivate:
  static int count;
public:
  static int getCount();
}
```

초기화는 반드시 클래스 외부에서 해야한다.
```cpp
int Tmp::count == 0;
int Tmp::getCount(){
  return count;
}
```
static 멤버 함수는 static 멤버 변수에만 접근할 수 있다. 

접근 방식은 두 개이나 보통은 클래스명을 붙여 사용한다.
```cpp
Tmp::count;
Tmp t;
t.getCount();
```
