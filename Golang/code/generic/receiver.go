package main

import "fmt"

type MySlice[T int | float32] []T

func (s MySlice[T]) sum() T {
	var sum T
	for _, v := range s {
		sum += v
	}
	return sum
}

func main() {
	var a MySlice[int] = []int{1, 2, 3, 4}
	var b MySlice[float32] = []float32{1.2, 3.4, 4.3, 4.3}
	fmt.Println(a.sum(), b.sum())
}
