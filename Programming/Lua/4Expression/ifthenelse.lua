local i = 1
a={"hello", ",world"}
while a[i] do
	print(a[i])
	i=i+1
end

repeat
	line=io.read()
until line~=""
print(line)


