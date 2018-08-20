package main

import (
    "fmt"
    "log"
    "net/http"
)

func main() {
    http.Handle("/", http.HandlerFunc(handler))
    err := http.ListenAndServe("localhost:8000", nil)
    if err != nil {
        log.Fatal(err)
    }
}

func handler(w http.ResponseWriter, r *http.Request) {
    fmt.Fprintf(w, "hello world!")
}