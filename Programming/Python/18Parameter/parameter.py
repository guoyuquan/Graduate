def f(a, b, c):
	print(a, b, c)
f(1, 2, 3)
f(c=1, b=2, a=3)
def fun1(a, b=2, c=3):
	print(a, b, c, sep=',')
fun1(6)
fun1(1)
fun1(6, 6, 6)
def fun2(*args):
	print(args)
fun2(1)
fun2(6, 6)
fun2(6, 6, "hello")
def fun3(**args):
	print(args)
fun3(a=1, b=2)
def fun5(a, *b, **c):
	print(a, b, c)
fun5(1, 2, 3, x=1, y=6)
def kwonly(a, *b, c):
	print(a, b, c)
kwonly(1, 2, c=3)
