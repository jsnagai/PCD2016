import java.util.*;
import java.util.concurrent.Semaphore;	

public class CalcThr{
	public static double[] A;
	public static double[] B;
	public static double pe=0.0;

	public static void main(String args[]) throws InterruptedException{
		if(args.length != 1 || !args[0].matches("\\d*[^0]\\d*")) {
			System.err.println("usage: java CalcThE MaxThreads.");
			System.exit(1);
		} 
		int MaxThreads = Integer.parseInt(args[0]);
		int N = 10000;
		Thread[] th;
		RunThr[] rh;
		double[] array;
		double final_sum=0;
		rh = new RunThr[MaxThreads];
		th = new Thread[MaxThreads];
		A = new double[N];
		B = new double[N];
		Semaphore sem = new Semaphore(1,true);
		Random g = new Random();
                for(int k=0;k<N;k++){
                        A[k]=1.0;
                	B[k]=1.0;
		}
		long  start = System.currentTimeMillis();
		for(int i=0;i<MaxThreads;i++){
			rh[i] = new RunThr(i,N,MaxThreads,sem);
			th[i] = new Thread(rh[i]);
			th[i].start();
		}
		for(int i=0;i<MaxThreads;i++){
			th[i].join();
		}
		long time =  System.currentTimeMillis() - start;
		System.out.println("Resultado = "+pe);
		System.out.println("\nEm"+time+".ms\n");
	}
}
