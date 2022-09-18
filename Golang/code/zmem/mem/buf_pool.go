package mem

import (
	"errors"
	"fmt"
	"sync"
)

type Pool map[int]*Buf

type BufPool struct {
	Pool     Pool
	PoolLock sync.Mutex
	TotalMem uint64
}

var bufPoolInstance *BufPool
var once sync.Once

const (
	m4K   int = 4096
	m16K  int = 16384
	m64K  int = 65536
	m256K int = 262144
	m1M   int = 1048576
	m4M   int = 4194304
	m8M   int = 8388608
)

const (
	// 最限制总内存池大小为5GB
	EXTRA_MEM_LIMIT int = 5 * 1024 * 1024
)

func MemPool() *BufPool {
	once.Do(func() {
		bufPoolInstance = new(BufPool)
		bufPoolInstance.Pool = make(map[int]*Buf)
		bufPoolInstance.TotalMem = 0
		// bufPoolInstance.prev = nil
		bufPoolInstance.initPool()
	})
	return bufPoolInstance
}

func (bp *BufPool) initPool() {
	bp.makeBufList(m4K, 5000)
	bp.makeBufList(m16K, 1000)
	bp.makeBufList(m64K, 500)
	bp.makeBufList(m256K, 200)
	bp.makeBufList(m1M, 50)
	bp.makeBufList(m4M, 20)
	bp.makeBufList(m8M, 10)
}

func (bp *BufPool) Alloc(N int) (*Buf, error) {
	var index int
	if N <= m4K {
		index = m4K
	} else if N <= m16K {
		index = m16K
	} else if N <= m64K {
		index = m64K
	} else if N <= m256K {
		index = m256K
	} else if N <= m1M {
		index = m1M
	} else if N <= m4M {
		index = m4M
	} else if N <= m8M {
		index = m8M
	} else {
		return nil, errors.New("alloc size too large")
	}

	bp.PoolLock.Lock()
	defer bp.PoolLock.Unlock()

	if bp.Pool[index] == nil {
		if (bp.TotalMem + uint64(index/1024)) >= uint64(EXTRA_MEM_LIMIT) {
			return nil, errors.New("already use too many memory")
		}
		newBuf := NewBuf(index)
		bp.TotalMem += uint64(index / 1024)
		fmt.Printf("Alloc Mem Size: %d KB\n", newBuf.Capacity/1024)
		return newBuf, nil
	}

	targetBuf := bp.Pool[index]
	bp.Pool[index] = targetBuf.Next
	bp.TotalMem -= uint64(index / 1024)
	targetBuf.Next = nil
	fmt.Printf("Alloc Mem Size: %d KB\n", targetBuf.Capacity/1024)
	return targetBuf, nil
}

func (bp *BufPool) Revert(buf *Buf) error {
	index := buf.Capacity
	buf.Clear()

	bp.PoolLock.Lock()
	defer bp.PoolLock.Unlock()

	if _, ok := bp.Pool[index]; !ok {
		errStr := fmt.Sprintf("Index %d not in BufPool\n", index)
		return errors.New(errStr)
	}

	buf.Next = bp.Pool[index]
	bp.Pool[index] = buf
	bp.TotalMem += uint64(index / 1024)
	fmt.Printf("Revert Mem Size: %d KB\n", index/1024)
	return nil
}

func (bp *BufPool) makeBufList(cap int, num int) {
	bp.Pool[cap] = NewBuf(cap)
	prev := bp.Pool[cap]

	for i := 1; i < num; i++ {
		prev.Next = NewBuf(cap)
		prev = prev.Next
	}
	bp.TotalMem += (uint64(cap) / 1024) * uint64(num)
}
