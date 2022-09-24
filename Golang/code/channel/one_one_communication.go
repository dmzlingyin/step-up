package main

import (
	"fmt"
	"time"
)

func worker1() {
	fmt.Println("working...")
	time.Sleep(time.Second)
}

func spawn() <-chan bool {
	ch := make(chan bool)
	go func() {
		fmt.Println("worker start to work...")
		worker1()
		ch <- true
	}()
	return ch
}

func main() {
	fmt.Println("start a worker...")
	c := spawn()
	<-c
	fmt.Println("worker done")
}
