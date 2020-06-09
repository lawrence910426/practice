import sys
from subprocess import Popen, PIPE
import os

cipher = open('TsaiBroSaid', 'rb').read()[81:]
table = {}

for i in range(1, 128):
    item = chr(i)
    process = Popen(["./TsaiBro", item], stdout=PIPE)
    (output, err) = process.communicate()
    exit_code = process.wait()
    ciph = output[81:]
    # print(item, output[81:])
    if len(ciph) > 0:
        table[ciph] = item

# print(cipher)
ans = ""
while len(cipher) > 0:
    for key in table:
        if cipher[:len(key)] == key and cipher[len(key)] is not ord('.'):
            print(key, table[key])
            ans = ans + table[key]
            cipher = cipher[len(key):]
    print(ans)
