import java.util.*;

public class AddingGroups{
	public static void main(String[] args){
		Collection<Integer> collection=new ArrayList<Integer>(Arrays.asList(1,2,3,4,5,6));
		Integer[] moreInts={7,8,9,10};
		collection.addAll(Arrays.asList(moreInts));
		Collections.addAll(collection, 11, 12, 13, 14, 15, 16);
		Collections.addAll(collection, 16, 16, 16, 16, 16, 16);
		List <Integer> lsit =Arrays.asList(16,16,16);
		lsit.set(1,99);
	}
}
