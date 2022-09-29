package mem

import (
	"C"
	"fmt"
	"unsafe"
	"zmem/c"
)

type Buf struct {
	Next     *Buf
	Capacity int
	length   int
	head     int
	data     unsafe.Pointer
}

func NewBuf(size int) *Buf {
	return &Buf{
		Next:     nil,
		Capacity: size,
		length:   0,
		head:     0,
		data:     c.Malloc(size),
	}
}

// Golang的指针不能进行计算操作, 通过转换为uintptr无符号整形进行计算, 再转为指针类型
func (b *Buf) SetBytes(src []byte) {
	c.Memcpy(unsafe.Pointer(uintptr(b.data)+uintptr(b.head)), src, len(src))
	b.length += len(src)
}

func (b *Buf) GetBytes() []byte {
	data := C.GoBytes(unsafe.Pointer(uintptr(b.data)+uintptr(b.head)), C.int(b.length))
	return data
}

func (b *Buf) Copy(other *Buf) {
	c.Memcpy(b.data, other.GetBytes(), other.length)
	b.head = 0
	b.length = other.length
}

func (b *Buf) Pop(len int) {
	if b.data == nil {
		fmt.Println("pop data is nil")
		return
	}
	if len > b.length {
		fmt.Println("pop len > length")
		return
	}
	b.length -= len
	b.head += len
}

// 什么时候调用该方法?
func (b *Buf) Adjust() {
	if b.head != 0 {
		if b.length != 0 {
			c.Memmove(b.data, unsafe.Pointer(uintptr(b.data)+uintptr(b.head)), b.length)
		}
		b.head = 0
	}
}

// 实际的内存回收, 由内存池进行管理
func (b *Buf) Clear() {
	b.length = 0
	b.head = 0
}

func (b *Buf) Head() int {
	return b.head
}

func (b *Buf) Length() int {
	return b.length
}
