D = {'A':6, 'B': 6, 'C': 6}
for key in D:
	print(key+" => %d" % D[key])
import os
p = os.popen('pwd')
print(p.next())
E = enumerate('spam')
I=iter(E)
print(next(I))
while True:
	try:
		print(next(I))
	except StopIteration:
		break

