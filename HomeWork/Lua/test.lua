require "json"
testcase = [==[[
    "JSON Test Pattern pass1",
	{"object with 1 member":["array with 1 element"]},
	    {},
		[],
		    -42,
			true,
			    false,
				null,
				    {
						    "integer": 1234567890,
							    "real": -9876.543210,
								    "e": 0.123456789e-12,
									    "E": 1.234567890E+34,
										    "":  23456789012E66,
											    "zero": 0,
												    "one": 1,
													    "space": " ",
														    "quote": "\"",
															    "backslash": "\\",
																    "controls": "\b\f\n\r\t",
																	    "slash": "/ & \/",
																		    "alpha": "abcdefghijklmnopqrstuvwyz",
																			    "ALPHA": "ABCDEFGHIJKLMNOPQRSTUVWYZ",
																				    "digit": "0123456789",
																					    "0123456789": "digit",
																						    "special": "`1~!@#$%^&*()_+-={':[,]}|;.</>?",
																							    "hex": "\u0123\u4567\u89AB\uCDEF\uabcd\uef4A",
																								    "true": true,
																									    "false": false,
																										    "null": null,
																											    "array":[  ],
																												    "object":{  },
																													    "address": "50 St. James Street",
																														    "url": "http://www.JSON.org/",
																															    "comment": "// /* <!-- --",
																																    "# -- --> */": " ",
																																	    " s p a c e d " :[1,2 , 3

																																	    ,

																																	    4 , 5        ,          6           ,7        ],"compact":[1,2,3,4,5,6,7],
																																		    "jsontext": "{\"object with 1 member\":[\"array with 1 element\"]}",
																																			    "quotes": "&#34; \u0022 %22 0x22 034 &#x22;",
																																				    "\/\\\"\uCAFE\uBABE\uAB98\uFCDE\ubcda\uef4A\b\f\n\r\t`1~!@#$%^&*()_+-=[]{}|;:',./<>?"
																																				    : "A key can be any string"
																																					},
																																					    0.5 ,98.6
																																					    ,
																																					    99.44
																																					    ,

																																					    1066,
																																					    1e1,
																																					    0.1e1,
																																					    1e-1,
																																					    1e00,2e+00,2e-00
																																					    ,"rosebud"] ]==]
																								

test = '  \n \t hello world'
test2 = [==[[[[[[[[[[[[[[[[[[[["你好"]]]]]]]]]]]]]]]]]]]]==]

test3 = [==[{
	    "JSON Test Pattern pass3": {
		            "The outermost value": "must be an object or array.",
			            "In this test": "It is an object."
				        }
				}
				]==]
--print( json.Marshal(testcase))
a = json.Marshal(testcase)
--print(a[20])
print(json.Unmarshal(a))
function printTable(a)
	for k, v in pairs(a) do
		if type(v) == 'table' then
			printTable(v)
		else
			print(k, v)
		end
	end
end
b = json.Marshal(test2)
--printTable(a)
c = json.Marshal(test3)
ret = json.Unmarshal(a)
a1 = json.Marshal(ret)


function check(a, b)
	local falg = false
	for k1, v1 in pairs(a) do
		if type(v1) == 'table' then
			flag = check(a[k1], b[k1])
		elseif b[k1] == v1 then 
			flag = true
		end
		if not flag then
			print(k1, v1, "table 1")
			print(k1, b[k1], "table 2")
		end
	end
	return flag
end

print(check(a, a1))
b1 = json.Marshal(json.Unmarshal(b))
print(check(b, b1))
c1= json.Marshal(json.Unmarshal(c))
print(check(c, c1))
test1 = [==[{1, ["2"]=2}]==]
--a = json.Marshal(test1)
print(json.Unmarshal({1, ["2"]=2}))
print(json.Unmarshal({nil, nil, 1}))
--print(json.Unmarshal(json.Marshal(test1)))

print(json.Unmarshal({b="cd"}))
test5= '{{},{{},{}}}'
print( json.Marshal(test5))
print(json.Unmarshal({{},{{},{}}}))
test6='["mismatch"}'
print(json.Marshal(test6))
test7='["Unclosed array"'
print(json.Marshal(test7))
test8 = '"A JSON payload should be an object or array, not a string."'
print(json.Marshal(test8))
test9 = '{unquoted_key: "keys must be quoted"}'
print(json.Marshal(test9))
test10 = '["extra comma",]' --not pass
print(json.Marshal(test10))
test11 = '["double extra comma",,]'--not pass
print(json.Marshal(test11))
test12 = '[   , "<-- missing value"]' -- not pass
print(json.Marshal(test12))
test13 = '["Comma after the close"],' -- not pass
print(json.Marshal(test13))
test14 = '["Extra close"]]' --not pass
print(json.Marshal(test14))
test15 = '{"Extra comma": true,}'
print(json.Marshal(test15))
test16 = '{"Extra value after close": true} "misplaced quoted value"'
print(json.Marshal(test16)) --not pass
test17 = '{"Illegal expression": 1 + 2}'
print(json.Marshal(test17))
test18 = '{"Illegal invocation": alert()}'
print(json.Marshal(test18))
test19 = '{"Numbers cannot have leading zeroes": 013}'
print(json.Marshal(test19) )--not pass
test20 = '{"Numbers cannot be hex": 0x14}'
print(json.Marshal(test20))
test21 = '["Illegal backslash escape: \x15"]'
print(json.Marshal(test21)) -- not pass
test22 = '[\naked]'
print(json.Marshal(test22) )
test23 = '["Illegal backslash escape: \017"]'
print(json.Marshal(test23) ) --not pass
test24 = '[[[[[[[[[[[[[[[[[[[["Too deep"]]]]]]]]]]]]]]]]]]]]'
print(json.Marshal(test24))
test25 = '{"Missing colon" null}'
print(json.Marshal(test25))
test26 = '{"Double colon":: null}'
print(json.Marshal(test26))
test27 = '{"Comma instead of colon", null}'
print(json.Marshal(test27))
test28 = '["Colon instead of comma": false]'
print(json.Marshal(test28))
test29 = '["Bad value", truth]'
print(json.Marshal(test29))
test30 = '["Bad value", truth]'
print(json.Marshal(test30))
test31 = '["test31tabcharacterinstring"]'
print(json.Marshal(test31))
test32 = [==[["line
break"]]==]
print(json.Marshal(test32)) -- not pass
test33 = '[0e]'
print(json.Marshal(test33))
test34 = '[0e+]'
print(json.Marshal(test34))
test35 = '[0e+-1]'
print(json.Marshal(test35))
test36 = '{"Comma instead if closing brace": true,'
print(json.Marshal(test36))
test37 = '["mismatch"}'
print(json.Marshal(test37))
index = 1
tmp = {}
while index < 10000 do
	tmp[index]='你好，中国'
	index = index + 1
end
print('ok')
s = json.Unmarshal(tmp)
a = json.Marshal(s)
print(json.Unmarshal(a))
test38 = '{"abc":"haha}'
print(json.Marshal(test38))
test39 = '{{}"'
print(json.Marshal(test39))
test40 = '{{"",}'
print(json.Marshal(test40))
test41 = '{{?}}'
print(json.Marshal(test41))
test42 = '{"he'
print(json.Marshal(test42))
test43 = '{["{]'
print(json.Marshal(test43))
