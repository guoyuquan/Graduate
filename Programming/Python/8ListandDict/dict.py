d={'spam':2, 'ham':1, 'eggs':3};
print(d['spam']);
print(d);
print(len(d));
print('ham' in d);
print(list(d.keys()));
print('*****************');
d['ham']=['grill', 'bake', 'fry'];
print(d);
del d['eggs'];
print(d);
d['brunch']='Bacon';
print(d);
print(d.values());
print(d.keys());
print(d.items());
print(d.get('spam'));
print(d.get('toast'));
print(d.get('toast', 88));
d1={'toast':6, 'muffin':66};
d.update(d1);
print(d);
print('*************************');
print(d.pop('muffin'));
print(d.pop('toast'));
print(d);
print('**************************');
table={
	'Python': 'Guido van Rossum',
	'Perl': 'Larry Wail',
	'Tcl': 'John Ousterhout'
	};
language = 'Python';
creater = table[language];
print(creater);
for lang in table:
	print(lang, '\t', table[lang]);

rec={};
rec['name']='mel';
rec['age']=66;
rec['job'] = 'trainer/writer';
print(rec);


print('********************');
print(list(zip(['a', 'b', 'c'], [1,2,3])));
d=dict(zip(['a', 'b', 'c'], [1, 2, 4]));
print(d);

d={k:v for (k,v) in zip(['a', 'b', 'c'], [1,2,3])};
print(d);


print('******************');
d={x: x**2 for x in [1,2,3,4]};
print(d);
d={c: c*4 for c in 'SPAM'};
print(d);
d={c.lower(): c+'!' for c in ['SPAM', 'EGGS', 'HAM']};
print(d);

d=dict.fromkeys(['a', 'b', 'c'], 0);
print(d);

d={k:0 for k in ['a', 'b', 'c']};
print(d);

d={k: None for k in 'spam'};
print(d);
d=dict(a=1, b=2, c=3);
print(d);
k=d.keys();
print(k);
v=d.values();
print(v);
print(list(d.items()));
print(k[0]);
d={'a':1, 'b':2, 'c':3};
print(d);
ks=d.keys();
ks.sort();
for k in ks:print(k, d[k]);
sorted(d);
print(d);

