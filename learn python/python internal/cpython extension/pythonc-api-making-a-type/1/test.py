import ccv

cdict = ccv.CountDict("name")
print(cdict.set("a", "hello"))
print(cdict.set("b", "world"))
print(cdict.getKeys())
print(cdict.getVals())
print(cdict.getName())
print(cdict.dict)
print(cdict.keys)
print(cdict.vals)
print(cdict.count)
print(cdict.name)