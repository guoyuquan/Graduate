S = 'spam'
offset=0
for item in S:
	print(item, 'appears at offset', offset)
	offset+=1
print('***************************')
for (offset, item) in enumerate(S):
	print(item+'appears at offset %d' % offset)
for item in enumerate(S):
	print(item)
E = enumerate(S)
print(next(E))
#while E:
#	next(E)
print([c * i for (i, c) in enumerate(S)])
