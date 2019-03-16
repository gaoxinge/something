import timeit

lon1, lat1, lon2, lat2 = -72.345, 34.323, -61.823, 54.826
num = 500000

t = timeit.Timer("c1.great_circle(%f, %f, %f, %f)" % (lon1, lat1, lon2, lat2), "import c1")
print "c1:", t.timeit(num)

t = timeit.Timer("c2.great_circle(%f, %f, %f, %f)" % (lon1, lat1, lon2, lat2), "import c2")
print "c2:", t.timeit(num)

t = timeit.Timer("c3.great_circle(%f, %f, %f, %f)" % (lon1, lat1, lon2, lat2), "import c3")
print "c3:", t.timeit(num)

t = timeit.Timer("c4.great_circle(%f, %f, %f, %f, %d)" % (lon1, lat1, lon2, lat2, num), "import c4")
print "c4:", t.timeit(1)