def fun():
	x=6
	return (lambda n: x**2)
	#return action

x = fun()
print(x(2))
