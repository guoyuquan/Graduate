from functools import reduce
print(reduce((lambda x, y: x + y), [1, 2, 3]))
print(reduce((lambda x, y: x * y), [1, 2, 3]))
reduce((lambda x, y: x*y), [])
