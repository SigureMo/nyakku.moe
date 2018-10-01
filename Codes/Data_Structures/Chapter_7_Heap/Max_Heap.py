import copy

class Heap():
    def __init__(self, s):
        self.heap = self.build_max_heap(s)

    def max_heapify(self, heap, heap_size, root):
        left = 2 * root + 1
        right = 2 * root + 2
        larger = root
        if left <= heap_size and heap[larger] < heap[left]:
            larger = left
        if right <= heap_size and heap[larger] < heap[right]:
            larger = right
        if larger != root:
            heap[larger], heap[root] = heap[root], heap[larger]
            self.max_heapify(heap, heap_size, larger)

    def build_max_heap(self, heap):
        heap_size = len(heap) - 1
        for i in range((heap_size - 1)//2, -1, -1):
            self.max_heapify(heap, heap_size,i)
        return heap

    def heap_sort(self):
        heap = copy.copy(self.heap)
        for i in range(len(heap)-1,-1,-1):
            heap[0], heap[i] = heap[i], heap[0]
            self.max_heapify(heap, i-1, 0)
            return heap

    def heap_insert(self, data):
        heap = self.heap
        heap.append(data)

        heap_size = len(heap) - 1
        father = (heap_size - 1) // 2
        son = heap_size
        while father >= 0:
            if heap[father] < heap[son]:
                heap[father], heap[son] = heap[son], heap[father]
                son = father
                father = (father - 1) // 2
            else:
                break
        return heap

a = [30, 50, 57, 77, 62, 78, 94, 80, 84]
heap = Heap(a)
print(heap.heap)
heap.heap_insert(100)
heap.heap_insert(1)
print(heap.heap)
