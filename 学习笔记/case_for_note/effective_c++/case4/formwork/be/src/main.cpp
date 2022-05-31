#include <iostream>
#include <list>

class PhoneNumber {};

class ABEntry {
public:
    ABEntry(const std::string& name, const std::string& address, 
            const std::list<PhoneNumber>& phone);
private:
    std::string thename_;
    std::string theaddress_;
    std::list<PhoneNumber> thephone_;
    int numtimeconsulted;
};

ABEntry::ABEntry(const std::string& name, const std::string& address, 
            const std::list<PhoneNumber>& phone) : thename_(name), theaddress_(address),
            thephone_(phone), numtimeconsulted(0) {
}

// ABEntry::ABEntry(const std::string& name, const std::string& address, 
//             const std::list<PhoneNumber>& phone) {
//     thename_ = name;  // 这些都是赋值，而非初始化
//     theaddress_ = address;
//     thephone_ = phone;
//     numtimeconsulted = 0;
// }

int main(int argc, char* argv) {
    
    return 0;
}