test=open('test.txt', 'w');
test.write('hello text\n');
print(test.write('goodbye text\n'));
test.close();
test=open('test.txt');
print(test.readline());
print(test.readline());
print(test.readline());
test.close();
print(open('test.txt').read());
d={'a':1, 'b':2};
f=open('datafile.pk1', 'wb');
import pickle;
pickle.dump(d, f);
f.close();
f=open('datafile.pk1', 'rb');
e=pickle.load(f);
print(d);
