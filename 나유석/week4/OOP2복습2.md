# 객체지향프로그래밍 4주차 복습하기2
## 클래스

---

### 복사생성자(copy construntor)

클래스의 생성자 중 하나인 복사생성자는 말 그대로 한 객체의 값을 복사해서
**똑같은 값의 객체**를 생성하는 것이다.

똑같은 값의 객체를 생성하기에 멤버변수 별로 새롭게 생성하기에 일반적으로는 안전하다.

다만 클래스의 멤버 변수 중 포인터가 포함되는 경우 복사생성자를 통한 객체 생성을 할 경우
문제가 생길 수 있다.

```cpp
#include<iostream>
#include<cstring>
using namespace std;

class Tmp{
private:
  int code;
  char* name;
public:
  Tmp(int c, const char* n)
    : code{ c }, name{ new char[strlen(n) + 1] } {
    for (int i{ 0 }; name[i] != '\0'; i++){
        name[i] = n[i];
    }
    name[strlen(n)] = '\0';
  }
};

int main(){
  Tmp t1(123, "name");
  Tmp t2{ t1 };
}
```
위의 예문은 단순히 보면 문제가 없어보인다.
하지만 클래스에 setter를 추가하고 t1의 멤버변수 name의 역참조 값을 변경하여 이름을 변경하면
t2의 멤버변수 name의 역참조 값 또한 변경된다.

이는 깊은 복사일지라도 포인터 값을 복사하기에 두 객체가 실질적으로 가리키고 있는 메모리가
같으면서 생기는 문제이다.

특히 클래스에 동적배열을 이용하기 위해 new함수를 쓰고 delete를 이용해 해제시키는 과정에서
복사생성자가 사용 될 경우 중복으로 delete하거나 이미 delete하여 할당 해제한 값을 불러올 수 있다.


**이를 예방하기 위해서는 복사생성자를 명시적으로 정의해주어야한다.**

---

### 이동생성자(move constructor)

이동생성자는 Rvalue를 대입하여 객체를 생성할 때 쓰는 생성자이다.
Rvalue는 기본적으로 Rvalue가 포함된 코드가 실행되면 사라지는 값이다.

사용예)
```cpp
#include<iotream>
using namespace std;

class Tmp{
public:
  Tmp() { cout << "default constructor" << endl; }
  Tmp(const Tmp& t) { cout << "copy constructor" << endl; }
  Tmp(Tmp&& t) noexcept { cout << "move constructor" << endl; }
};

int main() {
    Tmp t{ move(Tmp{}) };
}
```

위와 같이 생성자의 파라미터에 **클래스명(클래스명&& 임시명)** 을 해주면 된다.
*참고로 move()함수는 객를 Rvlaue처럼 사용한다는 함수이다.*

이동생성자를 따로 신경써줘야 할 때가 있는데 바로 멤버 변수로 동적 할당을 쓸 때이다.
특히 소멸자에 delete함수를 넣었을 때 문제가 생긴다.

이동생성자로 객체를 생성하면 Rvalue로 쓰인 객체는 다음 코드가 시행 되기 전에 소멸되는데
이 때 delete함수가 사용되면서 Rvalue에 동적 할당되었던 변수의 메모리가 할당 해제되어
이동생성자로 생성한 객체의 동적으로 할당된 변수의 값이 할당 해제된 메모리를 가리키며 문제가 발생한다.

이러한 문제를 해결하기 위한 방법으로 복사생성자에서 사용한 방법과 같이 새로 선언해주는 방법도 있지만
어차피 사라질 Rvalue의 할당을 이동시키는 방법이 비용 측면에서 이득이다.

``cpp
Tmp(Tmp&& t) noexcept : name{ t.name } {
  t.name = nullptr;
}
```
위와 같이 동적 할당된 변수를 얕은 복사로 경로를 복사하고
복사한 Rvalue의 연결의 끊는 방식으로 할당된 경로를 이동시키는 방법을 사용할 수 있다.
