from pwn import *
from random import randint, choice
from multiprocessing import Process, Pool

def runner(foo):
    while True:
        try:
            host, port = 'eof01.zoolab.org', 42069
            r = remote(host, port)

            def gen_rand():
                r = randint(0, 2 ** 8)
                ans = ""
                for i in range(7, -1, -1):
                    if r > 2 ** i:
                        r -= 2 ** i
                        ans += str(i)
                return ans
                
            query = [gen_rand() for _ in range(6)]
            print(query)

            table = {}
            for q in query:
                table[q] = set(q)

            for _ in range(100):
                ans = None
                for q in query:
                    r.recvuntil(":".encode('utf-8'))
                    r.sendline(q.encode('utf-8'))
                res = r.recvline()[1:-1]
                res = str(res)[2:-1]
                print(res)
                res = [item == 'o' for item in res]
                for ans in range(8):
                    errors = 0
                    for i in range(6):
                        if res[i] != (str(ans) in query[i]):
                            errors += 1
                    if errors <= 1:
                        print(errors, ans)
                        r.sendline(str(ans).encode('utf-8'))
                        break

            res = r.recvline()
            print(res)
        except:
            pass

siz = 100
pool = Pool(siz)
pool.map(runner, [None for _ in range(siz)])

