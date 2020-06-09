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
        return False
    elif 'Uncaught Exception: token decryption failed in /var/www/html/csrf.php:25' in result.text:
        return False
    elif 'invalid csrf_token' in result.text:
        return True
    else:
        print(result.text)

def convert(token):
    return base64.b64encode(bytes(token[0]) + bytes(token[1]) + bytes(token[2]) + bytes(token[3]))

token = base64.b64decode(token)
cipher_raw = [bytearray(token[i * 16:i * 16 + 16]) for i in range(4)]
cipher = copy.deepcopy(cipher_raw)
plaintext = []

for chunk in range(2, 3):
    for offset in range(1, 17):
        cipher[chunk][16 - offset] = 0
        for i in range(offset):
            cipher[chunk][15 - i] ^= offset
        
        for guess in range(256):
            cipher[chunk][16 - offset] ^= guess
            result = check_valid(convert(cipher))
            if result:
                ans = guess ^ cipher_raw[chunk][16 - offset]
                cipher[chunk][16 - offset] ^= guess
                plaintext.insert(0, ans)
                print()
                print("Found: ", ans)
                print(plaintext)
                print()
            else:
                pass
                # print(guess, end=' ')
                # print()
            cipher[chunk][16 - offset] ^= guess
        
        for i in range(offset):
            cipher[chunk][15 - i] ^= offset
