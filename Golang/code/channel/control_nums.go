package main

import (
	"fmt"
	"sync"
)

var wg sync.WaitGroup

func worker(ch chan bool, i int) {
	fmt.Println("worker id: ", i)
	<-ch
	wg.Done()
}

func main() {
	ch := make(chan bool, 3)
	for i := 0; i < 100; i++ {
		wg.Add(1)
		ch <- true
		go worker(ch, i)
	}
	wg.Wait()
}
