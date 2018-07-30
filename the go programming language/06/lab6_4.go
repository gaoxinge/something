package main

import (
    "fmt"
    "bytes"
)

type IntSet struct {
    words []uint64
}

func popcount(x uint64) int {
    size := 0
    for ; x != 0; x >>= 1 {
        size += int(x % 2)
    }
    return size
}

func (s *IntSet) Has(x int) bool {
    word, bit := x/64, uint(x%64)
    return word < len(s.words) && s.words[word] & (1 << bit) != 0
}

func (s *IntSet) Add(x int) {
    word, bit := x/64, uint(x%64)
    for word >= len(s.words) {
        s.words = append(s.words, 0)
    }
    s.words[word] |= 1 << bit
}

func (s *IntSet) AddAll(xs...int) {
    for _, x := range xs {
        s.Add(x)
    }
}

func (s *IntSet) Remove(x int) {
    word, bit := x/64, uint(x%64)
    if word < len(s.words) {
        s.words[word] &= (^(1 << bit)) 
    }
}

func (s *IntSet) UnionWith(t *IntSet) {
    for i, tword := range t.words {
        if i < len(s.words) {
            s.words[i] |= tword
        } else {
            s.words = append(s.words, tword)
        }
    }
}

func (s *IntSet) IntersectWith(t *IntSet) {
    for i, tword := range t.words {
        if i >= len(s.words) {
            break;
        }
        s.words[i] &= tword
    }
}

func (s *IntSet) DifferenceWith(t *IntSet) {
    for i, tword := range(t.words) {
        if i >= len(s.words) {
            break;
        }
        s.words[i] &= ^tword
    }
}

func (s *IntSet) SymmetricDifference(t *IntSet) {
    for i, tword := range(t.words) {
        if i < len(s.words) {
            s.words[i] ^= tword
        } else {
            s.words = append(s.words, tword)
        }
    }
}

func (s *IntSet) Clear() {
    s.words = []uint64{}
    // s.words = make([]uint64, 0)
}

func (s *IntSet) Copy() *IntSet {
    t := new(IntSet)
    for _, word := range s.words {
        t.words = append(t.words, word)
    }
    return t
}

/*
func (s *IntSet) Copy() *IntSet {
    t := IntSet{}
    for _, word := range s.words {
        t.words = append(t.words, word)
    }
    return &t
}
*/

func (s *IntSet) Len() int {
    size := 0
    for _, word := range s.words {
        size += popcount(word)
    }
    return size
}

func (s *IntSet) String() string {
    var buf bytes.Buffer
    buf.WriteByte('{')
    for i, word := range s.words {
        if word == 0 {
            continue
        }
        for j := 0; j < 64; j++ {
            if word & (1 << uint(j)) != 0 {
                if buf.Len() > len("{") {
                    buf.WriteByte(' ')
                }
                fmt.Fprintf(&buf, "%d", 64*i+j)
            }
        }
    }
    buf.WriteByte('}')
    return buf.String()
}

func (s *IntSet) Elems() []int {
    result := []int{}
    for i, word := range s.words {
        if word == 0 {
            continue
        }
        for j := 0; j < 64; j++ {
            if word & (1 << uint(j)) != 0 {
                result = append(result, 64*i+j)
            }
        }
    }
    return result
}

func main() {
    // old test
    var x, y IntSet
    
    x.Add(1)
    x.Add(144)
    x.Add(9)
    fmt.Println(x.String())
    
    y.Add(9)
    y.Add(42)
    fmt.Println(y.String())
    
    
    x.UnionWith(&y)
    fmt.Println(x.String())
    fmt.Println(x.Has(9), x.Has(123))
    
    // new test
    var z IntSet
    z.Add(63)
    z.Add(64)
    z.Add(1234)
    fmt.Println(z.Len(), z.String())
    
    z.Remove(6)
    z.Remove(64)
    fmt.Println(z.Len(), z.String())
    
    a := z.Copy()
    z.Add(3)
    a.Add(4)
    fmt.Println(z.String(), a.String())
    
    z.AddAll(5, 6, 7)
    fmt.Println(z.Len(), z.String())
    
    a.IntersectWith(&z)
    fmt.Println(a.String())
    
    a.Add(12345)
    a.DifferenceWith(&z)
    fmt.Println(a.String())
    
    a.Add(5)
    a.Add(6)
    a.SymmetricDifference(&z)
    fmt.Println(a.String())
    
    fmt.Println(a.Elems())
    
    z.Clear()
    fmt.Println(z.Len(), z.String())
}