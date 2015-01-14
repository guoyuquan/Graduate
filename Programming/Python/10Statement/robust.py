while True:
	reply = raw_input('Enter text: ')
	if reply == 'stop':
		break
	elif not reply.isdigit():
		print('Bad!'*8)
	else:
		print(int(reply)**2)
print('Bye')
