package main

import (
    "bufio"
    "fmt"
    "os"
)

func main() {
    counts := make(map[string]int)
    correspond_files := make(map[string][]string)
    files := os.Args[1:]
    if len(files) == 0 {
        countLines(os.Stdin, "stdin", counts, correspond_files)
    } else {
        for _, arg := range files {
            f, err := os.Open(arg)
            if err != nil {
                fmt.Fprintf(os.Stderr, "dup2: %v\n", err)
                continue
            }
            countLines(f, arg, counts, correspond_files)
            f.Close()
        }
    }
    for line, n := range counts {
        if n > 1 {
            fmt.Printf("%s:  %d  %v\n", line, n, correspond_files[line])
        }
    }
}

func countLines(f *os.File, 
                arg string, 
                counts map[string]int, 
                correspond_files map[string][]string) {
    var line string
    input := bufio.NewScanner(f)
    for input.Scan() {
        line = input.Text()
        counts[line]++
        if pos(correspond_files[line], arg) == -1 {
            correspond_files[line] = append(correspond_files[line], arg)
        }
    }
}

func pos(args []string, arg string) int {
    for k, v := range args {
        if v == arg {
            return k
        }
    }
    return -1
}
