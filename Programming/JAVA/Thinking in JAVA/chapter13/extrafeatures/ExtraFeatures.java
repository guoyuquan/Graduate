class MyException extends Exception{
	private int x;
	public MyException(){}
	public MyException(String msg){super(msg);}
	public MyException(String msg, int x){
		super(msg);
		this.x=x;
	}
	public int val(){return x;}
	public String getMessage(){
		return "Detail Message: "+x+super.getMessage();
	}
}

public class ExtraFeatures{
	public static void f() throws MyException{
		System.out.println("Throwing MyException from f()");
		throw new MyException();
	}

	public static void g() throws MyException{
		System.out.println("Throwing MyException from g()");
		throw new MyException("Originated in g()");
	}

	public static void h() throws MyException{
		System.out.println("Throwing MyException from h()");
		throw new MyException("originated in h()",  47);
	}

	public static void main(String [] args){
		try{
			f();
		}catch(MyException e){
			e.printStackTrace(System.out);
		}

		try{
			g();
		}catch(MyException e){
			e.printStackTrace(System.out);
		}

		try{
			h();
		}catch(MyException e){
			e.printStackTrace(System.out);
			System.out.println("e.val()="+e.val());
		}
	}
}
