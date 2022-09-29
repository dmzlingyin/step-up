package main

import (
	"fmt"
	"sync"
	"time"
)

func worker2(i int) {
	fmt.Printf("worker %d is working...\n", i)
	time.Sleep(time.Second)
	fmt.Printf("worker %d works done\n", i)
}

func worker3(i int) {
	fmt.Println("I am worker3")
	time.Sleep(time.Second)
	fmt.Println("worker3 runnnnnnn...")
}

func spawnGroup(f func(i int), num int, groupSignal <-chan bool) <-chan bool {
	ch := make(chan bool)
	var wg sync.WaitGroup

	for i := 0; i < num; i++ {
		wg.Add(1)
		go func(i int) {
			<-groupSignal
			fmt.Printf("worker %d start to work\n", i)
			f(i)
			wg.Done()
		}(i + 1)
	}

	go func() {
		wg.Wait()
		ch <- true
	}()
	return ch
}

func main() {
	// just like a sig-gun
	groupSignal := make(chan bool)

	ch1 := spawnGroup(worker2, 5, groupSignal)
	ch2 := spawnGroup(worker3, 10, groupSignal)

	fmt.Println("are you ready?")
	time.Sleep(time.Second * 3)
	close(groupSignal)
	<-ch1
	<-ch2
}
