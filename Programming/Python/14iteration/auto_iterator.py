L = [1, 2, 3]
for x in L:
	print(x**2)
I = iter(L)
while True:
	try:
		print(I.next()**2)
	except StopIteration:
		break

