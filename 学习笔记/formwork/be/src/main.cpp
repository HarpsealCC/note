/*** 
 * @FilePath: /github/harpseal/学习笔记/formwork/be/src/main.cpp
 * @Author: harpseal
 * @Date: 2022-06-09 15:42:52
 * @LastEditTime: 2022-10-17 10:57:56
 * @email: 844291270@qq.com
 */


#include <iostream>
#include <limits>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>
#include <boost/bind.hpp>
#include <boost/function.hpp>
#include <boost/lexical_cast.hpp>

const __int128_t INT128_MIN_VALUE = (__int128_t)1 << 127;
const __int128_t INT128_MAX_VALUE = -(INT128_MIN_VALUE + 1);

std::ostream& operator<<(std::ostream& os, __int128_t T) {
    if (T<0) os<<"-";if (T>=10 ) os<<T/10;if (T<=-10) os<<(-(T/10));
    return os<<( (int) (T%10) >0 ? (int) (T%10) : -(int) (T%10) ) ;
}



class GetSkValue {
public:
GetSkValue() {

}
template<class A>
A GetValue() {
    return a_;
}

private:
   double a_ = 12.35;
};

template<class A>
bool Comparelt(std::string value, GetSkValue& nodevalue) {
    A tmp = boost::lexical_cast<A>(value);
    if (tmp < nodevalue.GetValue<A>()) {
        return true;
    } else {
        return false;
    }
}
template<class A>
bool Comparegt(std::string value, GetSkValue& nodevalue) {
    A tmp = boost::lexical_cast<A>(value);
    if (tmp > nodevalue.GetValue<A>()) {
        return true;
    } else {
        return false;
    }

}
template<class A>
bool CompareEq(std::string value, GetSkValue& nodevalue) {
    A tmp = boost::lexical_cast<A>(value);
    if (tmp == nodevalue.GetValue<A>()) {
        return true;
    } else {
        return false;
    }
}
enum Valuetype {
    bool_type,
    int_type,
    double_type
};
enum Optype {
    EQ,
    LT,
    GT
};

typedef boost::function<bool (std::string, GetSkValue&) > ThreadFunctor;



template <class F>
class GenerateFuncByValueType {
public:
GenerateFuncByValueType(const F& f, std::string min, GetSkValue& kv) {
    func_ = boost::bind(f, min, kv);
}

    F func_;
};
template <class T>
ThreadFunctor FuncGenerater(Optype type) {
    switch(type) {
        case EQ:
            return boost::bind(CompareEq<T>, _1, _2);
        case LT:
            return boost::bind(Comparelt<T>, _1, _2);
        case GT:
            return boost::bind(Comparegt<T>, _1, _2);
        default:
            break;
    }
}



ThreadFunctor FuncGeneraterBy(Valuetype data_type, Optype op_type) {
    switch(data_type) {
        case int_type:
            return FuncGenerater<int>(op_type);
        case double_type:
            return FuncGenerater<double>(op_type);
        default:
        break;
    }
}
template <class T>
struct iterator_traits_s {
    typedef typename T::value_type value_type;
};
template <class T>
struct iterator_traits_s<T*> {
    typedef T value_type;
};

#include <vector>
#include <iostream>
#include <iterator>
#include <algorithm>

int main() {
    std::vector<int> result{1, 3, 3, 4, 4, 5, 6};
    std::vector<int>a (-1);
    std::copy(result.begin(), result.end(), 
        std::ostream_iterator<int>(std::cout, " "));
    result.swap(std::vector<int>(-1));
    std::copy(result.begin(), result.end(), 
        std::ostream_iterator<int>(std::cout, " "));
    return 0;
}
