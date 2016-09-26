import java.util.Random;

public class CalcThr{
	public static int MaxThreads = 3;
	public static int tcount = 10;
	public static int count_limit = 12;
    public static int counter;
 	public static Boolean runF;
  	public static Boolean flag = true;
  	

	public static void main(String args[]) throws InterruptedException{
		Thread[] th;
		RunThr[] rh;
		int final_sum=0;
		rh = new RunThr[MaxThreads];
		th = new Thread[MaxThreads];
		
		long  start = System.currentTimeMillis();

		for(int i=0;i<MaxThreads;i++){
			rh[i] = new RunThr(i);
			th[i] = new Thread(rh[i]);
			th[i].start();
		}
		for(int i=0;i<MaxThreads;i++){
			th[i].join();
		}
		long time =  System.currentTimeMillis() - start;
		System.out.printf ("Main(): Waited on %d threads. Final value of count = %d. Done.\n", MaxThreads, counter);

	}
}
