def printdebug(func):
	def __decorator():
		print('enter the login')
		func()
		print('exit the login')
	return __decorator

@printdebug
def login():
	print('in login')

login()
