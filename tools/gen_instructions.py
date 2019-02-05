#!/usr/bin/python3
import sys
from enum import Enum
from collections import namedtuple

class Indexes(Enum):
    NAME = 0
    ARGS = 1
    OPCODE = 2
    CYCLES = 3

Argument = namedtuple("Argument", ["is_deref_addr", "value"])

FORMAT_1 = """case 0x{}:
  exec_instruction([&] () {{ instr_{}({}); }}, {});
  break;"""

FORMAT_2 = """case 0x{}:
  exec_instruction([&] ({} &v) {{ instr_{}(v{}); }}, {}, {});
  break;"""

REGISTERS = {"A": "_af.high", "F": "_af.low", "AF": "_af.word",
             "B": "_bc.high", "C": "_bc.low", "BC": "_bc.word",
             "D": "_de.high", "E": "_de.low", "DE": "_de.word",
             "H": "_hl.high", "L": "_hl.low", "HL": "_hl.word",
             "SP": "_sp.word"}

CONDITIONS = { "-": "None",
               "NZ": "NonZero",
               "Z": "Zero",
               "NC": "NonCarry",
               "C": "Carry"}

def get_arg(arg):
    fmt = "{}"
    is_deref_addr = False
    if arg[0] == "(":
        arg = arg[1:len(arg)-1]
        is_deref_addr = True
    if arg[:6] == "$FF00+":
        fmt = fmt.format("0xFF00 + {}")
        arg = arg[6:]
    if arg in ("n", "b"):
        return Argument(is_deref_addr, fmt.format("*it++"))
    if arg == "nn":
        return Argument(is_deref_addr, fmt.format("fetch_word()"))
    register = REGISTERS.get(arg)
    if register != None:
        return Argument(is_deref_addr, fmt.format(register))
    if arg == "-/-":
        return Argument(False, "")
    if (arg[:2] == "c:"):
        return Argument(False, "JumpCondition::" + CONDITIONS.get(arg[2:]))
    return Argument(False, arg)

def parse_args(args):
    ret = list()
    args = args.split(",")
    for arg in args:
        ret.append(get_arg(arg))
    return ret

if len(sys.argv) != 2:
    sys.exit(1)
file = open(sys.argv[1], "r")

for line in file:
    if line == "<CB>\n":
        print("""case 0xCB:\nswitch(*it++) {""")
    elif line == "</CB>\n":
        print("}\nbreak;")
    else:
        line = line.split()
        name = line[Indexes.NAME.value]
        args = parse_args(line[Indexes.ARGS.value])
        opcode = line[Indexes.OPCODE.value]
        cycles = line[Indexes.CYCLES.value]
        if args[0].is_deref_addr:
            if len(args) < 2:
                print(FORMAT_2.format(opcode, "Byte", name, "", args[0].value, cycles))
            else:
                if "word" in args[1].value:
                    print(FORMAT_2.format(opcode, "Word", name, ", " + args[1].value, args[0].value, cycles))
                else:
                    print(FORMAT_2.format(opcode, "Byte", name, ", " + args[1].value, args[0].value, cycles))
        else:
            str_args = ""
            for e in args:
                if e.is_deref_addr:
                    str_args += "read<Byte>(" + e.value +")"
                else:
                    str_args += e.value
                str_args += ", "
            print(FORMAT_1.format(opcode, name, str_args[:len(str_args) - 2], cycles))
file.close()
