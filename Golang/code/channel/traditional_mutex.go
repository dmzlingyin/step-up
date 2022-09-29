package main

import (
	"fmt"
	"sync"
	"time"
)

type Center struct {
	sync.Mutex
	i int
}

var center Center

func increase() int {
	center.Lock()
	defer center.Unlock()
	center.i++
	return center.i
}

func main() {
	for i := 0; i < 10; i++ {
		go func() {
			v := increase()
			fmt.Printf("after increase, val= %d\n", v)
		}()
	}
	time.Sleep(time.Second)
}
