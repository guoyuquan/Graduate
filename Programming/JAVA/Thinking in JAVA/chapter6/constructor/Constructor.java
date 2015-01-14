class cons{
	public cons(){System.out.println("1");}
	public cons(int x){this();System.out.println(x);}
}

public class Constructor{
	public static void main(String []args){
		cons x=new cons(12);
	}
}
