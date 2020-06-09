import sys
from subprocess import Popen, PIPE
import os

cipher = open('TsaiBroSaid', 'rb').read()
domain = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz1234567890_{}"
ans = ["AIS3{y"]

while True:
    best = -1
    ans_temp = []

    for i in domain:
        for item in ans:
            process = Popen(["./TsaiBro", item + i], stdout=PIPE)
            (output, err) = process.communicate()
            exit_code = process.wait()
            
            common = 0
            while common < len(cipher) and common < len(output) and output[common] == cipher[common]:
                common += 1
            
            if cipher[common + 1] is not 46 and common is len(output):
                print(cipher[common + 1], common, len(output))
                print(item + i, common)
                if common == best:
                    ans_temp.append(item + i)
                if common > best:
                    ans_temp = [item + i]
                    best = common
    
    ans = ans_temp
    print(ans, best)
