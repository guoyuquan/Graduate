import java.util.*;
class Apple{
	private static int counter=0;
	private final int id=counter++;
	public int id(){return id;}
}

class Orange{}

public class ApplesAndOrangesWithGenerics{
	public static void main(String[] args){
		ArrayList<Apple> apples=new ArrayList<Apple>();
		for(int i=0; i<3; i++)
			apples.add(new Apple());
		//apples.add(new Orange());
		for(int i=0; i<apples.size(); i++)
			System.out.println(apples.get(i).id());
		for(Apple c:apples)
			System.out.println(c.id());
	}
}
