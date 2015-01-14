f = open('file_parse.py')
L = f.readlines()
L = [line.rstrip() for line in L]
print(L)
for line in L:
	print(line)
for line in [l.rstrip() for l in open('file_parse.py')]:
	print(line)
print('************************1*******************')
for line in [l.upper() for l in open('file_parse.py')]:
	print(line)
print('************************2*******************')
for line in [l.split() for l in open('file_parse.py')]:
	print(line)
print('************************3*******************')
for line in [l.replace(' ', '!') for l in open('file_parse.py')]:
	print(line)
print('************************4*******************')
for (a, b) in [('sys' in l, l) for l in open('file_parse.py')]:
	print(a, b)
print('***********************5********************')
for line in [l for l in open('file_parse.py') if l[0] == 'f']:
	print(line)
