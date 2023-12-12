#include <iostream>
#include <ostream>
#include <string>
#include <iomanip>

class A {
  public:
    int a;
    std::string b;
    A(int _a, std::string _b): a(_a), b(_b) {};
    // 必须要用friend修饰 如果没有friend 操作符重载的返回值就是A& 
    friend std::ostream& operator<<(std::ostream& out, const A& obj) {
        out << obj.b << " # " << std::setfill('0') << std::setw(4) << std::hex << obj.a;
        return out;
    }
};

int main() {

    A a{0x0721, "0d00"};
    std::cout << a << std::endl;

    return 0;
}
