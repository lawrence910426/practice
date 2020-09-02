from function import LSTM_Model
from os import listdir
from os.path import isfile, join
import csv

words_path = "/mnt/d/Github/practice/Security/AIS3-2020/Project/analysis/words"
files = [f for f in listdir(words_path) if isfile(join(words_path, f))]

model = LSTM_Model()
ans = {}
field = ["red", "blue", "green"]
for i in field:
    ans[i] = {}
    for j in field:
        ans[i][j] = 0

for file_name in files:
    with open(words_path + "/" + file_name, newline='') as csvfile:
        rows = csv.reader(csvfile, delimiter=',')
        for row in rows:
            if len(row) >= 3 and row[2] in field:
                try:
                    temp = model.query(row[0], row[1])
                    ans[temp][row[2]] += 1
                    print(temp)
                    print(row[2])
                except:
                    pass
            print(ans)

print(ans)
