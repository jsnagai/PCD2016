import java.util.Random;
class RunThr implements Runnable{
	private int N;
	private int MaxThreads;
	private int id;
	private double[] array;
	public double valor;
	
	public RunThr(int aid,int aN, int aMaxThreads, double[] aarray){
		id = aid;
		N = aN;
		MaxThreads = aMaxThreads;
		array = aarray;
	}		

	public void run(){
		Random g = new Random();
		for(int k=id;k<N;k+=MaxThreads){
			array[k]=g.nextDouble();
		}
		for(int k=id;k<N;k+=MaxThreads){
			valor+=array[k];
		}
	

	}

}
