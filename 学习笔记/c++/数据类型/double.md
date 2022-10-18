<!--
 * @FilePath: /github/harpseal/学习笔记/c++/数据类型/double.md
 * @Author: harpseal
 * @Date: 2022-07-21 09:41:29
 * @LastEditTime: 2022-07-21 09:59:08
 * @email: 844291270@qq.com
-->
# c++中的double类型

## nan值相关

### 概念

NaN（Not a Number，非数）是计算机科学中数值数据类型的一类值，表示未定义或不可表示的值。常在浮点数运算中使用。首次引入NaN的是1985年的IEEE 754浮点数标准。  -- 百度百科

### 返回nan的运算

* 至少有一个参数是NaN的运算
* 不定式
    下列除法运算：0/0、∞/∞、∞/−∞、−∞/∞、−∞/−∞
    下列乘法运算：0×∞、0×−∞
    下列加法运算：∞ + (−∞)、(−∞) + ∞
    下列减法运算：∞ - ∞、(−∞) - (−∞)
* 产生复数结果的实数运算。例如：
    对负数进行开偶次方的运算
    对负数进行对数运算
    对正弦或余弦到达域以外的数进行反正弦或反余弦运算
-- 百度百科

c++代码
```
double nan = std::numeric_limits<double>::quiet_NaN();  // nan
or
double nan =  sqrt(-2);  // -nan
```

### 在c++中的表现

nan类型不会参与比较运算
```
    if (nan <= 3.14) {
        std::cout << nan << "  <= 3.14 ";
    } else if (nan > 3.14) {
        std::cout << nan << " > 3.14 ";
    } else {
        // nan值会走这个分支
        std::cout << nan << " is nan ";  
    }
```
如果nan值存在于vector，然后对此vector进行排序
```
排序前
{100000.0, -0.1,-10.0, 10.0, 0.1,0,-10000.0,nan, std::numeric_limits<double>::max(), 1.2, -1.2, 2.2, -4.2}
排序后
{-10000 -10 -0.1 0 0.1 10 100000 nan -4.2 -1.2 1.2 2.2 1.79769e+308}
```
可以看出，此vector依据nan值所在的位置，将vector分为两部分，此两部分分别进行排序