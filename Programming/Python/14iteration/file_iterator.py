f = open('file_iterator.py')
print(dir(f))
#f.__next__()
while True:
	s=f.readline()
	if not s:
		break
	print(s)
#while True:
#	print(f.__iter__())
for line in open('file_iterator.py'):
	print(line.upper())
