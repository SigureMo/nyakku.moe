'''
# 1003 我要通过！ （20 分）
src：https://pintia.cn/problem-sets/994805260223102976/problems/994805323154440192

“答案正确”是自动判题系统给出的最令人欢喜的回复。本题属于 PAT 的“答案正确”
大派送 —— 只要读入的字符串满足下列条件，系统就输出“答案正确”，否则输出“
答案错误”。

得到“答案正确”的条件是：
1. 字符串中必须仅有 `P`、 `A`、 `T`这三种字符，不可以包含其它字符
2. 任意形如 `xPATx` 的字符串都可以获得“答案正确”，其中 `x` 或者是空字符串，或者
是仅由字母 `A` 组成的字符串；
3. 如果 `aPbTc` 是正确的，那么 `aPbATca` 也是正确的，其中 `a`、 `b`、 `c` 均或者是空字符
串，或者是仅由字母 A 组成的字符串。
现在就请你为 PAT 写一个自动裁判程序，判定哪些字符串是可以获得“答案正确”的。


# 格式：
IN：
每个测试输入包含 1 个测试用例。第 1 行给出一个正整数 n (<10)，是需要检测的字符串个
数。接下来每个字符串占一行，字符串长度不超过 100，且不包含空格。
OUT：
每个字符串的检测结果占一行，如果该字符串可以获得“答案正确”，则输出 `YES`，
否则输出 `NO`。

# 样例：
IN：
8
PAT
PAAT
AAPATAA
AAPAATAAAA
xPATx
PT
Whatever
APAAATAA
OUT:
YES
YES
YES
YES
NO
NO
NO
NO
'''
import re

def check(s):
    if re.match(r'(?P<end>A*)PAT(?P=end)',s):
        return True
    elif ('P' in s) and ('A' in s) and ('T' in s):
        if s.index('P'):
            return check(s[:s.index('T')-1] + s[s.index('T'):-s.index('P')])
        else:
            return check(s[:s.index('T')-1] + s[s.index('T'):])
    else:
        return False

n = eval(input())
for i in range(n):
    l = input()
    if check(l):
        print('YES')
    else:
        print('NO')
    
