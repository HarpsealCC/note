## const 修饰常量
### 普通类型const
```
char greeting[] = "Hello";
char* p = greeting;  // non-const pointer, non-const data
const char* p = greeting;  // non-const pointer, const data
char* const p = greeting;  // const pointer, non-const data
const char* const p = greeting;  // const pointer, const data
```
可以这么记，对于 char *p，p为指针类型，但是在添加const时将char去掉
那么const char* p就是const *p，而*p代表具体值，就是值不变的（const data）
同理，将char* const p转为* const p，p为指针，就是指针不变（const point）


### 迭代器类型const
```
std::vector<int> vec(10);
std::cout << "size " << vec.size() << std::endl;

const std::vector<int>::iterator iter = vec.begin();
*iter = 10; // OK
++iter; // error

std::vector<int>::const_iterator citer = vec.begin();
*citer = 11; // error
++citer; // OK
```
记得方法可以按照普通类型来类比
const std::vector<int>::iterator iter 将iterator去掉，iter为指针，因此为指针不变（const point）
至于const_iterator没什么歧义，就认为它是值不变的指针就可以


## const 修饰函数声明
### const 修饰返回值

const修饰返回值可以有效防止用户使用函数不当导致的诡异问题
```
class Rational {};
Rational operator* (const Rational& lhs, const Rational& rhs) {
    Rational ab;
    return ab;
}
(a*b) = c; 是可以编译过的
```
添加了const对返回值赋值操作也是没有影响的，在返回自定义对象时，多多使用const做修饰
内置类型不用有这样的顾虑[^注1]，不过应该也可以在返回值使用const进行修饰


[^注1]:*如果一个函数的返回值为内置类型，那么改动函数返回值不会合法,原因未知*


### const 修饰参数
```
参数使用const修饰是个良好的编程习惯，一方面是对如何使用参数有理解，能够明确哪些参数是需要修改，哪些是不能被修改的，
另一方面是能避免一些模糊的错误，尤其是在调试接口的时候，一旦出现莫名其妙的问题，首先可以排除是由于参数被修改引起的。
```

### const 修饰成员函数
```
将const添加到成员函数上的目的就是，为了确认该成员函数可作用于const对象上。
两个成员函数如果只在常量性（有没有const）不同，是可以被重载的。


个人理解，这就意味着，const用来修饰的函数应当是用来重载某些对const对象操作有需求的接口，而不应当单独存在（纯个人理解）。

除非是定死了一定不进行对象修改的接口，那感觉和const对象又是一样的功能了。归根到底还是const对象调用const接口。

const对象可以通过指针进行修改。
const TextBlock ctb("World");
std::cout << ctb[0] << std::endl;
char* pc = (char*)&ctb[0];  // 书里不用进行强转，但是实际会报错
*pc = 'J';

可以使用mutable修饰成员，这样即使是const接口，也可以对这个成员变量进行修改

```

### const与non-const成员函数应避免重复
```
良好的风格应该是用const成员函数来实现非const成员函数的功能。
虽然转型不是一件好事儿，但是在消除重复代码上，还是可以做个妥协的。
const char& operator[](std::size_t postition) const {  
    return text[postition];
}
char& operator[](std::size_t position) {
    return 
        const_cast<char&>(
            static_cast<const TextBlock&>(*this)[position]);
}
此外，要用const实现非const函数，如果反过来的话，非const函数会修改成员的值，这会导致const接口的效用消失
char& operator[](std::size_t postition) {
    a = 2;  // 这会导致const接口效用消失，且不容易debuf
    return text[postition];
}
const char& operator[](std::size_t postition) const {
    // 这会导致const接口效用消失，且不容易debuf
    return static_cast<const char&>(const_cast<TextBlock&>(*this)[postition]);
}

```