package main

import (
	"github.com/Ompluscator/dynamic-struct"
	"fmt"
)

func main() {
	instance := dynamicstruct.
		NewStruct().
		AddField("Integer", 0, "").
		AddField("Text", "", "").
		AddField("Float", 0.0, "").
		AddField("Boolean", false, "").
		AddField("Slice", []int{0, 1, 2}, "").
		Build().
		New()
	fmt.Println(instance)
}
