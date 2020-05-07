class Solution0(object):
    S, M, L = 0, 1, 2
    LEFT, RIGHT = 0, 1

    brackets = {
        '(': (LEFT, S),
        ')': (RIGHT, S),
        '[': (LEFT, M),
        ']': (RIGHT, M),
        '{': (LEFT, L),
        '}': (RIGHT, L)
    }
    def isValid(self, s: str) -> bool:
        stack = []
        for c in s:
            type, id = Solution0.brackets[c]
            if type == Solution0.LEFT:
                stack.append(c)
            else:
                if not stack:
                    return False
                top = stack[-1]
                top_type, top_id = Solution0.brackets[top]
                if top_type == Solution0.LEFT and top_id == id:
                    stack.pop()
                else:
                    return False
        if stack:
            return False
        return True

class Solution1(object):
    brackets = {
        '(': ')',
        '[': ']',
        '{': '}',
        '?': '?'
    }
    def isValid(self, s: str) -> bool:
        stack = ['?']
        for c in s:
            if c in Solution1.brackets:
                stack.append(c)
            else:
                if Solution1.brackets[stack.pop()] != c:
                    return False
        return len(stack) == 1

def test_case(id: int) -> str:
    return [
        '()', '()[]{}', '(]', '([)]', '{[]}', ']'
    ][id]

if __name__ == '__main__':
    s = test_case(4)
    print(s)
    print(Solution1().isValid(s))
