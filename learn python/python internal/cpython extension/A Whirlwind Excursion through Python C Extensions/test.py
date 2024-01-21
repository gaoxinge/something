# test ext1
import ext1

print(ext1.hello_world)
print(ext1.hello_world())
help(ext1)

# test ext2
import ext2

print(ext2.string_peek("Whirlwind", 5))
try:
    print(ext2.string_peek("whirlwind"))
except Exception as e:
    print(e)
try:
    print(ext2.string_peek("whirlwind", "0"))
except Exception as e:
    print(e)
print(ext2.string_peek("whirlwind", 2000))

print(ext2.string_peek2("Whirlwind", 5))
try:
    print(ext2.string_peek2("whirlwind"))
except Exception as e:
    print(e)
try:
    print(ext2.string_peek2("whirlwind", "0"))
except Exception as e:
    print(e)
try:
    print(ext2.string_peek2("whirlwind", 2000))
except Exception as e:
    print(e)
    
a = [1, 2, 3]
b = ext2.insert_powers1(a, 2)
print(a, b)

a = [1, 2, 3]
b = ext2.insert_powers2(a, 2)
print(a, b)

# test ext3
import ext3

cdict = ext3.CountDict()
print(cdict)
print(cdict.set("a", "hello"))
print(cdict.set("b", "world"))
print(cdict.dict)
print(cdict.count)