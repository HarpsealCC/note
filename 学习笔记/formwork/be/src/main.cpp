/*** 
 * @FilePath: /formwork/be/src/main.cpp
 * @Author: harpseal
 * @Date: 2022-06-09 15:42:52
 * @LastEditTime: 2023-01-31 17:37:31
 * @email: 844291270@qq.com
 */


// #include <iostream>
// #include <limits>
// #include <cstring>
// #include <vector>
// #include <algorithm>
// #include <cmath>
// #include <boost/bind.hpp>
// #include <boost/function.hpp>
// #include <boost/lexical_cast.hpp>

// const __int128_t INT128_MIN_VALUE = (__int128_t)1 << 127;
// const __int128_t INT128_MAX_VALUE = -(INT128_MIN_VALUE + 1);

// std::ostream& operator<<(std::ostream& os, __int128_t T) {
//     if (T<0) os<<"-";if (T>=10 ) os<<T/10;if (T<=-10) os<<(-(T/10));
//     return os<<( (int) (T%10) >0 ? (int) (T%10) : -(int) (T%10) ) ;
// }



// class GetSkValue {
// public:
// GetSkValue() {

// }
// template<class A>
// A GetValue() {
//     return a_;
// }

// private:
//    double a_ = 12.35;
// };

// template<class A>
// bool Comparelt(std::string value, GetSkValue& nodevalue) {
//     A tmp = boost::lexical_cast<A>(value);
//     if (tmp < nodevalue.GetValue<A>()) {
//         return true;
//     } else {
//         return false;
//     }
// }
// template<class A>
// bool Comparegt(std::string value, GetSkValue& nodevalue) {
//     A tmp = boost::lexical_cast<A>(value);
//     if (tmp > nodevalue.GetValue<A>()) {
//         return true;
//     } else {
//         return false;
//     }

// }
// template<class A>
// bool CompareEq(std::string value, GetSkValue& nodevalue) {
//     A tmp = boost::lexical_cast<A>(value);
//     if (tmp == nodevalue.GetValue<A>()) {
//         return true;
//     } else {
//         return false;
//     }
// }
// enum Valuetype {
//     bool_type,
//     int_type,
//     double_type
// };
// enum Optype {
//     EQ,
//     LT,
//     GT
// };

// typedef boost::function<bool (std::string, GetSkValue&) > ThreadFunctor;



// template <class F>
// class GenerateFuncByValueType {
// public:
// GenerateFuncByValueType(const F& f, std::string min, GetSkValue& kv) {
//     func_ = boost::bind(f, min, kv);
// }

//     F func_;
// };
// template <class T>
// ThreadFunctor FuncGenerater(Optype type) {
//     switch(type) {
//         case EQ:
//             return boost::bind(CompareEq<T>, _1, _2);
//         case LT:
//             return boost::bind(Comparelt<T>, _1, _2);
//         case GT:
//             return boost::bind(Comparegt<T>, _1, _2);
//         default:
//             break;
//     }
// }



// ThreadFunctor FuncGeneraterBy(Valuetype data_type, Optype op_type) {
//     switch(data_type) {
//         case int_type:
//             return FuncGenerater<int>(op_type);
//         case double_type:
//             return FuncGenerater<double>(op_type);
//         default:
//         break;
//     }
// }
// template <class T>
// struct iterator_traits_s {
//     typedef typename T::value_type value_type;
// };
// template <class T>
// struct iterator_traits_s<T*> {
//     typedef T value_type;
// };


// int main() {
//     for (int i = 0; i < 1000000; i ++) {
//         size_t need_read_filesize = 65535;
//         char* buffer1 = new char[need_read_filesize];
//         std::unique_ptr<char> buffer(buffer1);
//         std::string result(buffer1, need_read_filesize);
//     }
//     while(1) {

//     }
//     return 0;
// }


#include <iostream>
using namespace std;

// foo 可以是成员函数或者成员对象
char check_member_foo(...);
template <typename T>
auto check_member_foo(T const& t, decltype(&T::foo) p = 0)->decltype(p);

template<typename T>
struct has_member_fun_or_property
{
    static const bool value =
    sizeof(char) != sizeof( check_member_foo( *static_cast<T*>(0) ) );
};

struct test
{
    void foo(int, double);
};

struct test2
{
    //int foo;
};

// int main()
// {
//     cout << has_member_fun_or_property<test>::value << endl;
//     cout << has_member_fun_or_property<test2>::value << endl;
    
//     return 0;
// }


// #include <iostream>
// #include <typeinfo>
 
// int main() {
//     int a = 1, b = 2;
//     int *p = &a;
//     decltype(*p) decl_p = b;
//     std::cout << "修改前b: " << b << std::endl;
//     decl_p = 5;
//     std::cout << "修改后b: " << b << std::endl;
 
//     return 0;
// }

int fun()
{
    std::cout << " 1111 ";
}

int main(int argv, char* argc[])
{
    decltype(fun) x;
    std::cout << x << std::endl;
}