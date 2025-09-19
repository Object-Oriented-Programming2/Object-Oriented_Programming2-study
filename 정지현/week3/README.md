클래스 – 데이터 멤버 & 멤버 함수
멤버함수 : 클래스 내부에 바로 정의 or 내부에 프로토타입 선언 후 외부에 따로 정의
Const 멤버함수는 함수 안에서 데이터멤버 값을 변경할 수 없음
접근 제한자 : 접근 권한을 설정하는 private, protected, public
Private에 접근하기 위해서 setter/getter함수 사용
중복 정의 방지 위해 #ifndef or #pragma once 사용

예시)
class Student{
public:
	// 기본 생성자
	Student() {
		// 초기화 코드
	}
};
Student s; 
//기본 생성자 호출

매게변수 생성자: 매게변수를 사용하여 객체의 값을 원하는 값으로 초기화
예)
Public:
	Int num;
	Student ( int n ) {
		num = n;
	}
Student s (10); // num을 10으로 초기화
변환 생성자: 단일 매게변수 가짐, 다른 타입의 값을 해달 클래스 타입으로 변환할 때 호출
멤버 초기화 리스트(member initializer list) : 생성자 뒤에 콜론(:)으로 시작하는 초기화 구역 – 한번에 초기화할 수 있기 때문에 효율적

Operater 연산자
객체에 다른 객체의 값을 대입하는 역할
Tmp& : 대입 연산식의 값이 lvalue가 되어서 연쇄 대입 가능
Const가 앞에 붙으면 매개변수를 값으로 전달하고, 불필요한 복사를 방지(원래의 객체 값을 변형되지 않게 해줌)
