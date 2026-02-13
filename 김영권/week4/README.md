<ostringstream>
사용하기 위해서 <sstream> 파일을 포함시켜야 한다.
여러 데이터 타입을 조합하여 하나의 형식화된 문자열을 만들어야 할 때 유용
cout으로 출력하듯이 데이터를 넣고 .str() 함수를 호출하여 쌓인 데이터들을 string 형태로 출력

#사용예시

#include <iostream>
#include <string>
#include <sstream>
using namespace std;

int main()
{
    ostringstream oss;

    string name = "홍길동";
    int age = 30;

    oss << "이름: " << name;
    oss << ", 나이: " << age;
    oss << "세";
    
    string result = oss.str();
    
    cout << result << endl;
}
