import java.util.Random;

class RunThr implements Runnable{
	private int N;
	private int MaxThreads;
	private int id;
	public RunThr(int aid,int aN, int aMaxThreads, double[][] aarray,double[][] aaarray,double[][] Res){
		id = aid;
		N = aN;
		MaxThreads = aMaxThreads;
	}		

	public void run(){
		for(int k=id;k<N;k+=MaxThreads){
			for(int j=0;j<N;j++){
				CalcThr.Res[k][j]=CalcThr.array1[k][j]+CalcThr.array2[k][j];
			}
		}
	

	}

}
