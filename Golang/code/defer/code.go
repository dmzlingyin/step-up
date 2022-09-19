package main

import "fmt"

func main() {
	defer foo(1, foo(3, 0))
	defer foo(2, foo(4, 0))
}

func foo(index, value int) int {
	fmt.Println(index)
	return index
}
