public class CalcThr{
	public static void main(String args[]) throws InterruptedException{
		if(args.length != 1 || !args[0].matches("\\d*[^0]\\d*")) {
			System.err.println("usage: java CalcThE MaxThreads.");
			System.exit(1);
		} 
		int MaxThreads = Integer.parseInt(args[0]);
		int N = 10000000;
		Thread[] th;
		RunThr[] rh;
		double[] array;
		double final_sum=0;
		rh = new RunThr[MaxThreads];
		th = new Thread[MaxThreads];
		array = new double[N];
		long  start = System.currentTimeMillis();
		for(int i=0;i<MaxThreads;i++){
			rh[i] = new RunThr(i,N,MaxThreads,array);
			th[i] = new Thread(rh[i]);
			th[i].start();
		}
		for(int i=0;i<MaxThreads;i++){
			th[i].join();
			final_sum+=rh[i].valor;
		}
		long time =  System.currentTimeMillis() - start;
		System.out.println("Resultado = "+final_sum/MaxThreads);
		System.out.println("\nEm"+time+".ms\n");
	}
}
