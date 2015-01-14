while True:
	name = raw_input('Enter name: ')
	if name == 'stop':
		break
	age = raw_input('Enter age: ')
	if age.isdigit():
		print('Hello, '+name+' => ', int(age)**2)
	else:
		print('Bad age')
