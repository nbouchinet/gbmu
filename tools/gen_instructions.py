#!/usr/bin/python3
import argparse
from enum import Enum
from collections import namedtuple

class Indexes(Enum):
    NAME = 0
    ARGS = 1
    OPCODE = 2
    CYCLES = 3

Argument = namedtuple("Argument", ["is_deref_addr", "value"])

FORMAT_1 = "exec_instruction([&] () {{ instr_{}({}); }}, {});"

FORMAT_2 = "exec_instruction([&] ({} &v) {{ instr_{}(v{}); }}, {}, {});"

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

parser = argparse.ArgumentParser()
parser.add_argument("file", help="the instruction table file")
parser.add_argument("--debug", help="add debugs prints to std::cerr", action="store_true")
params = parser.parse_args()

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
    if (arg[:2] == "c:"):
        return Argument(False, "JumpCondition::" + CONDITIONS.get(arg[2:]))
    return Argument(False, arg)

def parse_args(args):
    ret = list()
    args = args.split(",")
    for arg in args:
        if arg != "-/-":
            ret.append(get_arg(arg))
    return ret

def print_debug(name, args):
    fmt = 'std::cerr << std::hex << "{}(" << {} << ")" << std::endl;';
    args_list = list()
    args_len = len(args)
    for e in args:
        arg_str = '"'
        if e.is_deref_addr:
            arg_str += "&"
        arg_str += e.value
        if e.value.startswith("JumpCondition::"):
            args_list.append(arg_str + '"')
            continue
        args_list.append(arg_str + '="')
        arg_str = '+'
        if e.is_deref_addr:
            arg_str += "read<Byte>("
        if e.value == "fetch_word()":
            arg_str += 'static_cast<Word>(*it << 8 | *(it + 1))'
        elif e.value == "*it++":
            arg_str += '*it'
        else:
            arg_str += e.value
        if e.is_deref_addr:
            arg_str += ")"
        args_list.append(arg_str)
    if len(args_list) != 0:
        print(fmt.format(name, ' << " " << '.join(args_list)))
    else:
        print(fmt.format(name, '""'))


file = open(params.file, "r")

for line in file:
    if line == "<CB>\n":
       print("case 0xCB:\nswitch(*it++) {")
    elif line == "</CB>\n":
        print("}\nbreak;")
    else:
        line = line.split()
        print("case 0x{}:".format(line[Indexes.OPCODE.value]))
        name = line[Indexes.NAME.value]
        args = parse_args(line[Indexes.ARGS.value])
        cycles = line[Indexes.CYCLES.value]
        if params.debug:
            print_debug(name, args)
        if len(args) != 0 and args[0].is_deref_addr:
            if len(args) < 2:
                print(FORMAT_2.format("Byte", name, "", args[0].value, cycles))
            else:
                if "word" in args[1].value:
                    print(FORMAT_2.format("Word", name, ", " + args[1].value, args[0].value, cycles))
                else:
                    print(FORMAT_2.format("Byte", name, ", " + args[1].value, args[0].value, cycles))
        else:
            str_args = ""
            for e in args:
                if e.is_deref_addr:
                    str_args += "read<Byte>(" + e.value +")"
                else:
                    str_args += e.value
                str_args += ", "
            print(FORMAT_1.format(name, str_args[:len(str_args) - 2], cycles))
        print("break;")
file.close()
