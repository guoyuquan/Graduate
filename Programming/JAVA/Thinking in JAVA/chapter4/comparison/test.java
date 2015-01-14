public class test{
	public static void main(String []args){
		comp("Hello", "World");
	}
	private static void comp(String s1, String s2){
		System.out.println(s1==s2);
		System.out.println(s1!=s2);
		//System.out.println(s1>s2);
		System.out.println(s1.equals(s2));
		//System.out.println(s1<s2);
	}
}
