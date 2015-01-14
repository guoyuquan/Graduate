def interssect(seq1, seq2):
	res = []
	for x in seq1:
		if x in seq2:
			res.append(x)
	return res
print(interssect('something', ['a', 'b', 'e']))
print(interssect('something', []))
