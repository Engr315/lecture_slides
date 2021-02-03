import cPopcount

print (cPopcount.cPopcount(0))

print (cPopcount.cPopcount(1))

l = list(range(10))

print (sum(map(cPopcount.cPopcount,l)))
print (cPopcount.cPopcount_all(l))

