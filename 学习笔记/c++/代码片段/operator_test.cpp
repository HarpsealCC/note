/**
 * @file operator_test.cpp
 * @brief
 * @author liuchengzhuo (844291270@qq.com)
 * @version 1.0
 * @date 2023-11-23
 *
 * @copyright Copyright (c) 2023
 *
 * @par 修改日志:
 * <table>
 * <tr><th>Date       <th>Version <th>Author
 * <tr><td>2023-11-23 <td>1.0     <td>liuchengzhuo
 * <th>Description
 * <td>用于练习一些运算符
 * </table>
 */
#include <cstring>
#include <iostream>
class CMyString {
public:
    /**
     * @brief Construct a new CMyString object
     * 必须要注意，在pdate为空的时候需要给CMyString至少分配一个字节的内存，不然会析构函数会崩溃
     * @param  pdata            My Param doc
     */
    CMyString(char* pdata = nullptr) {
        if (pdata == nullptr) {
            pdata_  = new char[1];
            *pdata_ = '\0';
        } else {
            int length = strlen(pdata);
            pdata_     = new char[length + 1];
            strcpy(pdata_, pdata);
        }
    }
    CMyString(const CMyString& str) {
        int len = strlen(str.pdata_);
        pdata_  = new char[len + 1];
        strcpy(pdata_, str.pdata_);
    }
    ~CMyString() {
        delete[] pdata_;
    }

    CMyString&           operator=(const CMyString& str);
    friend std::ostream& operator<<(std::ostream& os, CMyString& str);

private:
    char* pdata_ = nullptr;
};
/**
 * @brief
 * 一般的实现方案，在delete之后如果出现new的异常，原对象的数据会被破坏
 */
// CMyString& CMyString::operator=(const CMyString& str) {
//     if (&str == this) {
//         return *this;
//     }
//     delete[] pdata_;
//     pdata_ = nullptr;
//     pdata_ = new char[strlen(str.pdata_) + 1];
//     strcpy(pdata_, str.pdata_);
//     return *this;
// }
/**
 * @brief 通用的实现方案，
 */
CMyString& CMyString::operator=(const CMyString& str) {
    if (&str != this) {
        CMyString strtemp(str);
        char*     ptemp = strtemp.pdata_;
        strtemp.pdata_  = pdata_;
        pdata_          = ptemp;
    }
    return *this;
}
std::ostream& operator<<(std::ostream& os, CMyString& str) {
    os << str.pdata_;
    return os;
}

int main() {
    CMyString my_string("1234556788");
    std::cout << my_string << std::endl;
    CMyString my_string2;
    std::cout << my_string2 << std::endl;
    my_string2 = my_string;
    std::cout << my_string2 << std::endl;
    return 0;
}