import sys
temp=sys.stdout
sys.stdout=open('log.txt', 'a')
print('spam')
print(1, 2, 3)
sys.stdout.close()
sys.stdout=temp
print('back here')
print(open('log.txt').read())
sys.stderr.write(('Bad!'*8)+'\n')
print >> sys.stderr, 'Bad!'*8
