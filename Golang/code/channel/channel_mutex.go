package main

import (
	"fmt"
	"time"
)

type Counter struct {
	c chan int
	i int
}

var cter Counter

func init() {
	cter = Counter{
		c: make(chan int),
	}

	// 实际加和的代码
	go func() {
		for {
			cter.i++
			cter.c <- cter.i
		}
	}()
}

// 从channel中获取已经加和的值
func inc() int {
	return <-cter.c
}

func main() {
	for i := 0; i < 10; i++ {
		go func(i int) {
			v := inc()
			fmt.Printf("goroutine %d: incd val= %d\n", i, v)
		}(i)
	}
	time.Sleep(time.Second * 2)
}
