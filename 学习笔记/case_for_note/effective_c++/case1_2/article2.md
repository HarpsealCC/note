#条款02 尽量以const，enum，inline替换#define

形似函数的宏
```
#define CALL_WITH_MAX(a, b) f(a) > (b) ? (a) : (b))
```

会产生问题的情况：
```
int a=5， b=0;
CALL_WITH_MAX(++a, b);   // a被累加2次
CALL_WITH_MAX(++a, b+10)  // a被累加1次
```

可以使用inline模板函数对其进行包装
```
template<typename T>
inline void CallWithMax(const T& a, const T& b) {
    f(a > b ? a : b);
}
```


```
对于单纯常量而言，最好以const对象或者enum替换#define
对于形似函数的宏，最好改用inline函数替换#define

e.g.
之后也不用匿名空间的参数表示数组大小，直接使用enum进行替换
```


###测试时的其他心得-成员变量赋值--个人总结

成员变量在声明时一般可以赋初值，也可以在构造函数的成员列表中赋初值。

const成员变量与引用成员变量是必须赋初值的（确切原因后续补充，当前猜测，const如果不赋初值就没有存在的意义，引用则必须有个实实在在的地址作为依靠才有意义）

const与引用成员变量，一般在构造函数的参数列表进行赋值，不是必须，网上有一部分资料写的必须，是有问题的

static 成员变量必须在类外进行定义，但是static const 的integral类型是可以在声明时候进行初始化的。其他类型必须在类外（见Test3）
