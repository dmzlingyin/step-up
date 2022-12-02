package main

type Queue[T interface{}] struct {
	elements []T
}

func (q *Queue[T]) Put(value T) {
	q.elements = append(q.elements, value)
}

func (q *Queue[T]) Pop() (T, bool) {
	var value T
	if len(q.elements) == 0 {
		return value, true
	}
	value = q.elements[0]
	q.elements = q.elements[1:]
	return value, len(q.elements) == 0
}

func (q *Queue[T]) Size() int {
	return len(q.elements)
}

func main() {
	var qi Queue[int]
	qi.Put(1)
	qi.Put(2)
	qi.Put(3)
	qi.Pop()
	qi.Pop()
	qi.Pop()

	var qs Queue[string]
	qs.Put("1")
	qs.Put("2")
	qs.Put("3")
	qs.Pop()
	qs.Pop()
	qs.Pop()
}
