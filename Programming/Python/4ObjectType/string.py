S='Python';
Y="Python";
print(S[0]);
print(Y[1]);
print(S[-1]);
print(Y[-6]);
print(S[1:3]);
print(S[:]);
print(S[:3]);
print(S[1:]);
print(S+'xyz');
print(S*8);
S='z'+S[1:];
print(S);
print(S.find('on'));
print(S.replace('on', "XYZ"));
print(S);
line='aaa, bbb, ccc';
print(line.split(','));
print(S.upper);
print(S.isalpha());
line='something\n';
print(line);
print(line.rstrip());
print('%s, eggs, and %s'%('spam', "SPAM!"));
print('{0}, eggs, and {1}'.format('spam', 'SPAM!'));
print(dir(S));
print(len(S));
print(ord('\n'));
msg="""aaaaa
bbbbb
cccc
"""
print(msg);
