def f1():
	X=68
	def f2():
		print(X)
	return f2
a=f1()
a()
