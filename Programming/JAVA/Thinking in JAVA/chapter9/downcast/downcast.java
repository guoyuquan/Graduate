class use{
	public void f(){System.out.println("base f()");}
	public void g(){System.out.println("base g()");}
}

class more extends use{
	public void f(){System.out.println("derived f()");}
	public void g(){System.out.println("derived g()");}
	public void u(){System.out.println("u()");}
}

public class downcast{
	public static void main(String [] args){
		use []x={new use(), new more()};
		x[0].f();
		x[1].g();
		((more)x[1]).u();
		((more)x[0]).u();
	}
}
