##各种变量类型初始化的状态
全局静态与局部静态变量的内置类型都会初始化为0
局部变量与成员变量的内置类型会初始化为随机值
非内置类型（如class、struct等）会调用默认构造函数


##class使用参数列表初始化与使用赋值操作初始化的区别
以下的操作只是赋值操作，而非初始化

```
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
            const std::list<PhoneNumber>& phone) {
    thename_ = name;  // 这些都是赋值，而非初始化
    theaddress_ = address;
    thephone_ = phone;
    numtimeconsulted = 0;
}
```
这样调用的弊端是，在进入赋值操作之前，ABEntry类会先调用一次默认构造函数[^注1]，之后再赋值操作中，还会调用一次拷贝构造函数，效率有显著的降低。
[^注1]:p28页，在进入构造函数之前，会先进行成员变量的初始化。

通常应该按如下的方式进行初始化，在进入构造函数之前，在初始化列表中均调用拷贝构造函数来对成员进行初始化操作
```
ABEntry::ABEntry(const std::string& name, const std::string& address, 
            const std::list<PhoneNumber>& phone) : thename_(name), theaddress_(address),
            thephone_(phone), numtimeconsulted(0) {
}
```
对自定义的class来说，可以省去不小的开销，但是对内置类型的效率提升可能没有很明显（八成编译器有优化），不过为了一致性，可以都一起写成使用参数列表进行初始化。

虽然有其他的写法，但是为了避免混淆或者有成员变量的初始化被遗漏，可以定下一个规则，规定总是在初始化列表中初始化所有的成员变量。以免还得记得哪些需要初始化（const与reference成员是必须初始化的，不然会报错，在case3中已经有测试了，后续在articl5中还会再进行介绍）

另外，c++有着十分固定的c++成员初始化的顺序，父类总比子类更先初始化，class的成员变量是按照其声明的顺序进行的初始化

##不同编译单元内的non-local-static的初始化次序

