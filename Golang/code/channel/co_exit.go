package main

import (
	"fmt"
	"sync"
	"time"
)

func worker4(i int, quit <-chan bool) {
	defer fmt.Printf("worker %d works done\n", i)
	fmt.Printf("worker %d is working...\n", i)
	for {
		select {
		case <-quit:
			return
		default:
			time.Sleep(time.Second)
		}
	}
}

func spawnGroup1(f func(int, <-chan bool), num int, groupSignal <-chan bool) <-chan bool {
	c := make(chan bool)
	var wg sync.WaitGroup

	for i := 0; i < num; i++ {
		wg.Add(1)
		go func(i int) {
			fmt.Printf("worker %d: start to work...\n", i)
			f(i, groupSignal)
			wg.Done()
		}(i + 1)
	}

	go func() {
		wg.Wait()
		c <- true
	}()
	return c
}

func main() {
	fmt.Println("start a group of workers...")
	groupSignal := make(chan bool)
	c := spawnGroup1(worker4, 5, groupSignal)

	// 3s后停止工作
	time.Sleep(3 * time.Second)
	fmt.Println("stop work!!!!!")
	close(groupSignal)
	<-c
}
