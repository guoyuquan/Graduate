import java.util.*;
public class SimpleSet{
	public static void main(String[] args){
		Collection<Integer> c=new Set<Integer>();
		for(int i=0; i<10; i++){
			c.add(i);
			c.add(i);
		}
		for(Integer i:c)
			System.out.print(i+" ");
		System.out.println();
	}
}
