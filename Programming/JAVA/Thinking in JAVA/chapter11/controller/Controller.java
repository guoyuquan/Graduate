import java.util.*;
abstract class Event{
	private long eventTime;
	protected final long delayTime;
	public Event(long delayTime){
		this.delayTime=delayTime;
		start();
	}
	public void start(){
		eventTime=System.nanoTime()+delayTime;
	}
	public boolean ready(){
		return System.nanoTime()>=eventTime;
	}
	public abstract void action();
}

public class Controller{
	private List<Event> eventList=new ArrayList<Event>();
	public void addEvent(Event c){eventList.add(c);}
	public void run(){
		while(eventList.size()>0)
			for(Event e:new ArrayList<Event>(eventList))
				if(e.ready()){
					System.out.println(e);
					e.action();
					eventList.remove(e);
				}
	}
}
