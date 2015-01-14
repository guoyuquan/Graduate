S1 = 'abc'
S2 = 'xyz123'
print(map(None, S1, S2))
print(list(map(ord, 'spam')))
print('**************************')
res = []
for c in 'spam': res.append(ord(c))
print(res)
