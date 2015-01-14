a = {x=10, y=20}
print(a)
print(a.x, a.y)
polyline = {color="blue", thickness=2, npoints=4,
		{x=0, y=0},
		{x=-10, y=0},
		{x=-10, y=1},
		{x=0, y=1},
	}
print(polyline[2].x)
print(polyline[4].y)
print(polyline.color)
