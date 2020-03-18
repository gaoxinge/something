## [现在招个Java后端怎么这么难，撩人的回复率简直低到可怕，明明显示已读，但就是没人回复，这是为什么呢？](https://www.zhihu.com/question/376985972/answer/1062406134)

### 跳动字节

- 1

```python
"""
字节跳动在北京有N个工区，形成一个环状，
Bytebus是往返在各个工区的通勤车，按工区的顺序行驶，其中第 i 个工区有汽油 gas[i] 升。
你有一辆油箱容量无限的的Bytebus，从第 i 个工区开往第 i+1 个工区需要消耗汽油 cost[i] 升。
你从其中的一个工区出发，开始时油箱为空。
如果你可以绕环路行驶一周，则返回出发时工区的编号，否则返回 -1。	

输入: 	
    gas  = [1,2,3,4,5]	
    cost = [3,4,5,1,2]	
输出: 
    3
"""


class Ring:

    def __init__(self, r):
        self.r = r
        
    def __getitem__(self, i):
        return self.r[i % len(self.r)]

    def __len__(self):
        return len(self.r)


def index(gas, cost):
    r = [g - c for g, c in  zip(gas, cost)]
    r = Ring(r)
    for i in range(len(r)):
        left = 0
        for j in range(len(r)):
            left += r[i + j]
            if left < 0:
                break
        else:
            return i
    return -1


gas = [1, 2, 3, 4, 5]
cost = [3, 4, 5, 1, 2]
print(index(gas, cost))
```