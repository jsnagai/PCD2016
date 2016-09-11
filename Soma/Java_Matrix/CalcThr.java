import java.util.Random;

public class CalcThr{

public static double[][] array1;
public static double[][] array2;
public static double[][] Res;

	public static void main(String args[]) throws InterruptedException{
		if(args.length != 1 || !args[0].matches("\\d*[^0]\\d*")) {
			System.err.println("usage: java CalcThE MaxThreads.");
			System.exit(1);
		} 
		int MaxThreads = Integer.parseInt(args[0]);
		int N = 1000;
		Thread[] th;
		RunThr[] rh;
		Random g = new Random();

		int final_sum=0;
		rh = new RunThr[MaxThreads];
		th = new Thread[MaxThreads];
		array1 = new double[N][N];
		array2 = new double[N][N];
		Res = new double[N][N];
	
		long  start = System.currentTimeMillis();
		for(int i=0;i<N;i++){
			for(int j=0;j<N;j++){
			array1[i][j] = g.nextDouble();
			array2[i][j] = g.nextDouble();
			}
		}
		for(int i=0;i<MaxThreads;i++){
			rh[i] = new RunThr(i,N,MaxThreads,array1,array2,Res);
			th[i] = new Thread(rh[i]);
			th[i].start();
		}
		for(int i=0;i<MaxThreads;i++){
			th[i].join();
		}
		long time =  System.currentTimeMillis() - start;
	
		System.out.println("\nEm"+time+".ms\n");
	}
}
