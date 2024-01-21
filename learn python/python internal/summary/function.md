# function

## 参数

### 参数个数

- 最多255个
- 超过255个，在编译器就会报错

```python
def g(n):
    s = "def g("
    for _ in range(n - 1):
        s += "x%d, " % _
    s += "x%d):\n    pass\n" % (n - 1)

    s += "g("
    for _ in range(n - 1):
        s += "%d, " % _
    s += "%d)\n" % (n - 1)
    return s


import ast
ast.parse(g(256))
```