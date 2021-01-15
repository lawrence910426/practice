from pwn import *

conn = remote("eofqual.zoolab.org", 10110)
line = conn.recvline()
cipher = conn.recvline().decode('UTF-8')
cipher = cipher[9:-33]
cipher = bytes.fromhex(cipher)
line = conn.recvline()

def check_valid(token):
    conn.sendline(token)
    line = conn.recvline()
    ans = line.decode('UTF-8')
    if "系統" in ans:
        return False
    else:
        return True

print(len(cipher) / 8)
