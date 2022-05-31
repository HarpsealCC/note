#include <iostream>


class Test1 {
public:
    Test1() {}

    static const int test1_a_; 
    static const int test1_b_ = 5; 
};

const int Test1::test1_a_ = 2;

class Test2 {
public:
    Test2() {}
    enum { num_turns = 5 };
    // static const int num_turns = 5;
    int score_num[num_turns];
    
};
// const int Test2::num_turns = 5;
class Test3 {
public:
    Test3(int a) : score_num_(a) /*,ref_num_(a)*/ {
    }
    
    const int score_num_ /* = 1 也行*/;
    const int score_uinit_num_;  // const类型成员变量必须初始化
    const double score__double_num_ = 0.1;
    // const 类型可以在声明时候初始化，不过这么用就失去了一次在构造类为其赋值的机会
    // 那还不如用static const，还能节约一些空间
    static const int stat_num_ = 1;  // static const 对于integral类型可以在类内声明时初始化
    static const double double_num_;  // 其他类型就不行了
};
const double Test3::double_num_ = 0.1;

class Test4 {
public:
    Test4(int& a) : ref_arg1_(a) {
    }
    void SetArgs(int& a) {
        ref_arg1_ = a;
    }
    int& ref_arg1_;
    int& ref_arg2_;    // 引用类型成员变量必须初始化
    int a1 = 8;
};


int main(int argc, char* argv) {
    std::cout << " Test a " << Test1::test1_a_  << " Test b " << Test1::test1_b_ << std::endl;
    std::cout << " Test size " << sizeof(Test2::score_num) << std::endl;
    int test_array[5] = {0};
    std::cout << " test_array size " << sizeof(test_array)/sizeof(test_array[0]) << std::endl;
    int a = 8;
    Test3 test3(a);
    std::cout << " Test const " << test3.score_num_  << std::endl;
    Test4 test4(a);
    std::cout << " ref print ptr " << static_cast<void*>(&test4.ref_arg1_) /*<< " " << static_cast<void*>(&test4.ref_arg2_)*/;
}

