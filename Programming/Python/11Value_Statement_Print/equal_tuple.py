nudge = 1
wink = 2
nudge, wink = wink, nudge
print(nudge, wink)
print(type(nudge))
[a, b, c] = (1, 2, 3)
print(a, c)
(a, b, c) = "ABC"
print(a, c)
string='SPAM'
a, b, c, d=string
print(a, d)
#a, b, c=string
a, b, c = string[0], string[1], string[2:]
print(a, b, c)
print('****************************')
a, b, c=list(string[:2])+[string[2:]]
print(a, b, c)
print('****************************')
((a, b), c)=('SP', 'AM')
print(a, b, c)
red, green, blue=range(3)
print(red, blue)
print('****************************')
l = [1, 2, 3, 5, 6]
while l:
	front, l = l[0], l[1:]
	print(front, l)
for (a, b, c) in [(6, 6, 6), (6, 6, 6)]:
	print(a, b, c)
#a, b, c='ab'
