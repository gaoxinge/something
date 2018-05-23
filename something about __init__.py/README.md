# something about \_\_init\_\_.py

## import: thread safe and cache mechanism

- [import inside of a Python thread](https://stackoverflow.com/questions/12389526/import-inside-of-a-python-thread)

## prepare

```
- test.py
- t
  - __init__.py
  - b.py
```

```python
# b.py
# -*- coding: utf-8 -*-

class B(object):
    def __init__(self, b):
        self.b = b
```

```python
# __init__.py
# -*- coding: utf-8 -*-

import random
from b import B

b = B(random.random())
print "b.b", b.b
```

## test1

```python
# test.py: only one print
# -*- coding: utf-8 -*-
from t import b
x = b

from t import b
y = b

x == y
```

## test2

```python
# test.py: only one print
# -*- coding: utf-8 -*-
import threading

def f(x):
    from t import b
    print x
    
t1 = threading.Thread(target=f, args=(5,))
t2 = threading.Thread(target=f, args=(8,))
t1.start()
t2.start()
t1.join()
t2.join()
```

## test3

```python
# test.py: two print
# -*- coding: utf-8 -*-
from multiprocessing import Process

def f(x):
    from t import b
    print x
    
if __name__ == "__main__":
    p1 = Process(target=f, args=(5,))
    p2 = Process(target=f, args=(8,))
    p1.start()
    p2.start()
    p1.join()
    p2.join()
```