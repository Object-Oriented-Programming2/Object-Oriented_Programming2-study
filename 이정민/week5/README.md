**연산자 오버로딩
​•보통 연산자는 int,float,string같은 타입에서 자주 사용함.
​•class객체들도 연산자를 사용할 수 있도록 연산자 오버로딩을 지원함.
​•구현은 함수처럼 함. 대신 operator와 적용할 연산자를 뒤에다가 붙여서 사용함.
​•연산자 오버로딩은 friend함수 or class 멤버함수로 만들어야함.

연산자 오버로딩을 case를 나눠서 알아보자

**참/거짓 판단 오버로딩
​•주로 ==,!=,>,<등 대소판단이나 같은지를 확인할 때 사용한다.

​•​friend함수 예시
friend bool operator==(const Power& left, const Power& right)
{
	if (left.kick == right.kick && left.punch == right.punch)
		return true;
	return false;
}

​•멤버함수 예시
bool operator==(const Power& other)
{
	return (kick == other.kick && punch == other.punch);
}

**대입+연산 오버로딩
​•주로 +,-,+=,=등 연산을 하거나 연산+대입/대입 등을 할 때 사용한다.
​•매개변수에 따라 객체 + int등의 연산도 가능하다.

​•객체 + 객체 예시
Power operator+=(const Power& other)
{
	kick += other.kick;
	punch += other.punch;
	return *this;
}

​•객체 + int 예시
Power operator+(int a)
{
	Power temp;
	temp.kick = kick + a;
	temp.punch = punch + a;
	return temp;
}

​•대입 예시(객체 = other객체)
Power operator=(const Power& a)
{
	kick = a.kick;
	punch = a.punch;
	return *this;
}

**cin,cout 오버로딩
​•기존 class의 멤버변수등을 불러올 때는 getter함수를 추가로 만들었음.
​•operator<< / operator>>을 사용하여 객체 내 원하는 부분을 자체적으로 불러오도록/대입하도록 해주는 기능을 함.

​•cin 오버로딩 예시
friend istream& operator>>(istream& input, Power& a)
{
	input >> a.kick >> a.punch;
	return input;
}

​•cout 오버로딩 예시
friend ostream& operator<<(ostream& output,const Power& a)
{
	output << "kick = " << a.kick << ", punch = " << a.punch << endl;
	return output;
}

**prefix와 postfix operator
​•prefix와 postfix를 int타입으로 다음과 같이 예시를 들 수 있다.
prefix:  ++a;
postfix: a++;

​​??:똑같이 ++을 사용하는데 어떻게 구분하나요?
->&를 사용하면 prefix,사용하지 않으면 postfix기능을 한다.
+postfix는 parameter위치에 int타입을 추가해주고 prefix는 void형식으로 오버로딩한다.

​•prefix 예시
Power& operator++()
{
	kick++;
	punch++;
	return *this;
}

​•postfix 예시
Power operator++(int a)
{
	Power temp = *this;
	++(*this);
	return temp;
}
