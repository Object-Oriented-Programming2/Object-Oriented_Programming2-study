# 객체지향프로그래밍 3주차 복습하기1
## 클래스

---
###상수 객체와 상수 멤버 함수의 관계
객체와 멤버 함수가 상수인지 아닌지에 따라 접근 할 수 있는 권한이 다르다.

| 객체   | 멤버 함수 | 접근 가능 여부 |
|--------|-----------|----------------|
| 비상수 | 비상수    | 가능 |
| 비상수 | 상수      | 가능 |
| 상수   | 비상수    | 불가능 |
| 상수   | 상수      | 가능 |

```cpp
#include<iostream>
using namespace std;

class Tem{
private:
  int tem;
public:
  explicit Tem(int = 1);
  void setTem(int n){
    tem = n}
  int getTem() const{
    return tem;}
}:

int main(){
  Tem isNotConst;
  const Tem isConst;

  isNotConst.setTem();
  isNotConst.getTem();
  //isConst.setTem();  //컴파일 오류
  isConst.getTem();
}
```

**한 줄 요약** 객체가 상수면 접근할 수 있는 멤버 함수 또한 상수뿐이다.

---

### Memver Initialize List
생성자를 선언 할 때 멤버변수를 초기화하는 방법 중 하나

사용방법
*클래스명(인자 1, 인자 2 ...)
  :멤버변수1{ 인자 1 }, 멤버변수2{ 인자 2}...{
  ...
}*

예문
```cpp
#include<iostream>
using namespace std;

class Tem{
private:
  const int _id;
  int _num;
public:
  Tem (int id, int num)
    : _id{ id }, _num{ num}{
    cout << "object constructor" << endl;
  }
};
```

**주요 특징**
코드 진행 순서가 다름.
생성자 내의 코드는 객체가 생성된 이후 진행됨.
멤버 이니셜라이저 리스트는 객체의 생성과 동시에 초기화를 진행함.
덕분에 상수 멤버 변수의 초기화를 할 수 있음.

---

###참조 반환(주의!)
함수는 참조자를 반환할 수 있음.
다만 클래스에서 참조자를 반환하는 경우에는 주의를 해야함.

```cpp
#include<iostream>
using namespace std;

class Tem{
private:
  int _tem;
public:
  int getTem(){
    return _tem;
  }
  int& getReferenceTem() {
    return _tem;
  }

```

위의 Tem 클래스에서 _tem 멤버 변수는 private 캡슐에 속해 있으므로 일반적으로는 클래스 바깥에서 접근이 불가능하다.
하지만 getReferenceTem() 함수는 _tem을 참조 형식으로 반환해버리기 때문에 _tem에 접근 할 수 있게된다.
이 경우 컴파일 오류는 나지 않으나 의도치 않ㅇ느 오류가 발생할 가능성이 생긴다.
그러므로 private 캡슐에 반드시 접근해야할 상황이 아닌 이상 참조자 반환 형식을 쓰는 것을 지양한다.

---

###default, delete
생성자와 소멸자는 사용자가 정의하지 않아도 자동적으로 정의되어 실행될 수 있다.
이 때 따로 정의하지 않고 default를 사용하여 내부에 정의된 생성자나 소멸자를 사용할 수 있다.

예시
```cpp
Student() = default;
Student(const Student& origin) = default;
```

이는 기본생성자가 명시적으로 정의되지 않아도 컴파일러가 정의하여 사용하나
일반생성자가 명시적으로 정의되면 컴파일러가 기본생성자를 정의하지 않기에 간편하게 쓰기 위한 문법이다.

delete는 반대로 암시적으로 정의되는 생성자나 소멸자를 제거하는 것이다.
보통 복사생성자를 사용자에게 허용하지 않을 때 사용한다.
다만 소멸자를 제거할 경우 객체를 생성할 수 없다.
사용 방법은 default와 동일하다.

---

###Composition(구성)
구성은 단순히 말해 클래스 내의 클래스이다.
클래스의 멤버 변수로 다른 클래스를 선언하여 사용한다.

사용예

```cpp
#include<iostream>

class Phone{
private:
  string name;
public:
  Phone(const string& name)
    :name{name}{ cout << "Phone constructor" << endl;}
  ~Phone() { cout << "Phone destructor" << endl;}
};

class Person{
private:
  string name;
  const Phone phone;
public:
  Person(const string& name, const Phone& phone)
    : name{ name }, phone { phone } { cout << "Person contructor" << endl; }
  ~Person() { cout << "Person destructor" << endl;}


int main(){
  Phone phone{ "eyePhone" };
  Person person{ "pby", phone };
}
```

위의 예문과 같이 클래스의 멤버 변수로 미리 정의한 클래스를 선언하는 형식을 ##Composition(구성)##이라고 한다.

다만 위의 코드를 실행해보면 생성자 출력이 2번, 소멸자 출력이 3번 나타난다.
이는 person 객체를 생성할 때 phone 객체를 복사생성자로 복사하여 다른 Phone 객체를 생성하나
복사생성자는 따로 정의되지 않아 컴파일러가 기본적으로 정의한 복사생성자가 실행되어 출력을 하지 않기 떄문이다.

