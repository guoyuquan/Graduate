D={'food':'spam', 'quantity':4, 'color':'pink'};
print(D['food']);
D['quantity']+=1;
print(D);
Dic={};
Dic['name']='Bob';
Dic['job']='dev';
Dic['age']=40;
print(Dic);
rec={'name':{'first':'Bob', 'last':'Smith'}, 'job':['dev', 'mgr'], 'age':40.5};
print(rec['name']['last']);
print(rec['job']);
print(rec['job'][-1]);
rec['job'].append('janitor');
print(rec);
Ks=list(D.keys());
print(Ks);
Ks.sort();
for key in Ks:
	print(key, '=>', D[key]);
for c in 'spam':
	print(c.upper());
x=4;
while x>0:
	print('spam!'*x);
	x-=1;
for keys in sorted(D):
	print(keys, '=>', D[keys]);
squares=[x**2 for x in[1,2,3,5,6]];
print(squares);
squares=[];
for x in [1,2,3,5,6]:
	squares.append(x**2);
print(squares);
D['e']=99;
print(D);
#print(D['f']);
if not 'f' in D:
	print('missing');
if 'f' in D:
	print("there");
value=D.get('x', 0);
print(value);
value=D['x'] if 'x' in D else 6;
print(value);
