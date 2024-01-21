import sys
from foo import f, g, h

a = "qwer123412eawrqwer1234"
print a,
print sys.getrefcount(a)
b = f(a)
print b,
print sys.getrefcount(b),
print sys.getrefcount(a)
c = g(a)
print c,
print sys.getrefcount(c),
print sys.getrefcount(a)
d = h(a)
print d,
print sys.getrefcount(d),
print sys.getrefcount(a)
d = a
print d,
print sys.getrefcount(d),
print sys.getrefcount(a)


def f(a):
    print "in g", sys.getrefcount(a)
    return 1
    

a = "1234324ewrqwer2341234"
print "before f", sys.getrefcount(a)
b = f(a)
print "after f", sys.getrefcount(a)


def g(a):
    print "in g", sys.getrefcount(a)
    return a
    
a = "qwer123421423rqwer234234"
print "before g", sys.getrefcount(a)
b = g(a)
print "after g", sys.getrefcount(a)
print "after g", sys.getrefcount(b)