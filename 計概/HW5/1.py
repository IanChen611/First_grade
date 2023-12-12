from sys import stdin

def input(): 
    return stdin.readline().strip()

# n 島嶼數量
# m 可見造傳送門的組合數
# t 魔法設備等級
# x 等級一魔法設備價格
n, m, t, x = map(int, input().split())


class ListNode:
    def __init__(self, data): 
        # 此傳送門的基礎成本
        self.data = data
        #傳送門接兩邊的島嶼編號
        self.beside_one = None
        self.beside_two = None
        return

#建造傳送門資訊表
l = []


# a b島嶼傳送門基礎成本為c
a, b, c = map(int, input().split())
for i in range(n):
    tem = ListNode(c)
    tem.beside_one = a
    tem.beside_two = b
    l.append(tem)

print(l)
