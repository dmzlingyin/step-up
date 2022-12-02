package main

import "fmt"

func Add[T int | float32 | float64](a, b T) T {
	return a + b
}

func main() {
	fmt.Println(Add[int](1, 2))
}
