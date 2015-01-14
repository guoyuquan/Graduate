L1 = [1,2,3]
L2 = [6, 6, 6]
print(type(zip(L1, L2)))
print(zip(L1, L2))
for (x, y) in zip(L1, L2):
	print(x, y, '--', x+y)
