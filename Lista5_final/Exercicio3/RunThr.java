import java.util.Random;
import java.util.concurrent.ThreadLocalRandom;
import java.util.concurrent.locks.*;

class RunThr implements Runnable{
	private int id;
	public static final Object locker = new Object();

	public RunThr(int aid){
		if(CalcThr.flag){
			CalcThr.flag = false;
			CalcThr.counter = 0;
			CalcThr.runF = false;
		}
		id = aid;
	}		
	public void UpdateGlobals(){

		synchronized(locker){
			if(id==0){
				// watch_counter()
				try {
					if(CalcThr.counter<CalcThr.count_limit){
						System.out.printf("watch_counter(): Thread %d, going into wait...\n", id);
						while(!CalcThr.runF)locker.wait();
						System.out.printf("watch_counter(): Thread %d, condition signal received\n",id);
						CalcThr.counter += 125;
						System.out.printf("watch_counter(): Thread %d, now counter = %d\n", id, CalcThr.counter);
					}
				} catch (InterruptedException e){
					System.err.println(e.toString());
				}            
			}
			else{
				// inc_counter()
				for(int i=0; i<CalcThr.tcount; i++){
					CalcThr.counter++;
					if(CalcThr.counter==CalcThr.count_limit){
						System.out.printf("inc_counter(): Thread %d, counter = %d, threshold reached\n", id, CalcThr.counter);
						CalcThr.runF = true;                    
						locker.notifyAll();                  
						System.out.printf("inc_counter(): Thread %d, counter = %d, just sent signal\n", this.id, CalcThr.counter);
					}
					System.out.printf("inc_counter(): Thread %d, counter = %d, unlocking locker\n", this.id,CalcThr.counter);
					try {
						Thread.sleep(500);
					} catch (InterruptedException e){
						System.err.println(e.toString());
					}
				}
			}
		}
	}

	public void run(){
		if(this.id==0)
			System.out.printf("Starting watch_counter(): Thread %d\n", id);
		else
			System.out.printf("Starting inc_counter(): Thread %d\n", id);
		this.UpdateGlobals(); 

	}

}
