import os
import pickle
import random
from base64 import b64decode, b64encode
from Crypto.Util import Counter
from Crypto.Cipher import Blowfish

p = open('user.pickle','rb').read()

with open('test.pickle', 'wb') as handle:
    payload = [{'name':'A', 'password':'A', 'admin': True} for _ in range(7)]
    payload.append('A' * 46)
    pickle.dump(payload, handle, protocol=pickle.HIGHEST_PROTOCOL)
pp = open('test.pickle','rb').read()

print(len(p), len(pp))

# key = os.urandom(8)
# iv = random.randint(0, 2**64)

# ctr = Counter.new(64, initial_value=iv, little_endian=True)
# cipher = Blowfish.new(key, Blowfish.MODE_CTR, counter=ctr)

# TOKEN = cipher.encrypt(p)

print('''
                         .
                          A       ;
                |   ,--,-/ \---,-/|  ,
               _|\,'. /|      /|   `/|-.
           \`.'    /|      ,            `;.
          ,'\   A     A         A   A _ /| `.;
        ,/  _              A       _  / _   /|  ;
       /\  / \   ,  ,           A  /    /     `/|
      /_| | _ \         ,     ,             ,/  \ 
     // | |/ `.\  ,-      ,       ,   ,/ ,/      \/ 
     / @| |@  / /'   \  \      ,              >  /|    ,--.
    |\_/   \_/ /      |  |           ,  ,/        \  ./' __:..
    |  __ __  |       |  | .--.  ,         >  >   |-'   /     `
  ,/| /  '  \ |       |  |     \      ,           |    /
 /  |<--.__,->|       |  | .    `.        >  >    /   (
/_,' \\  ^  /  \     /  /   `.    >--            /^\   |
      \\___/    \   /  /      \__'     \   \   \/   \  |
       `.   |/          ,  ,                  /`\    \  )
         \  '  |/    ,       V    \          /        `-\ 
          `|/  '  V      V           \    \.'            \_
           '`-.       V       V        \./'\ 
               `|/-.      \ /   \ /,---`\ 
                /   `._____V_____V'
                           '     '
''')

# print("Your token:", b64encode(TOKEN).decode(), end="\n\n")
# username = input('username : ')
# password = input('password : ')
TOKEN    = input("TOKEN : ")
TOKEN = b64decode(TOKEN)
TOKEN = bytearray(TOKEN)
for i in range(192):
    TOKEN[i] ^= p[i] ^ pp[i]
TOKEN = bytes(TOKEN)
print(b64encode(TOKEN))
# ctr = Counter.new(64, initial_value=iv, little_endian=True)
# cipher = Blowfish.new(key, Blowfish.MODE_CTR, counter=ctr)
# print()

