L = [1, 2, 3, 6, 6]
print(sum(L))
print('any', any(L))
print('all', all(L))
print('max', max(L))
print('min', min(L))
print('&&'.join([l for l in open('test.py')]))

print('**********************')
Z = zip((1,2,3), (6, 6, 6,))
I=iter(Z)
I2=iter(Z)
print(I.next())

print(I2.next())
print(I.next())
print(I2.next())
print(next(I))
print(next(I2))
