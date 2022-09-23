package main

import (
	"fmt"
	"time"
)

func main() {
	ch := make(chan bool)
	go a(ch)
	go b(ch)
	time.Sleep(time.Second * 2)
}

func a(ch chan bool) {
	for i := 1; i <= 100; i++ {
		// first
		ch <- true
		if i%2 == 1 {
			fmt.Println("goroutine 1: ", i)
		}
	}
}

func b(ch chan bool) {
	for i := 1; i <= 100; i++ {
		// second
		<-ch
		if i%2 == 0 {
			fmt.Println("goroutine 2: ", i)
		}
	}
}
