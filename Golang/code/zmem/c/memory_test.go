package c

import (
	"bytes"
	"encoding/binary"
	"fmt"
	"testing"
	"unsafe"
)

func IsLittleEndian() bool {
	var n int32 = 0x01020304

	u := unsafe.Pointer(&n)
	pb := (*byte)(u)

	b := *pb
	return b == 0x04
}

func IntToBytes(n uint32) []byte {
	x := int32(n)
	bytesBuffer := bytes.NewBuffer([]byte{})

	var order binary.ByteOrder
	if IsLittleEndian() {
		order = binary.LittleEndian
	} else {
		order = binary.BigEndian
	}
	binary.Write(bytesBuffer, order, x)
	return bytesBuffer.Bytes()
}

func TestMemory(t *testing.T) {
	data := Malloc(4)
	fmt.Printf("data %+v, %T\n", data, data)

	myData := (*uint32)(data)
	*myData = 5
	fmt.Printf("data %+v, %T\n", *myData, *myData)

	var a uint32 = 100
	Memcpy(data, IntToBytes(a), 4)
	fmt.Printf("data %+v, %T\n", *myData, *myData)

	Free(data)
}
