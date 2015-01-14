keys = ['spam', 'eggs', 'toast']
vals = [6, 6, 6]
print(list(zip(keys, vals)))
D = {}
for (k, v) in zip(keys, vals):
	D[k]=v
print(D)
print('**********************')
D = dict(zip(keys, vals))
print(D)
