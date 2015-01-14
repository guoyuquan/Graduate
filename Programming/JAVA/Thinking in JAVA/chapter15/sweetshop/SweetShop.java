class Candy{
	static {System.out.println("Loading Candy");}
}

class Gum{
	static {System.out.println("Loading Gum");}
}

class Cookie{
	static {System.out.println("Loading Cookie");}
}

public class SweetShop{
	public static void main(String[] args){
		System.out.println("inside main");
		new Candy();
		System.out.println("After creating candy");
		try{
			Class.forName("Gum");
		}catch(ClassNotFoundException e){
			System.out.println("Could not find Gum");
		}

		System.out.println("After Class.forName(\"Gun\")");
		new Cookie();
		System.out.println("After Creating Cookie");
	}
}
