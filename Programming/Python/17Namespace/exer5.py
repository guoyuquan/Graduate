X = 'Spam'
def func():
	X='Ni'
	def nested():
		print(X)
	nested()
func()
print(X)
