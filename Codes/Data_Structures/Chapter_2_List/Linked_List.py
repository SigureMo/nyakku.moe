class Node():
    def __init__(self, value):
        self.value = value
        self.pointer = None

class LinkedList():
    def __init__(self):
        self.head = None

    def append(self, value):
        if not self.head:
            self.head = Node(value)
            return
        curr = self.head
        while curr.pointer:
            curr = curr.pointer
        curr.pointer = Node(value)

    def find(self, value):
        curr = self.head
        while curr and curr.value != value:
            curr = curr.pointer
        return curr

    def remove(self, value):
        curr = self.head
        if curr.value == value:
            self.head = curr.pointer
            del curr
            return
        while curr:
            if curr.value == value:
                p.pointer = curr.pointer
                del curr
                break
            else:
                p = curr
                curr = curr.pointer

    def count(self):
        curr = self.head
        cnt = 1
        while curr:
            curr = curr.pointer
            cnt += 1
        return cnt



def print_linked_list(linkedList):
    curr = linkedList.head
    while curr:
        print(curr.value, end=' ')
        curr = curr.pointer
    print()

def reverse(my_list):
    """ 返回一个反转后的链表 """
    reversed_list = LinkedList()
    curr = my_list.head
    while curr:
        if not reversed_list.head:
            reversed_list.head = Node(curr.value)
        else:
            node = Node(curr.value)
            node.pointer = reversed_list.head
            reversed_list.head = node

        curr = curr.pointer
    return reversed_list

def remove_duplicates(my_list):
    new_list = LinkedList()
    curr = my_list.head
    while curr:
        if not new_list.find(curr.value):
            new_list.append(curr.value)
        curr = curr.pointer
    return new_list

foo = LinkedList()
foo.append(1)
foo.append(2)
foo.append(3)
foo.append(5)
print_linked_list(foo)
print(foo.count())
foo.remove(5)
print_linked_list(foo)
print_linked_list(reverse(foo))
