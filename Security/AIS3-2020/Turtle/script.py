import requests
from bs4 import BeautifulSoup
import base64
import copy

session = requests.Session()
result = session.get("https://turtowl.ais3.org/")
soup = BeautifulSoup(result.text, features="html.parser")
token = soup.find("input", {"name":"csrf_token"})['value']
print(token)

def check_valid(token):
    result = session.post("https://turtowl.ais3.org/?action=login", data={
        "csrf_token": token,
        "username": "admin",
        "password": "admin"
    })
    if result.text == '<script>; document.location.replace("\/");</script>':
        return "Good"
    elif 'Uncaught Exception: token decryption failed in /var/www/html/csrf.php:25' in result.text:
        return False
    elif 'invalid csrf_token' in result.text:
        return True
    else:
        print(result.text)

token = base64.b64decode(token)
flag = []
fake = []
IV_raw = bytearray(token[0:16])
cipher_raw = bytearray(token[16:])
chunks_raw = [cipher_raw[i * 16:i * 16 + 16] for i in range(0, 3)]
for j in range(15, 0, -1):
    for i in range(0, 128):
        if i == 16 - j:
            continue
        IV = copy.deepcopy(IV_raw)
        cipher = copy.deepcopy(cipher_raw)
        chunks = copy.deepcopy(chunks_raw)
        for k in range(j, 16):
            chunks[1][k] ^= 16 - j
        chunks[1][j] ^= i
        ans = check_valid(base64.b64encode(bytes(IV) + bytes(chunks[0]) + bytes(chunks[1]) + bytes(chunks[2])))
        result = i ^ chunks_raw[1][j] ^ j
        if ans:
            print()
            print("--------------------")
            print("Suceed on ", result, i)
            print("--------------------")
            flag.insert(0, result)
            fake.insert(0, i)
    
    print()
    print("**************************")
    print("Done ", j)
    print(flag)
    chunks_raw[1][j] ^= fake[0]
    print("**************************")
