abstract class Base{
	abstract void f();
}

class Derived extends Base{
	void f(){System.out.println("extended");}
}

public class Abstract{
	static void func(Base s){s.f();}
	public static void main(String [] args){
		//Base b=new Base();
		Derived d=new Derived();
		func(d);
	}
}
