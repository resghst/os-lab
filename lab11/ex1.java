import java.util.concurrent.locks.*;

public class ex1 implements Runnable{
	private Lock lock = new ReentrantLock();
	private Condition threadCond = lock.newCondition();

	private int product = 0;
	private int k = 1;

	public  void run(){
		k++;
		if ( k % 2 == 1 ) 
			for (int i = 0; i<50; i++) 
				setProduct();
		else
			for (int i = 0; i<50; i++) 
				getProduct();
	}

	public void setProduct(){
		lock.lock();
		try{
			while(this.product >= 10){
				try{ threadCond.await(); }
				catch(InterruptedException e){ e.printStackTrace(); }
			}
			this.product++;
			System.out.printf("To produce (%d)%n", this.product);
			threadCond.signal();
		}
		finally{
			lock.unlock();
		} 
    	for(int i=0;i <100000;i++){}
	}

	public void getProduct(){
		lock.lock();
		try{
			while(this.product == 0){
				try{ threadCond.await(); }
				catch(InterruptedException e){ e.printStackTrace(); }
			}
			this.product--;
			System.out.printf("To consume (%d)%n", this.product);
			threadCond.signal();
		}
		finally{
			lock.unlock();
		} 
    	for(int i=0;i <100000;i++){}
	}


	public static void main(String[] args){
		ex1 Syc = new ex1();
		Thread thread0 = new Thread(Syc);
		thread0.start();
		Thread thread1 = new Thread(Syc);
		thread1.start();
		try{
			thread0.join();
			thread1.join();
		}catch(InterruptedException e){}
		//System.out.printf("(%d)%n", Syc.getvalue() );
	} 
}