class tester:
	def __init__(self, start):
		self.state=start
	
	def __call__(self, label):
		print(label, self.state)
		self.state+=1
H=tester(99)
H('juice')
