print(len([1,2,3]));
print([1,2,3]+[5,6]);
print(['Ni!']*4);
print(str([1,2])+"36");
print([1,2]+list("36"));
print(3 in [1, 2, 3]);
for x in [1, 2, 3]:
	print(x, ' ');

res=[c*4 for c in 'SPAM'];
print(res);
res=[];
for c in 'SPAM':
	res.append(c*4);

print(res);
print(list(map(abs, [-1, -2, 0, 1, 2])));

l=['spam', 'Spam', 'SPAM'];
l[1]='eggs';
print(l);
l[0:2]=['eat', 'more'];
print(l);
l.append('please');
print(l);
l.sort();
print(l);


l=['abc', 'ABD', 'aBe'];
print(l.sort());
print(l);
print(l.sort(key=str.lower));
print(l);
print(l.sort(key=str.lower, reverse=True));
print(l);

print(sorted(l, key=str.lower, reverse=True));
print(l);
print(sorted([x.lower() for x in l], reverse=True));
print(l);

l=[1,2];
l.extend([3,4,5]);
print(l);
print(l.pop());
print(l);
l.reverse();
print(l);
print(list(reversed(l)));

print('*******************');
l=['spam', 'eggs', 'ham'];
print(l.index('eggs'));
l.insert(1, 'toast');
print(l);
l.remove('eggs');
print(l);
l.pop(1);
print(l);
l=[1,2,3,5,6];


print('*******************');
print(l);
del l[0];
print(l);
del l[1:];
print(l);
