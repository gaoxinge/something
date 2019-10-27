package main

import "fmt"

type Point struct {
	X float64
	Y float64
}

type Point1 struct {
	Point
	Z float64
}

type Point2 struct {
	Z float64
	Point
}

func main() {
	p1 := Point1{}
	p1.X = 1
	p1.Y = 2
	p1.Z = 3
	fmt.Println(p1)

	p2 := Point2{}
	p2.X = 1
	p2.Y = 2
	p2.Z = 3
	fmt.Println(p2)
}
