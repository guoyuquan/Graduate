public class Private{
	private void f(){
		System.out.println("private f()");
	}
	public static void main(String []args){
		Private p=new Derived();
		p.f();
	}
}

class Derived extends Private{
	//@Override
	public void f(){
		System.out.println("public f()");
	}
}
