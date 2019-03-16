package main

import (
    "fmt"
    "log"
    "net/http"
)

type localString string

func (this localString) ServeHTTP(w http.ResponseWriter, r *http.Request) {
    fmt.Fprintf(w, string(this))
}

func main() {
    ls := localString("hello world")
    err := http.ListenAndServe("localhost:8000", ls)
    if err != nil {
        log.Fatal(err)
    }
}

