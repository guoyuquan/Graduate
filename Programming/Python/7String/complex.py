import sys;
print('My {1[spam]} runs {0.platform}'.format(sys, {'spam': 'laptop'}));
print('My {config[spam]} runs {sys.platform}'.format(sys=sys, config={'spam':'laptop'}));
somelist=list('SPAM');
print(somelist);
print('first={0[0]}, third={0[2]}'.format(somelist));
print('first={0}, last={1}'.format(somelist[0], somelist[-1]));
parts=somelist[0], somelist[-1], somelist[1:3];
print('first={0}, last={1}, middle={2}'.format(*parts));
