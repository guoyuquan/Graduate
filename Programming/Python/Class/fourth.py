class Person:
	def __init__(self, name, job=None, pay=0):
		self.name = name
		self.job = job
		self.pay = pay

if __name__ == '__main__':
	bob = Person('Bob')
	print(bob)
