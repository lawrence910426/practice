import pickle
from base64 import b64decode, b64encode

plaintext = open('user.pickle', 'rb').read()
for item in plaintext:
    print(hex(item), end=' ')
print(plaintext.decode('ascii'))
cipher = b64decode('cipher')

