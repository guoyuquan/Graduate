f = open('next.py')
print(next(f))
print(f.next())
L = [6, 6, 6]
I = iter(L)
print(iter(f) is f)
while True:
	print(I.next())
