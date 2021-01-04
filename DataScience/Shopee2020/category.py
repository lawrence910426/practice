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
    
for o in orders:
    print(o)
    break
