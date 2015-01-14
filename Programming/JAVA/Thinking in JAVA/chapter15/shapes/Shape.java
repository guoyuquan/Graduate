import java.util.*;

abstract class Shapes{
	void draw(){System.out.println(this + ".draw()");}
	abstract public String toString();
}

class Circle extends Shapes{
	public String toString(){return "Circle";}
}

class Square extends Shapes{
	public String toString(){return "Square";}
}

class Triangle extends Shapes{
	public String toString(){return "Triangle";}
}

public class Shape{
	public static void main(String [] args){
		List<Shapes> shapeList=Arrays.asList(new Circle(), new Square(), new Triangle());
		for(Shapes shape : shapeList)
			shape.draw();
	}
}
