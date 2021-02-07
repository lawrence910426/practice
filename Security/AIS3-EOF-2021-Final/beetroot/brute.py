from pwn import *
from random import randint, choice
from multiprocessing import Process, Pool
from itertools import product
import os 

def get_query(query, ans, jam):
    ret = ""
    index = 0
    for q in query:
        if (ans in q) == (index != jam):
            ret += 'o'
        else:
            ret += 'x'
        index += 1
    return ret


def gen_query(r):
    ans = ""
    for i in range(7, -1, -1):
        if r >= 2 ** i:
            r -= 2 ** i
            ans += str(i)
    return ans


def run(key):
    try:
        query = [gen_query(key[i]) for i in range(6)]
        print(query)

        for real_ans in range(8):
            for jam in range(7):
                res = get_query(query, str(real_ans), jam)
                # print(real_ans, jam, res)
                res = [item == 'o' for item in res]
                for ans in range(8):
                    errors = 0
                    for i in range(6):
                        if res[i] != (str(ans) in query[i]):
                            errors += 1
                    if errors <= 1:
                        if ans != real_ans:
                            raise
                        break
        print("Answer: ", query)
        os.system("echo '" + str(query) + "' > ans.txt")
    except:
        pass


siz = 3
pool = Pool(siz)
jobs = product(range(1, 2 ** 3), repeat=6)
pool.map(run, jobs)

