f=open('data.txt', 'w');
print(f.write('Hello\n'));
f.write('World\n');
f.close();
f=open('data.txt');
text=f.read();
print(text);
print(text.split());
print(dir(f));
data=open('data.txt', 'rb').read();
print(data);
print(data[4:8]);