json = {}
function Marshal(json_str)
	m, n = MarshalWorker(json_str, 1)
	if m == nil then
		return nil, 'error_type'
	else 
		return m
	end
end

function Unmarshal(lua_val)
	return UnmarshalWorker(lua_val)
end

function test(lua_val)
	return nil
end

json.Marshal = Marshal
json.Unmarshal = Unmarshal


local encode = function (s)
	local i = 1
	local ret = {}
	while i < string.len(s)+1 do
		local curchar = string.sub(s, i, i)
		if curchar == '\\' then
			table.insert(ret, '\\\\')
		elseif curchar == '"' then
			table.insert(ret, '\\"')
		elseif curchar == '/' then
			table.insert(ret, '\\/')
		elseif curchar == '\b' then
			table.insert(ret, '\\b')
		elseif curchar == '\n' then
			table.insert(ret, '\\n')
		elseif curchar == '\r' then
			table.insert(ret, '\\r')
		elseif curchar == '\t' then
			table.insert(ret, '\\t')
		elseif curchar == '\f' then 
			table.insert(ret, '\\f')
		else
			table.insert(ret, curchar)
		end
		i = i+1
	end
	s = table.concat(ret)
	s = encodeUTF8(s)
	return s
end

local utf_8 = function(uc)
	local a, b, c, d = string.byte(uc, 1, 4)
	a, b, c, d = a or 0, b or 0, c or 0, d or 0
	local val
	if a <= 0x7f then
		val = a
	elseif 0xc0 <= a and a<= 0xdf and b>=0x80 then
		val = (a - 0xc0) * 0x40 + b - 0x80
	elseif 0xe0 <= a and a <= 0xef and b >= 0x80 and c >= 0x80 then
		val = ((a - 0xe0) * 0x40 + b - 0x80)*0x40 + c -0x80
	elseif 0xf0 <= a and a <= 0xf7 and b > 0x80 and c >= 0x80 and d >=0x80 then
		val = (((a - 0xf0) * 0x40 + b - 0x80)*0x40 + c - 0x80)*0x40 + d - 0x80
	else
		return ""
	end
	if val < 0xffff then
		return string.format("\\u%.4x", val)
	elseif val <= 0x10ffff then
		val = val - 0x10000
		local high, low = 0xD800 + math.floor(val/0x400), 0xDC00 + ( val % 0x400)
		return string.format("\\u%.4x\\u$.4x", high, low)
	else
		return ""
	end
end

local substitute = function(str, pat, rep)
	if string.find(str, pat) then
		return string.gsub(str, pat, rep)
	else
		return str
	end
end

function encodeUTF8(ustr)
--	ustr = substitute(ustr, "[\1-\31\127]", utf_8)
	if string.find(ustr, "[\128-\255]") then
		ustr = substitute(ustr, "[\192-\223][\128-\255]", utf_8)
		ustr = substitute(ustr, "[\224-\239][\128-\255][\128-\255]", utf_8)
		ustr = substitute(ustr, "[\240-\255][\128-\255][\128-\255][\128-\255]", utf_8)
	end
	return ustr
end

local escape = function(s)
	local i = 1
	local ret = {}
	local n = string.len(s)+1
	while i < n do
		local cur = string.sub(s, i, i)
		if cur == '\\' then
			local curchar = string.sub(s, i+1, i+1)
			if curchar == '"' then
				table.insert(ret, '"')
				i = i+1
			elseif curchar == '/' then
				table.insert(ret, '/')
				i = i+1
			elseif curchar == 'b' then
				table.insert(ret, '\b')
				i = i+1
			elseif curchar == 'n' then
				table.insert(ret, '\n')
				i = i+1
			elseif curchar == 'r' then
				table.insert(ret, '\r')
				i = i+1
			elseif curchar == 't' then
				table.insert(ret, '\t')
				i = i+1
			elseif curchar == 'f' then
				table.insert(ret, '\f')
				i = i+1
			elseif curchar == '\\' then
				table.insert(ret, '\\')
				i = i+1
			else 
				table.insert(ret, cur)
				table.insert(ret, curchar)
				i = i+1
			end
		else 
			table.insert(ret, cur)
		end
		i = i + 1
	end
	s = table.concat(ret)
	return s
end

local decode = function(s)
	--[==[s = string.gsub(s, '\\"', '"')
	s = string.gsub(s, '\\/', '/')
	s = string.gsub(s, '\\b', '\b')
	s = string.gsub(s, '\\n', '\n')
	s = string.gsub(s, '\\r', '\r')
	s = string.gsub(s, '\\t', '\t')
	s = string.gsub(s, '\\f', '\f')
	s = string.gsub(s, '\\\\', '\\')
	]==]
	s = escape(s)
	local i = 1, 1
	local tmp = ''
	while i < string.len(s)+1 do
		i = string.find(s, '\\u', i) 
		if i then
			tmp = string.sub(s, 1, i-1)
			local uni = string.sub(s, i+2, i+5)
			local n = tonumber(uni, 16)
			local x
			if n < 0x80 then
				x = string.char(n % 0x80)
			elseif n<0x800 then
				x = string.char(0xC0 + math.floor(n/0x40), 0x80+(math.floor(n)%0x40))
			elseif n<=0xffff then
				x = string.char(0xE0 + math.floor(n/0x1000), 0x80 + (math.floor(n/0x40)%0x40), 0x80 + (math.floor(n)%0x40))
			elseif n<= 0x10ffff then
				x = string.char(0xF0 + math.floor(n/0x40000), 0x80 + (math.floor(n/0x1000)%0x40), 0x80 + (math.floor(n/0x40)%0x40), 0x80 + (math.floor(n)%0x40))
			end
			tmp = tmp ..x
			tmp = tmp ..string.sub(s, i+6)
			s = tmp
		else
			i = string.len(s)+1
		end
	end
	return s
end

function MarshalWorker(json_str, pos)
	local p = removeWhiteSpace(json_str, pos)
	local startChar = string.sub(json_str, p, p) 
	if startChar == '{' then 
		return MarshalObject(json_str, p + 1)
	end

	if startChar == '[' then
		return MarshalArray(json_str, p + 1)
	end

	local comment = string.sub(json_str, p, p+1)
	if comment == '/*' then
		local i = string.find(json_str, '*/')
		return MarshalWorker(json_str, i+1)
	end

	if comment == '//' then
		i = string.find(json_str, '\n')
		return MarshalWorker(json_str, i+1)
	end
	return nil, 'error_type'
end

function removeWhiteSpace(json_str, pos)
	local p = pos
	local n = string.len(json_str)
	while string.find(' \t\n\f\b', string.sub(json_str, p, p), nil, true) and p <=n  do
		p = p + 1
	end
	if p<=n then
		return p
	else
		return nil
	end
end

function MarshalObject(json_str, pos)
	local ret  = {}
	local n = string.len(json_str)
	while pos <= n do
		pos  = removeWhiteSpace(json_str, pos)
		if pos  == nil then
			return nil, 'error_type'
		end
		local startChar = string.sub(json_str, pos, pos)
		if startChar == '}' then
			return ret, pos+1
		end
		if startChar == ',' then
			pos  =removeWhiteSpace(json_str, pos + 1)
			if pos == nil or type(pos) ~= 'number' then
				return nil, 'error_type'
			end
			startChar = string.sub(json_str, pos, pos)
		end
		local key = ""
		local val = ""
		if startChar == '"' or startChar == "'" then
			key, pos = collectKey(json_str, pos+1, startChar)
			if key == nil then
				return nil, 'error_type'
			end
			key = decode(key)
		else
			return nil, 'error_type'
		end
		pos = removeWhiteSpace(json_str, pos)
		if pos == nil then
			return nil, 'error_type'
		end
		startChar = string.sub(json_str, pos, pos)
		if startChar == '{' then
			val, pos = MarshalObject(json_str, pos+1)
		elseif startChar == '[' then
			val, pos = MarshalArray(json_str, pos+1)
			if val == nil then
				return nil, 'error_type'
			end
		elseif startChar == '"' or startChar == "'" then
			val, pos = collectVal(json_str, pos+1, startChar)
			val = decode(val)
		elseif string.find('+-1234567890.eE', startChar) then
			val, pos = collectNum(json_str, pos)
			val = val * 1
		else
			val, pos = constant(json_str, pos)
		end
		if pos == nil or type(pos)~= 'number'  then
			return nil, 'error_type'
		end
		ret[key] = val
	end
	return nil, 'further implementation'
end

function MarshalArray(json_str, pos)
	local ret = {}
	local i = 1
	local index = 1
	local n = string.len(json_str)
	local p = pos
	while p <= n do
		val = ""
		p = removeWhiteSpace(json_str, p)
		if p == nil then
			return nil, 'error_type'
		end
		startChar = string.sub(json_str, p, p)
		if startChar == '"' or startChar == "'" then
			val, p = collectVal(json_str, p+1, startChar)
			val = decode(val)
		elseif startChar == '{' then
			val, p = MarshalObject(json_str, p+1)
		elseif startChar == '[' then
			val, p = MarshalArray(json_str, p+1)
		elseif string.find('+-1234567890.eE', startChar) then
			val, p = collectNum(json_str, p)
			val = tonumber(val)
			if val == nil then
				return nil, 'error_type'
			end
		elseif startChar == ']' then
			return ret, p+1
		elseif startChar == ',' then
			p = p + 1
		else 
			val, p = constant(json_str, p)
		end
		if p == nil  then
			return nil, 'error_type'
		end
		if startChar ~= ',' then 
			ret [index] = val
			index = index + 1
		end
		if type(p) ~='number' then
			return nil, 'error_type'
		end
	end
end

function nextQuote(json_str, pos, startChar)
	local stop = pos
	local n = string.len(json_str)+1
	while stop < n do
		if string.sub(json_str, stop, stop) == startChar then
			return stop
		end
		if string.sub(json_str, stop, stop) == '\\' then
			stop = stop + 1
		end
		stop = stop + 1
	end
	return stop
end

function collectKey(json_str, pos, startChar)
	local stop = nextQuote(json_str, pos, startChar)
	local i = string.find(json_str, ':', stop+1)
	if i == nil then
		return nil
	end
	return string.sub(json_str, pos, stop-1), i+1
end

function collectVal(json_str, pos, startChar)
	local stop = nextQuote(json_str, pos, startChar)
	return string.sub(json_str, pos, stop-1), stop+1
end

function collectNum(json_str, pos)
	local i = pos
	while string.find('+-1234567890.eE', string.sub(json_str, i, i)) do
		i = i + 1
	end
	return string.sub(json_str, pos, i-1), i
end

function constant(json_str, pos)
	consts = {["true"]=true, ["false"]=false, ["null"]='tmp'}
	for i, k in pairs(consts) do
		if string.sub(json_str, pos, pos + string.len(i)-1) == i then
			if i == "null" then
				return nil, string.len('null')+pos
			end
			return k, string.len(i) + pos
		end
	end
	return nil, nil
end

function UnmarshalWorker(lua_val)
	if lua_val == nil then
		return nil, 'error_type'
	end
	if next(lua_val) == nil then
		return "{}"
	end
	local flag, n = ArrayorDict(lua_val)
	if flag then
		return UnmarshalArray(lua_val, n)
	else
		return UnmarshalObject(lua_val)
	end
end

function UnmarshalArray(lua_val, n)
	local ret = {}
	table.insert(ret, "[")
	local i = 1
	while i < n+1 do
		if lua_val[i] == nil then
			table.insert(ret, "null")
			table.insert(ret, ',')
		else
			table.insert(ret, uniform(lua_val[i]))
			table.insert(ret, ",")
		end
		i = i+1
	end
	ret = table.concat(ret)
	ret = string.sub(ret, 1, string.len(ret)-1)
	ret = ret .."]"
	return ret
end

function UnmarshalObject(lua_val)
	local ret = {}
	table.insert(ret, '{')
	for k, v in pairs(lua_val) do
		if type(k) == 'number' then
			table.insert(ret, '"')
			table.insert(ret, tonumber(k))
			table.insert(ret, '"')
		else
			table.insert(ret, uniform(k))
		end
		table.insert(ret, ':')
		table.insert(ret, uniform(v))
		table.insert(ret, ",")
	end
	ret = table.concat(ret)
	ret = string.sub(ret, 1, string.len(ret)-1)
	ret = ret .."}"
	return ret
end

function ArrayorDict(lua_val)
	local max=0
	local flag = true
	for k, v in pairs(lua_val) do
		if type(k) =='number' and math.floor(k) == k and k>=1 then
			max = math.max(k, max)
		else 
			return false
		end
	end
	return true, max
end

function uniform(k)
	if k == nil then
		return 'null'
	elseif k == true then
		return 'true'
	elseif k == false then
		return 'false'
	elseif type(k) == 'string' then
		return '"' ..encode(k) ..'"'
	elseif type(k)== 'number' then
		return k
	elseif type(k) == 'table' then
		return UnmarshalWorker(k)
	else 
		return nil, 'error_type'
	end
end

function rightTable(o)
	local t = type(o)
	return (t=='string' or t=='boolean' or t=='number' or t=='nil') or (t=='function' and o==null)
end

	
return json
