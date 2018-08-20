package main

import (
    "fmt"
    "log"
    "net/http"
)

func main() {
    mux := http.NewServeMux()
    mux.Handle("/", http.HandlerFunc(handler))
    err := http.ListenAndServe("localhost:8000", mux)
    if err != nil {
        log.Fatal(err)
    }
}

func handler(w http.ResponseWriter, r *http.Request) {
    fmt.Fprintf(w, "hello world!")
}