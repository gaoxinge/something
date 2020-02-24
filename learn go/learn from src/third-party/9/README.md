# sasha-s/go-deadlock

## what is it

[sasha-s/go-deadlock](https://github.com/sasha-s/go-deadlock) provides (RW)Mutex drop-in replacements for sync.(RW)Mutex to debug deadlock.

## how it work

It wraps sync.(RW)Mutex to trace the lock order.