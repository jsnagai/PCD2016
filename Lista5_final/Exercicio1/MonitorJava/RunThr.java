import java.util.Random;
import java.util.concurrent.ThreadLocalRandom;

class RunThr implements Runnable{
	private int N;
	private int MaxThreads;
	private int id;
	private double[] x;
	private double[] y;
	private double SUMx_local;
	private double SUMy_local;
	private double SUMxx_local;
	private double SUMxy_local;

	public RunThr(int aid,int aN, int aMaxThreads, double[] aarray,double[] aaarray){
		id = aid;
		N = aN;
		MaxThreads = aMaxThreads;
		x=aarray;
		y=aaarray;
	}		
	public synchronized void UpdateGlobals(){
		CalcThr.SUMx = this.SUMx_local;
		CalcThr.SUMy = this.SUMy_local;
		CalcThr.SUMxx = this.SUMxx_local;
		CalcThr.SUMxy = this.SUMxy_local;

	}

	public void run(){
		for(int i = id;i<N;i+=MaxThreads){
			x[i]=ThreadLocalRandom.current().nextDouble();
			y[i]=ThreadLocalRandom.current().nextDouble();
		}
		for(int i =id;i<N;i+=MaxThreads){
			SUMx_local += x[i];
			SUMy_local += y[i];
			SUMxy_local += x[i]*y[i];
			SUMxx_local += x[i]*x[i];
		}
		UpdateGlobals();

	}

}
