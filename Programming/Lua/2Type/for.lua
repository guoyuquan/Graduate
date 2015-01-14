a = {}
for i = 1, 10 do
	a[i]=io.read()
end

for i = 1, 10 do
	print(a.tonumber(i))
end

for i = 1, 10 do
	print(a[i])
end
