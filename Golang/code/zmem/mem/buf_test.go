package mem_test

import (
	"fmt"
	"testing"
	"zmem/mem"
)

func TestBufPoolSetGet(t *testing.T) {
	pool := mem.MemPool()
	buffer, err := pool.Alloc(1)
	if err != nil {
		fmt.Println("pool alloc error\n", err)
		return
	}

	buffer.SetBytes([]byte("Aceld12345"))
	fmt.Printf("GetBytes = %+v, ToString = %s\n", buffer.GetBytes(), string(buffer.GetBytes()))
	buffer.Pop(4)
	fmt.Printf("GetBytes = %+v, ToString = %s\n", buffer.GetBytes(), string(buffer.GetBytes()))
}

func TestBufPoolCopy(t *testing.T) {
	pool := mem.MemPool()
	buffer, err := pool.Alloc(1)
	if err != nil {
		fmt.Println("pool alloc error\n", err)
		return
	}

	buffer.SetBytes([]byte("Aceld12345"))
	fmt.Printf("GetBytes = %+v, ToString = %s\n", buffer.GetBytes(), string(buffer.GetBytes()))

	obuffer, err := pool.Alloc(1)
	if err != nil {
		fmt.Println("pool alloc error\n", err)
		return
	}
	obuffer.Copy(buffer)
	fmt.Printf("other buffer GetBytes = %s\n", string(obuffer.GetBytes()))
}

func TestBufPoolAdjust(t *testing.T) {
	pool := mem.MemPool()

	buffer, err := pool.Alloc(4096)
	if err != nil {
		fmt.Println("pool alloc error\n", err)
		return
	}

	buffer.SetBytes([]byte("Aceld12345"))
	fmt.Printf("GetBytes = %+v, Head = %d, Length = %d\n", buffer.GetBytes(), buffer.Head(), buffer.Length())
	buffer.Pop(4)
	fmt.Printf("GetBytes = %+v, Head = %d, Length = %d\n", buffer.GetBytes(), buffer.Head(), buffer.Length())
	buffer.Adjust()
	fmt.Printf("GetBytes = %+v, Head = %d, Length = %d\n", buffer.GetBytes(), buffer.Head(), buffer.Length())
}
