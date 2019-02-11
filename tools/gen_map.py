import sys

def getSize(line):
    size = 1
    line = line.split()[1:2]
    if "CB" in line:
        size += 1
    size += str(line).count('n')
    size += str(line).count('b')
    return str(size)

fileObj=open(sys.argv[1], "r")
print('std::map<int, const char*> m = {', end = '')
i = 0
instr_cb = 0
for line in fileObj.readlines():
    if "CB" in line:
        instr_cb = 1
        continue
    opcode = ''.join(line[:-1].split()[len(line[:-1].split()) - 2])
    instr = ' '.join(line[:-1].split()[:-2])
    if not instr_cb:
        size = getSize(line)
        value = '{0x' + opcode + ', ' + '{\"' + instr + '\", ' + size + '}}, '
    else:
        size = getSize(line)
        value = '{0xCB' + opcode + ', ' + '{\"' + instr + '\", ' + size + '}}, '
    if i % 4 == 0:
        print('')
    print(value, end = '')
    i += 1

print('};')
fileObj.close()
