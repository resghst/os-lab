public class SynchronizedCounter implements Runnable{
	public int c = 0, k = 0;
	public synchronized void run(){
		k++;
		if ( k % 2 == 1 )
			for (int i = 0; i<25000000; i++) c++;
		else
			for (int i = 0; i<25000000; i++) c--;
	}
	public int getvalue(){ return c; }
	public static void main(String[] args){
		SynchronizedCounter Syc = new SynchronizedCounter();
		Thread thread0 = new Thread(Syc);
		thread0.start();
		Thread thread1 = new Thread(Syc);
		thread1.start();
		Thread thread2 = new Thread(Syc);
		thread2.start();
		Thread thread3 = new Thread(Syc);
		thread3.start();
		try{
			thread0.join();
			thread1.join();
			thread2.join();
			thread3.join();
		}catch(InterruptedException e){}
		System.out.printf("(%d)%n", Syc.getvalue() );
	} 
}