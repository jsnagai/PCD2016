
import java.util.Random;
import java.util.concurrent.Semaphore;
class RunThr implements Runnable{
	private int N;
	private int MaxThreads;
	private int id;
	private double[] array;
	public double valor;
	private Semaphore sem;

	public RunThr(int aid,int aN, int aMaxThreads, Semaphore sem){
		id = aid;
		N = aN;
		MaxThreads = aMaxThreads;
		this.sem = sem;
	}		

	public void run(){
		double pe_local=0;
		for(int k=id;k<N;k+=MaxThreads){
			pe_local += CalcThr.A[k]*CalcThr.B[k];
		}
		System.out.println(id+"\t"+pe_local+"\n");
		try{
			sem.acquire();
			CalcThr.pe+=pe_local;
			sem.release();


		}catch(InterruptedException e){
			System.out.println("Erro");
		}




	}

}
