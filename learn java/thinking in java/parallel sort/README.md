# parallel sort

## sort api

- `Arrays.sort` use merge sort and quick sort
- `Arrays.parallelSort` use parallel merge sort

## `Arrays.sort` vs `Arrays.parallelSort`

Run the command below

```
$ javac Main.java
$ java Main
[sort] size = 10, time = 0
[parallel sort] size = 10, time = 0
[sort] size = 20, time = 0
[parallel sort] size = 20, time = 0
[sort] size = 40, time = 1
[parallel sort] size = 40, time = 0
[sort] size = 80, time = 0
[parallel sort] size = 80, time = 0
[sort] size = 160, time = 0
[parallel sort] size = 160, time = 1
[sort] size = 320, time = 0
[parallel sort] size = 320, time = 0
[sort] size = 640, time = 1
[parallel sort] size = 640, time = 1
[sort] size = 1280, time = 1
[parallel sort] size = 1280, time = 1
[sort] size = 2560, time = 1
[parallel sort] size = 2560, time = 1
[sort] size = 5120, time = 2
[parallel sort] size = 5120, time = 1
[sort] size = 10240, time = 2
[parallel sort] size = 10240, time = 11
[sort] size = 20480, time = 5
[parallel sort] size = 20480, time = 6
[sort] size = 40960, time = 12
[parallel sort] size = 40960, time = 16
[sort] size = 81920, time = 15
[parallel sort] size = 81920, time = 10
[sort] size = 163840, time = 15
[parallel sort] size = 163840, time = 8
[sort] size = 327680, time = 32
[parallel sort] size = 327680, time = 16
[sort] size = 655360, time = 67
[parallel sort] size = 655360, time = 31
[sort] size = 1310720, time = 142
[parallel sort] size = 1310720, time = 67
[sort] size = 2621440, time = 301
[parallel sort] size = 2621440, time = 138
[sort] size = 5242880, time = 627
[parallel sort] size = 5242880, time = 317
```

We can see that 

- when the size is smaller than 50000, the performance of `Arrays.sort` is better than `Arrays.parallelSort`
- when the size is larger than 50000, the performance of `Arrays.parallelSort` is better than `Arrays.sort`