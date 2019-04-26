public class Main2 {  
    public static void main(String[] args) {
        Thread thread1 = new Thread(new Runnable1("A"));   // must use thread to run concurrently 
        Thread thread2 = new Thread(new Runnable1("B"));
        thread1.start();
        thread2.start();
    }
}

class Runnable1 implements Runnable {  
    private String name;

    public Runnable1(String name) {  
        this.name = name;  
    }

    @Override  
    public void run() {  
        for (int i = 0; i < 5; i++) {  
            System.out.println(name + " run " + (i+1) + " times");  
            try {  
                Thread.sleep(1000);  
            } catch (InterruptedException e) {  
                e.printStackTrace();  
            }  
        }    
    }
}    