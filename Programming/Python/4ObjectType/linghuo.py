L=[];
print(type(L));
print(type(type(L)));
if type(L)==type([]):
	print('yes');
if type(L)==list:
	print('yes');
if isinstance(L, list):
	print('yes');
#if isinstance(list, L):
#	print('yes');
