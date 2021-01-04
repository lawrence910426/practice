from itertools import permutations  
import numpy as np

order_data = open("order_sku.csv").read().splitlines()[1:]
sku_data = open("sku_dimenssion.csv").read().splitlines()[1:]
box_data = open("box_dimension.csv").read().splitlines()[1:]

sku = {}
for s in sku_data:
    sku_id,length,width,height = s.split(",")
    sku[sku_id] = (float(length),float(width),float(height))

boxes = {}
for b in box_data:
    _id,box_number,length,width,height = b.split(",")
    boxes[box_number] = (float(length),float(width),float(height))

orders = {}

for o in order_data:
    order_number, sku_id, quantity = o.split(",")
    if order_number not in orders:
        orders[order_number] = []
    
    for _ in range(int(quantity)):
        orders[order_number].append(sku[sku_id])

answer = []
for o in orders:
    def Big():
        ans = "UNFITTED"
        size_sum = 0
        item = orders[o]
        for packet in item:
            size_sum += packet[0] * packet[1] * packet[2]
        for b in boxes:
            box = boxes[b]
            if box[0] * box[1] * box[2] >= size_sum:
                ans = b
                break
        answer.append([o, ans])

    def Able(box, space, x, p):
        for i in range(0, box[0]):
            for j in range(0, box[1]):
                for k in range(0, box[2]):
                    # print(space[i:i + p[x][0]][j:j + p[x][1]][k:k + p[x][2]])
                    if np.sum(space[i:i + p[x][0]][j:j + p[x][1]][k:k + p[x][2]]) == 0:
                        for ii in range(i, i + p[x][0]):
                            for jj in range(j, j + p[x][1]):
                                for kk in range(k, k + p[x][2]):
                                    try:
                                        space[ii][jj][kk] = 1
                                    except:
                                        pass
                        return True
        return False
    def Small():
        def rec(p, dep):
            if dep == len(p):
                ans = "UNFITTED"
                for b in boxes:
                    box = boxes[b]
                    box = [int(box[i]) for i in range(3)]
                    space = np.zeros(box).tolist()   
                    fittable = False
                    for x in range(len(p)):
                        if not Able(box, space, x, p):
                            break
                        if x == len(p) - 1:
                            fittable = True
                    if fittable:
                        ans = b
                        break
                return ans
            else:
                ans = "UNFITTED"
                rec(p, dep + 1)
                for i in range(3):
                    for j in range(i + 1, 3):
                        p[dep][i], p[dep][j] = p[dep][j], p[dep][i]
                        ans = min(ans, rec(p, dep + 1))
                        # p[dep][i], p[dep][j] = p[dep][j], p[dep][i]
                return ans
        for p in permutations(orders[o]):
            temp = [[int(p[i][j] + 0.99) for j in range(3)] for i in range(len(p))]
            ans = "UNFITTED"
            ans = min(ans, rec(temp, 0))
        return ans
    
    if len(orders[o]) == 1:
        continue
    if len(orders[o]) >= 3:
        continue
    q = [o, Small()]
    answer.append(q)
    # print(q)

print("order_number,box_number")
for item in answer:
    print(item[0] + "," + item[1])
