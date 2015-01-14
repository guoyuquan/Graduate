public class Test{
	public static void main(String [] args){
		System.out.println(test(1,10,11));
		System.out.println(test(1,10,6));
	}
	private static boolean test(int begin, int end, int t){
		if(t<begin||t>end)
			return false;
		return true;
	}
}
