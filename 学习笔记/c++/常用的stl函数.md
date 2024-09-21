# 工作与刷题时常用的函数

### 数字转化为字符串
```
#include <string>

std::string str = std::to_string(num);
```

### 判断字符串是否为数字

```
#include <cctype>


bool ret = isdigit(ch)
```

### 初始化二维数组
```
#include <vecotr>

int rows = 101, cols = 101, initial_value = 1;

std::vector<std::vector<int>> dp(rows,std::vector<int>(cols, initial_value));
```

### 字符串子串的位置
```
#include <string>

int = str.find(substr);
```

### 反转容器

```
#include <algorithm>

std::vector<int> nums;
std::reverse(nums.begin(), nums.end());
```

### list移动元素

```
// lru中，将list中的一个iter挪到开始
#include <list>

auto it = cacheMap[key];
cacheItems.splice(cacheItems.begin(), cacheItems, it);
```