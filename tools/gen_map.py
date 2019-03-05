import sys
import json
import urllib.request

with urllib.request.urlopen('https://raw.githubusercontent.com/lmmendes/game-boy-opcodes/master/opcodes.json') as url:
    s = url.read()
jsontable = json.loads(s)

i = 1
for key,value in jsontable['unprefixed'].items():
    if value['mnemonic'] == 'PREFIX':
        continue
    if 'operand2' in value:
        print ('{0x' + value['addr'].upper()[2:] + ', {"' + value['mnemonic'] + " " + value['operand1'] + ' ' + value['operand2'] + '", ' + str(value['length']) + '}}, ', end="")
    elif 'operand1' in value:
        print ('{0x' + value['addr'].upper()[2:] + ', {"' + value['mnemonic'] + " " + value['operand1'] + '", ' + str(value['length']) + '}}, ', end="")
    else:
        print ('{0x' + value['addr'].upper()[2:] + ', {"' + value['mnemonic'] + '", ' + str(value['length']) + '}}, ', end="")
    if i % 3 == 0:
        print()
    i += 1

for key,value in jsontable['cbprefixed'].items():
    if 'operand2' in value:
        print ('{0xCB' + value['addr'].upper()[2:] + ', {"' + value['mnemonic'] + " " + value['operand1'] + ', ' + value['operand2'] + '", ' + str(value['length']) + '}}, ', end="")
    elif 'operand1' in value:
        print ('{0xCB' + value['addr'].upper()[2:] + ', {"' + value['mnemonic'] + " " + value['operand1'] + '", ' + str(value['length']) + '}}, ', end="")
    else:
        print ('{0xCB' + value['addr'].upper()[2:] + ', {"' + value['mnemonic'] + '", ' + str(value['length']) + '}}, ', end="")
    if i % 3 == 0:
        print()
    i += 1

#print()
