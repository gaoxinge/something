// lazy singleton # thread safe # class load

class Singleton {
    private static class SingletonWrapper {
        static Singleton instance = new Singleton();
    }
    
    private Singleton() {}
    
    public static Singleton getInstance() {
        return SingletonWrapper.instance;
    }
}