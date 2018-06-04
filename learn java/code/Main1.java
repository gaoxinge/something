public class Main1 {  
    public static void main(String[] args) {
        Thread1 thread1 = new Thread1("A");
        Thread1 thread2 = new Thread1("B");
        thread1.start();
        thread2.start();
    }
}

class Thread1 extends Thread {  
    private String name; 
    
    public Thread1(String name) {  
       this.name = name;  
    }
    
    @Override
    public void run() {  
        for (int i = 0; i < 5; i++) {
            System.out.println(name + " run " + (i+1) + " times");  
            try {
                sleep(1000);   // same as Thread.sleep
            } catch (InterruptedException e) {  
                e.printStackTrace();  
            }  
        }
    }  
}  