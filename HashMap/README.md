# HashMap

## structure

```
table
 ------
|      |
 ------
|entry |
 ------        ------
|entry | ---> |entry |
 ------        ------
```

```java
static class Entry<K,V> implements Map.Entry<K,V> {
        final K key;
        V value;
        Entry<K,V> next;
        final int hash;

        /**
         * Creates new entry.
         */
        Entry(int h, K k, V v, Entry<K,V> n) {
            value = v;
            next = n;
            key = k;
            hash = h;
        }
        .......
    }
```

```
public HashMap(int initialCapacity, float loadFactor) {
        //初始容量不能<0
        if (initialCapacity < 0)
            throw new IllegalArgumentException("Illegal initial capacity: "
                    + initialCapacity);
        //初始容量不能 > 最大容量值，HashMap的最大容量值为2^30
        if (initialCapacity > MAXIMUM_CAPACITY)
            initialCapacity = MAXIMUM_CAPACITY;
        //负载因子不能 < 0
        if (loadFactor <= 0 || Float.isNaN(loadFactor))
            throw new IllegalArgumentException("Illegal load factor: "
                    + loadFactor);

        // 计算出大于 initialCapacity 的最小的 2 的 n 次方值。
        int capacity = 1;
        while (capacity < initialCapacity)
            capacity <<= 1;
        
        this.loadFactor = loadFactor;
        //设置HashMap的容量极限，当HashMap的容量达到该极限时就会进行扩容操作
        threshold = (int) (capacity * loadFactor);
        //初始化table数组
        table = new Entry[capacity];
        init();
    }
```

## put

```java
public V put(K key, V value) {
        //当key为null，调用putForNullKey方法，保存null与table第一个位置中，这是HashMap允许为null的原因
        if (key == null)
            return putForNullKey(value);
        //计算key的hash值
        int hash = hash(key.hashCode());                  ------(1)
        //计算key hash 值在 table 数组中的位置
        int i = indexFor(hash, table.length);             ------(2)
        //从i出开始迭代 e,找到 key 保存的位置
        for (Entry<K, V> e = table[i]; e != null; e = e.next) {
            Object k;
            //判断该条链上是否有hash值相同的(key相同)
            //若存在相同，则直接覆盖value，返回旧value
            if (e.hash == hash && ((k = e.key) == key || key.equals(k))) {
                V oldValue = e.value;    //旧值 = 新值
                e.value = value;
                e.recordAccess(this);
                return oldValue;     //返回旧值
            }
        }
        //修改次数增加1
        modCount++;
        //将key、value添加至i位置处
        addEntry(hash, key, value, i);
        return null;
    }
```