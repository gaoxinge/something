package main

import (
    "encoding/json"
    "fmt"
)

type A1 struct {
    Value1 string
    Value2 int
}

type A2 struct {
    Value3 string
    Value4 int
}

type B struct {
    Value5 A2
    Value6 float64
}

func main() {
    // slice
    slice := make([]interface{}, 0)
    err := json.Unmarshal([]byte(`[{"Value1": "1", "Value2": 2}, {"Value3": "3", "Value4": 4}]`), &slice)
    if err != nil {
        fmt.Println(err)
        return
    }
    fmt.Println(slice)
    
    slice0, ok := slice[0].(map[string]interface{})
    if !ok {
        fmt.Println("type assertion error")
        return
    }
    fmt.Println(slice0)
    
    // map
    mapping := make(map[string]json.RawMessage)
    err = json.Unmarshal([]byte(`{"a": {"Value1": "1", "Value2": 2}, "b": {"Value3": "3", "Value4": 4}}`), &mapping)
    if err != nil {
        fmt.Println(err)
        return
    }
    fmt.Println(mapping)
    
    mapping0 := A1{}
    err = json.Unmarshal(mapping["a"], &mapping0)
    if err != nil {
        fmt.Println(err)
        return
    }
    fmt.Println(mapping0)
    
    // struct
    b := B{}
    bb := `{
        "Value5": {
            "Value3": "3",
            "Value4": 4            
        },
        "Value6": 6.00
    }`
    err = json.Unmarshal([]byte(bb), &b)
    if err != nil {
        fmt.Println(err)
        return
    }
    fmt.Println(b)
}