import java.util.Random;

public class CalcThr{

public static double[] array1;
public static double[] array2;
public static double SUMx = 0F;
public static double SUMy = 0F;
public static double SUMxy = 0F;
public static double SUMxx = 0F;

	public static void main(String args[]) throws InterruptedException{
		if(args.length != 1 || !args[0].matches("\\d*[^0]\\d*")) {
			System.err.println("usage: java CalcThE MaxThreads.");
			System.exit(1);
		} 
		int MaxThreads = Integer.parseInt(args[0]);
		int N = 1000000;
		Thread[] th;
		RunThr[] rh;
		Random g = new Random();

		int final_sum=0;
		rh = new RunThr[MaxThreads];
		th = new Thread[MaxThreads];
		array1 = new double[N];
		array2 = new double[N];
		
		long  start = System.currentTimeMillis();

		for(int i=0;i<MaxThreads;i++){
			rh[i] = new RunThr(i,N,MaxThreads,array1,array2);
			th[i] = new Thread(rh[i]);
			th[i].start();
		}
		for(int i=0;i<MaxThreads;i++){
			th[i].join();
		}
		long time =  System.currentTimeMillis() - start;
		double slope = (SUMx*SUMy - N*SUMxy)/(SUMx*SUMx - N*SUMxx);
		double y_intercept = (SUMy-slope*SUMx)/N;
		System.out.println("\nTime: "+time+".ms\n");
		System.out.printf("JavaThreads :: Minimos Quadrados: y = %6.3fx + %6.3f\n",slope,y_intercept );  
	}
}
