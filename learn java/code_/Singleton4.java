// lazy singleton # unthread safe # double check

/*
 * instance = new Singleton() :
 *  1 allocate memory
 *  2 create object
 *  3 assign memory to instance
 *
 * or
 *  1 allocate memory
 *  2 assign memory to instance
 *  3 create object
 *
 * the second step will let the second thread 
 * pass the first if and make program crash before
 * the first thread execute the final step 
 */

class Singleton {
    priatate static Singleton instance = null;
    
    private Singleton() {}
    
    public static Singleton getInstance() {
        if (instance == null) {
            synchronized (Singleton.class) {
                if (instance == null) {
                    instance = new Singleton();
                }
            }
        }
        return instance;
    }
}