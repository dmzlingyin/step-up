package main

import "fmt"

type Slice[T int | float32 | float64 | string] []T
type MyMap[KEY int | string, VALUE float32 | float64] map[KEY]VALUE

type MStruct[T int | float32] struct {
	name string
	data []T
}

func main() {
	var a Slice[int] = []int{1, 2, 3}
	fmt.Printf("Type Name: %T\n", a)

	var b Slice[float32] = []float32{1, 2, 3}
	fmt.Printf("Type Name: %T\n", b)

	var amap MyMap[string, float64] = map[string]float64{
		"jack": 12.4,
		"bob":  11,
	}
	fmt.Println(amap)

	s := MStruct[int]{
		name: "test",
		data: []int{1},
	}
	fmt.Println(s)
}
