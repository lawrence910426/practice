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
        print("GOOD")
        return "Good"
    elif 'Uncaught Exception: token decryption failed in /var/www/html/csrf.php:25' in result.text:
        return False
    elif 'invalid csrf_token' in result.text:
        return True
    else:
        print(result.text)

token = base64.b64decode(token)
flag = []
IV_raw = bytearray(token[0:16])
cipher_raw = bytearray(token[16:])
chunks_raw = [cipher_raw[i * 16:i * 16 + 16] for i in range(3)]
chunks_raw.insert(0, IV_raw)

for c in range(2, 3):
    for offset in range(1, 17):
        chunk_temp = copy.deepcopy(chunks_raw)
        for guess in range(0, 256):
            if guess == offset:
                continue

            chunks = copy.deepcopy(chunk_temp)
            
            for i in range(offset):
                chunks[c][15 - i] ^= offset
            chunks[c][16 - offset] ^= guess
            
            temp = bytes()
            for i in range(4):
                temp += bytes(chunks[i])
            ans = check_valid(base64.b64encode(temp))
            if ans:
                print()
                print("Done")
                print(guess ^ chunks_raw[c][16 - offset] ^ offset, guess)
                print(c, offset, guess)
                print()
                chunk_temp[c][16 - offset] ^= offset
            else:
                print(guess, end=' ')


