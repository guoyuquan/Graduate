interface test{
	void f();
}

class some implements test{
	public void f(){System.out.println("derived f()");}
}

public class Interface{
	public static void main(String [] args){
		some s=new some();
		s.f();
	}
}
