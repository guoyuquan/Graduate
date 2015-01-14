class C1:
	pass
class C2:
	pass
class C3(C1, C2):
	def setname(self, who):
		self.name = who
I1=C3()
I1.setname('bob')
print(I1.name)
