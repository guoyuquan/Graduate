import java.util.regex.*;

public class TheReplacements{
	public static void main(String [] args) throws Exception{
		String s=TextFile.read("TheReplacements.java");
		Matcher mInput=Pattern.compile("/\\*!(.*)!\\*/", Pattern.DOTALL).matcher(s);
		if(mInput.find())
			s=mInput.group(1);
		s=s.replaceAll(" {2, }", " ");
		s=s.replaceAll("(?m)^ +", " ");
		System.out.println(s);
		s=s.replaceFirst("[aeiou]", "(VOWEL1)");
		StringBuffer sbuf=new StringBuffer();
		Pattern p=Pattern.compile("[aeiou]");
		Matcher m=p.matcher(s);
		while(m.find())
			m.appendReplacement(sbuf, m.group().toUpperCase());
		m.appendTail(sbuf);
		System.out.println(sbuf);
	}
}
