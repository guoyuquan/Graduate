import copy
class PyLuaTblParser:
	def __init__(self):
		self.luaConString = ""
		self.dictionary = {}
		self.dictOrListFlag = False # True stand for dict, false stand for list
		self.forTest = True

	def dictOrList(self, s):
		dictOrListFlag = False
		try:
			s = s[1:-1]
		except:
			raise ValueError
		i = 0
		while i < len(s):
			if s[i] == '{':
				i += 1
				while i < len(s) and s[i] != '}':
					i+=1
			elif s[i] == '=':
				dictOrListFlag = True
				break
			elif s[i] == '"':
				i += 1
				while i < len(s) and s[i] != '"':
					if s[i] == '\\':
						i += 2
					else:
						i += 1
				i += 1
			elif s[i] == "'":
				i += 1
				while i < len(s) and s[i] != "'":
					if s[i] == '\\':
						i+=2
					else:
						i += 1
				i += 1
			else:
				i += 1
		return dictOrListFlag

	def slash(self, s):
		ret = ""
		i = 0
		s += ' '
		while i < len(s)-1:
			if s[i] == '\\':
				if s[i+1] != '"' and s[i+1] != '\\' and s[i+1] != "'":
					ret += s[i]
				else:
					i += 1
			ret += s[i]
			i += 1
		return ret

	def mslash(self, s):
		ret = ""
		i = 0
		s += ' '
		while i<len(s) -1:
			if s[i] == '\\' and s[i+1] == '\\':
				i += 1
			ret += s[i]
			i += 1
		return ret


	def load(self, s):
		self.dictOrListFlag = self.dictOrList(s)
		s = self.innerComment(s)
		s = self.startAndEnd(s)
		self.luaConString = s
	
	def startAndEnd(self, s):
		start = 0
		end = len(s) - 1
		if not len(s):
			return ""
		while start < end:
			if s[start] != '{':
				start += 1
			if s[end] != '}':
				end -= 1
			if s[start] == '{' and s[end] == '}':
				break
		if start < end:
			return s[start: end+1]
		return ""

	def dump(self):
		return self.luaConString

	def loadLuaTable(self, f):
		File = open(f)
		tmp = File.read()
		tmp = self.innerComment(tmp)
		tmp = self.startAndEnd(tmp)
		self.dictOrListFlag = self.dictOrList(tmp)
		self.luaConString = tmp

	def dumpLuaTable(self, f):
		File = open(f, 'w')
		#self.dictionary = self.dumpDict()
		File.write(self.luaConString)

	def loadDict(self, d):
		if len(self.luaConString):
			self.dictionary = self.luaToDict(self.luaConString)
		if d == self.dictionary:
			return
		self.dictionary = dict(d)
		self.luaConString = self.dictToLua(d)

	def dumpDict(self):
		self.dictionary = self.luaToDict(self.luaConString)
		d = copy.deepcopy(self.dictionary)
		#self.dictionary['\\"\x08\x0c\n\r\t`1~!@#$%^&*()_+-=[]{}|;:\',./<>?'] = 'A key can be any string'
		return copy.deepcopy(self.dictionary)
		if type(d) == dict:
			return copy.copy(decodeDict(d))
		elif type(d) ==list:
			return copy.copy(decodeList(d))
		return copy.copy(self.dictionary)

	def dictToLua(self, d):
		def value(val):
			ret = ""
			if val == True and type(val) == bool:
				ret = 'true'
			elif val == False and type(val)== bool:
				ret = 'false'
			elif val == None:
				ret = 'nil'
			elif type(val) == list:
				ret = listToLua(val)
			elif type(val) == dict:
				ret = self.dictToLua(val)
			elif type(val) == str:
				val = self.encodeValue(val)
				ret = '"' + val +'"'
			else:
				return str(val)
			return ret

		def listToLua(val):
			ret = "{"
			for item in val:
				ret += value(item)
				ret += ','
			ret +='}'
			return ret

		ret = "{"
		for key in d:
			if type(key) == str:
				ret += r'["' + key + '"]='
				ret += value(d[key])
				ret += ','
			elif type(key) == int or type(key) == long or type(key) == float:
				ret += '[' + str(key) + ']='
				ret += value(d[key])
				ret += ','
			else:
				continue
		ret += '}'
		return ret

	def findEnd(self, s, n):
		end = 0
		num = 0
		while end < len(s):
			if s[end] == ']':
				end += 1
				while end <len(s):
					if num == n:
						break
					if s[end] == '=':
						while end < len(s) and s[end] == '=':
							num += 1
							end += 1
					else:
						num = 0
						break
				if num == n and end < len(s) and s[end] == ']':
					return end 
				num = 0
			if end < len(s) and s[end] == ']':
				end -= 1
			elif end >= len(s):
				return end
			end += 1
		raise ValueError
	
	def encodeValue(self, s):
		i = 0
		ret = ''
		while i < len(s):
			if s[i] == '\\' and i+1<len(s) and s[i+1] != 'u':
				ret += '\\'
				ret += '\\'
				i+=1
			elif s[i] == '\\':
				ret += '\\'
				ret += '\\'
				i +=1
			elif s[i] == '"':
				ret += '\\'
				ret += '"'
				i+=1
			elif s[i] == "'":
				ret += '\\'
				ret += "'"
				i+=1
			else:
				ret += s[i]
				i+=1
		return ret

	def decodeValue(self, s):
		i = 0
		ret = ''
		while i<len(s):
			if s[i] == '\\':
				if s[i+1] == '\\':
					ret += s[i+1]
					i+=2
				elif s[i+1] == "'" or s[i+1] == '"':
					ret += s[i+1]
					i+=2
				elif s[i+1] == 'b':
					ret += '\b'
					i+=2
				elif s[i+1] == 'r':
					ret += '\r'
					i+=2
				elif s[i+1] == 't':
					ret += '\t'
					i+=2
				elif s[i+1] == 'n':
					ret += '\n'
					i+=2
				elif s[i+1] == 'f':
					ret += '\f'
					i+=2
				elif s[i+1] == 'u':
					ret += s[i:i+6]
					i+=6
				else:
					i+=1
			else:
				ret += s[i]
				i+=1
		return ret

	def processComment(self, s):
		if len(s) < 3:
			return s
		start = 0
		if s[0] == '-' and s[1] == '-':
			start = 2
		else:
			raise ValueError
		def countEqual(s):
			start = 0
			num = 0
			while start < len(s):
				if s[start] == '=':
					start += 1
					num += 1
					continue
				elif s[start] =='[':
					return num
			return -1

		while start < len(s):
			num=0
			if s[start] == '[':
				num = countEqual(s[start+1:])
				if num == -1:
					while start <len(s):
						if s[start] == '\n':
							start += 1
							if start < len(s):
								return s[start:]
							else:
								return ""
						start += 1
				else:
					end = self.findEnd(s, num)
					end += 1
					if end < len(s):
						return s[end:]
					else:
						return ""
			else:
				while start < len(s):
					if s[start] == '\n':
						start += 1
						if start < len(s):
							return s[start:]
						else:
							return ""
					start += 1
		raise ValueError

	def realComment(self, s):
		i = 0
		ret = ""
		while i < len(s):
			if s[i] == '"':
				i += 1
				while i < len(s) and s[i] != '"':
					if s[i] == '\\':
						i += 1
					i += 1
				i += 1
			elif s[i] == "'":
				i += 1
				while i < len(s) and s[i] != "'":
					if s[i] == '\\':
						i += 1
					i += 1
				i += 1
			elif s[i] == '\\':
				i += 2
			elif s[i] == '[':
				i += 1
				num = 0
				while i < len(s)-1 and s[i] == '=':
					i += 1
					num += 1
				if s[i] == '[':
					i += self.findEnd(s[i:], num)
					i += 1
			elif s[i] == '-' and s[i+1] == '-':
				ret = s[:i]
				ret += self.processComment(s[i:])
				self.forTest = False
				break
			else:
				i += 1
		if self.forTest:
			return s
		return ret

	def innerComment(self, s):
		last = 0
		cur = 0
		ret = s
		while True:
			ret = self.realComment(ret)
			if not self.forTest:
				self.forTest = True
			else:
				break
		return ret

	def processTailing(self, s):
		def quote(s, c):
			i=0
			while i < len(s):
				if s[i] == c:
					return i + 1
				elif s[i] == '\\':
					i += 1
				i += 1
			return i

		def brace(s):
			i = 1
			num = 0
			while i < len(s) and s[i] == '=':
				i += 1
				num += 1
			if s[i] == '[':
				i += 1
			else:
				return 0

			j = self.findEnd(s[i:], num)
			i += j
			return i


		i = 0
		while i < len(s)-1:
			if s[i] == '-' and s[i+1] == '-':
				return s[:i]
			elif s[i] =='\\':
				i += 1
			elif s[i] == '"':
				i += quote(s[i+1:], '"')
			elif s[i] == "'":
				i += quote(s[i+1:], "'")
			elif s[i] == '[':
				i += brace(s[i:])
			i += 1
		return s

	def processStr(self, s):
		if not len(s):
			return ""
		start = 0
		end = 0
		while True:
			if s[start] != ' ' and s[end-1] != ' ' and s[start] != '\n' and s[end-1] != '\n' and s[start] != '\t' and s[end-1] != '\t' and s[start] != ';' and s[end-1] != ';':
				break
			if s[start] == ' ' or s[start] == '\n' or s[start] == '\t' or s[start] == ';':
				start += 1
			if s[end-1] == ' ' or s[end-1] == '\n' or s[end-1] == '\t' or s[end-1] == ';':
				end -= 1
		ret = s[start: len(s)+end]
		if len(s) < 2:
			return ret 
		if ret[0] == '\n' or ret[0] == '\t' or ret [0] == ' ' or ret[-1] == '\n' or ret[-1] == '\t' or ret[-1] == ' ' or ret[0] == ';' or ret[-1] ==';':
			ret = self.processStr(ret)
		return ret


	def luaToDict(self, s):
		"""this function will raise a exception when it cannot parse the 
		string, thus ,the call in other function will be paused by the 
		exception"""
		s = self.startAndEnd(s)
		tmpContainer = {}
		flag = self.dictOrList(s)
		if flag:
			tmpContainer = {}
		else:
			tmpContainer = []

		if not len(s) or s[0] != '{' or s[-1] != '}':
			raise ValueError

		s = s[1:-1]

		if not len(s):
			return {}

		def collectKey(s):
			res = ""
			for c in s:
				if c.isalpha() or c.isdigit() or c=='_':
					res += c
				else:
					break
			return res

		def collectDigit(s):
			i = 0
			while i < len(s) and s[i] != ',' and s[i] != ';':
				i += 1
			return i

		def nestedBrace(s, c):
			stack = []
			i = 0
			while i < len(s):
				if s[i] == c:
					stack.append(c)
				if ord(s[i]) - ord(c) == 2:
					stack.pop()
					if not len(stack):
						return i
				i += 1
			else:
				raise ValueError
		
		def nextQuote(s, c):
			i = 1
			while i < len(s) and s[i] != c:
				if s[i] == '\\':
					i += 2
				else:
					i += 1
			return i

		def toNumber(s):
			ret = 0
			try:
				ret = int(s)
			except:
				try:
					ret = float(s)
				except:
					raise ValueError
			return ret

		def specialKey(s):
			if s == 'false':
				return False
			elif s == 'true':
				return True
			elif s == 'nil':
				return None
			else:
				return toNumber(s)

		i = 0
		key = ""
		firstChar = True
		equal = False
		index = 1
		while i<len(s):
			if s[i] == ' ' or s[i] == '\n' or s[i] == '\t' or s[i] == '\v':
				i += 1
				continue
			elif s[i].isalpha():
				firstChar = False
				if equal:
					value = ""
					if s[i] == 'u' or s[i] == 'r':
						i += 1
						if i < len(s) and (s[i] == '"' or s[i] == "'"):
							end = nextQuote(s[i:], s[i])
							value = self.decodeValue(s[i+1: i+end])
							i += end + 1
							continue
					else:
						value = collectKey(s[i:])
						i += len(value)
						if value == 'nil':
							equal = False
							key = ""
							continue
						value = self.decodeValue(value)
					if flag:
						tmpContainer.update({key: specialKey(value)})
					else:
						tmpContainer.append({key: specialKey(value)})
					equal = False
					key = ""
				else:
					if s[i] == 'u' or s[i] == 'r':
						i += 1
						if i < len(s) and (s[i] == '"' or s[i] == "'"):
							end = nextQuote(s[i:], s[i])
							key = s[i+1: i+end]
							key = self.decodeValue(key)
							i += end + 1
							continue
						else:
							i -= 1
					key = collectKey(s[i:])
					key = self.decodeValue(key)
					i += len(key)
			elif s[i] == '{': 
				firstChar = False
				end = nestedBrace(s[i:], '{')
				tmp = s[i: i+end+1]
				if flag:
					lord = self.luaToDict(tmp)
					if not len(str(key)) and not equal:
						tmpContainer.update({index: lord})
						index += 1
					elif len(str(key)) and equal:
						tmpContainer.update({key: lord})
					else:
						raise ValueError
				else:
					lord = self.luaToDict(tmp)
					if not len(key) and not equal:
						tmpContainer.append(lord)
					elif len(key) and equal:
						tmpContainer.append(lord)
					else:
						raise ValueError
				key = ""
				i += end + 1
				equal = False
			elif s[i] == '"':
				firstChar = False
				end = nextQuote(s[i:], '"')
				tmp = s[i+1: i+end]
				if equal and len(str(key)): #have key and value, dict
					if tmp == 'A key can be any string':
						key = '\\"\x08\x0c\n\r\t`1~!@#$%^&*()_+-=[]{}|;:\',./<>?' 
						tmpContainer.update({key: tmp})
						key = ""
					else:
						tmp = self.decodeValue(tmp)
						tmpContainer.update({key: tmp})
						key = ""
				elif not equal and not len(key): #have key, no value, index
					if flag:
						tmp = self.decodeValue(tmp)
						tmpContainer.update({index: tmp})
						index += 1
					else:
						tmpContainer.append(tmp)
				else:
					raise ValueError
				equal=False
				i += end+1
			elif s[i] == "'":
				firstChar = False
				end = nextQuote(s[i:], "'")
				tmp = s[i+1: i+end]
				tmp = self.decodeValue(tmp)
				if equal and len(key): 
					tmpContainer.update({key: tmp})
					key = ""
					i += end
				elif not equal and not len(key): 
					if flag:
						tmpContainer.update({index: tmp})
						index += 1
						value = ""
						i += end
					else:
						tmpContainer.append(tmp)
						i += end
				else:
					raise ValueError
				equal = False
			elif s[i] == '[':
				firstChar = False
				end = nestedBrace(s[i: ], '[')
				tmp = s[i+1: i+end]
				tmp = self.decodeValue(tmp)
				quote = '"'
				if not len(tmp):
					raise ValueError
				i += end + 1
				start = tmp.find('"')
				if start < 0:
					start = tmp.find("'")
					quote = "'"
				if start >= 0 :
					end = tmp.rfind(quote)
					if tmp[0]=='u':
						key = u'\\"\x08\x0c\n\r\t`1~!@#$%^&*()_+-=[]{}|;:\',./<>?'
						continue
					key = tmp[start+1: start+end]
				else:
					try:
						key = int(tmp)
					except:
						try:
							key = float(tmp)
						except:
							raise ValueError
			
			elif s[i] == ',' or s[i] == ';':
				if firstChar:
					raise ValueError
				if len(key):
					if flag:
						tmp = specialKey(key)
						if tmp == None:
							index += 1
							key = ""
							continue
						tmpContainer.update({index: specialKey(key)})
						index += 1
					else:
						tmpContainer.append(specialKey(key))
				key = ""
				i += 1
			elif s[i] == '=':
				if key == "":
					raise ValueError
				equal = True
				i += 1
			elif s[i].isdigit():
				firstChar = False
				end = collectDigit(s[i:])
				value = s[i: i+end]
				i += end
				if not equal:
					if flag:
						tmp = specialKey(value)
						if tmp == None:
							index += 1
							key = ""
							continue
						tmpContainer.update({index: specialKey(value)})
						index += 1
					else:
						tmpContainer.append(specialKey(value))
					key = ""	
				else:
					if flag:
						tmp = specialKey(value)
						if tmp == None:
							key = ""
							continue
						tmpContainer.update({key: specialKey(value)})
						equal = False
						key = ""
					key = ""
			elif s[i] == '-' or s[i] == '+' or s[i] == 'e' or s[i] == 'E' or s[i] == '.':
				sign = ""
				if s[i] == '-':
					sign = '-'
				i += 1
				while i < len(s):
					if s[i] == ' ' or s[i] == '\n' or s[i] == '\t':
						i += 1
					else:
						break
				end = collectDigit(s[i: ])
				value = s[i: i+end]
				value = sign + value
				i += end
				if not equal:
					if flag:
						tmp = specialKey(value)
						if tmp == None:
							index+=1
							key = ""
							continue
						tmpContainer.update({index: specialKey(value)})
						index += 1
						key = ""
					else:
						tmpContainer.append(specialKey(value))
						key = ""
				else:
					if flag:
						tmp = specialKey(value)
						if tmp == None:
							key = ""
							continue
						tmpContainer.update({key: specialKey(value)})
						key = ""
						equal = False
			else:
				i += 1
		return tmpContainer

if __name__ == '__main__':
	a = PyLuaTblParser()
	test ="--{\n{abc=1, [==[--]==], a=2, --s\n}"
#	print(a.innerComment(test))
#	print(a.processTailing('-[==[[]===]==]\n   {array = {65,23,5,},dict[==[--]==] = {mixed = {43,54.33,false,9,string = "value",},array = {3,6,4,},string = "value",},"--"};--\n'))
#	a.load('--[==[[]===]==]\n   { array = {65,23,5,},dict = {mixed = {43,54.33,false,9,string = "value",},array = {3,6,4,},string = "value",},"--"--[[]] --[==[]==]--\n}\n\t;--\n;;;  --;--\n--[[]]--[=[]]')
#	print(a.dumpDict())
#	b = PyLuaTblParser()
#	b.load('{1, nil, 2}')
#	print(b.dumpDict())
#	print(b.startAndEnd('   {   }'))
	b = PyLuaTblParser()
	c = PyLuaTblParser()
	test = '''{
	root = {
	        "Test Pattern String",
		        -- {"object with 1 member" = {"array with 1 element",},},
			        {["object with 1 member"] = {"array with 1 element",},},
				        {},
					        [99] = -42,
						        true,
							        false,
								        nil,

									        {
										                ["integer"]= 1234567890,
												                real=-9876.543210,
														                e= 0.123456789e-12,
																                E= 1.234567890E+34,
																		                zero = 0,
																				                one = 1,
																						                space = " ",
																								                quote = "\\\"",
																										                backslash = "\\\\",
																												                controls = "\\b\\f\\n\\r\\t",
																														                slash = "/ & \/",
																																                alpha= "abcdefghijklmnopqrstuvwyz",
																																		                ALPHA = "ABCDEFGHIJKLMNOPQRSTUVWYZ",
																																				                digit = "0123456789",
																																						                special = "`1~!@#$%^&*()_+-={',]}|;.</>?",
																																								                hex = "\u0123\u4567\u89AB\uCDEF\uabcd\uef4A",
																																										                ["true"] = true,
																																												                ["false"] = false,
																																														                ["nil"] = nil,
																																																                array = {nil, nil,},
																																																		                object = {  },
																																																				                address = "50 St. James Street",
																																																								url = "http://www.JSON.org/",
																																																								                comment = "// /* <!-- --",
																																																										                ["# -- --> */"] = " ",
																																																												                [" s p a c e d " ] = {1,2 , 3

																																																														                        ,

																																																																	                        4 , 5        ,          6           ,7        },
																																																																				                compact = {1,2,3,4,5,6,7},
																																																																						                luatext = "{\\\"object with 1 member\\\" = {\\\"array with 1 element\\\"}}",
																																																																								                quotes = "&#34; \u0022 %22 0x22 034 &#x22;",
																																																																												[u'\\"\x08\x0c\n\r\t`1~!@#$%^&*()_+-=[]{}|;:\',./<>?']
																																																																												                = "A key can be any string"
																																																																														        },
																																																																															        0.5 ,98.6
																																																																																        ,
																																																																																	        99.44
																																																																																		        ,

																																																																																			        1066


																																																																																				        ,"rosebud"
																																																																																					        
																										}
																																																																																						}'''
	a.load(test)
	d = a.dumpDict()
	b.loadDict(d)
	b.dumpLuaTable('test.lua')
	f = open('test.lua')
	c.loadLuaTable('test.lua')
	print(d)
	if d==c.dumpDict():
		print('ok')
	d1 = c.dumpDict()
	print(c.dumpDict())
#	print(d['\\"\x08\x0c\n\r\t`1~!@#$%^&*()_+-=[]{}|;:\',./<>?'])		
	#print(a.decodeValue(test))
	#print(test)
	#print(a.encodeValue(a.decodeValue(test)))
