from typing import Tuple

# Definition for singly-linked list.
class ListNode(object):
    def __init__(self, x):
        self.val = x
        self.next = None

class Solution(object):
    def addTwoNumbers(self, l1: ListNode, l2: ListNode) -> ListNode:
        head = ListNode(0)
        curr = head
        carry = 0
        while l1 or l2 or carry:
            next_val = 0
            if l1 is not None:
                next_val += l1.val
                l1 = l1.next
            if l2 is not None:
                next_val += l2.val
                l2 = l2.next
            next_val += carry
            carry, next_val = next_val // 10, next_val % 10
            curr.next = ListNode(next_val)
            curr = curr.next
        return head.next

def init_list(*vals: int) -> ListNode:
    l_head = ListNode(0)
    l = l_head
    for val in vals:
        l.next = ListNode(val)
        l = l.next
    return l_head.next

def print_list(l: ListNode) -> None:
    l_head = ListNode(0)
    l_head.next = l
    while l_head := l_head.next:
        print(l_head.val, end=" ")
    print()

def test_case(id: int) -> Tuple[ListNode, ListNode]:
    return [
        (init_list(2, 4, 3), init_list(5, 6, 4)),
        (init_list(5), init_list(5))
    ][id]

if __name__ == '__main__':
    l1, l2 = test_case(0)

    print_list(l1)
    print_list(l2)

    l = Solution().addTwoNumbers(l1, l2)
    print_list(l)
