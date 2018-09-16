'''
# 1002 写出这个数 （20 分）
src：https://pintia.cn/problem-sets/994805260223102976/problems/994805324509200384

读入一个正整数 n，计算其各位数字之和，用汉语拼音写出和的每一位数字。

# 格式：
IN：
每个测试输入包含 1 个测试用例，即给出自然数 n 的值。这里保证 n 小于 10^100
OUT：
在一行内输出 n 的各位数字之和的每一位，拼音数字间有 1 空格，但一行中最后一个拼音数字后没有空格。

# 样例：
IN：
1234567890987654321123456789
OUT
yi san wu
'''
d = {
    '1': 'yi',
    '2': 'er',
    '3': 'san',
    '4': 'si',
    '5': 'wu',
    '6': 'liu',
    '7': 'qi',
    '8': 'ba',
    '9': 'jiu',
    '0': 'ling',
    }

def spell(num):
    l = []
    for i in str(num):
        l.append(d[i])
    return ' '.join(l)

n = input()
sum = 0
for i in n:
    sum += int(i)
    #print(i)
print(spell(sum))
