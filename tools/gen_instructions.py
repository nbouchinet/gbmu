import json

FORMAT_NONE             = "exec_instruction([&] () {{ instr_{}(); }}, {})"

FORMAT_SINGLE           = "exec_instruction([&] () {{ instr_{}({}); }}, {})"
FORMAT_SINGLE_BYTE      = "exec_instruction([&] (Byte &v) {{ instr_{}({}); }}, {}, {})"
FORMAT_SINGLE_WORD      = "exec_instruction([&] (Word &v) {{ instr_{}({}); }}, {}, {})"

FORMAT_DOUBLE           = "exec_instruction([&] () {{ instr_{}({}, {}); }}, {})"
FORMAT_DOUBLE_BYTE      = "exec_instruction([&] (Byte &v) {{ instr_{}({}, {}); }}, {}, {})"
FORMAT_DOUBLE_WORD      = "exec_instruction([&] (Word &v) {{ instr_{}({}, {}); }}, {}, {})"

def get_deref(mnemonic, operand1, operand2):
    if "(" in operand1:
        operand = operand1
    elif "(" in operand2:
        operand = operand2
    else:
        # Should not happen
        abort()
        return None

    operand     = operand[1:-1]
    registers   = {
        "HL": "_hl.word", "DE": "_de.word",
        "C": "_bc.low", "BC": "_bc.word",
        "a16": "fetch_word()", "a8": "*it++",
        "d8": "*it++", "d16": "fetch_word()"
    }
    return registers.get(operand)

def get_reg(mnemonic, operand):
    registers = {
        "AF": "_af.word", "BC": "_bc.word",
        "DE": "_de.word", "HL": "_hl.word",
        "A": "_af.high", "F": "_af.low",
        "B": "_bc.high", "C": "_bc.low",
        "D": "_de.high", "E": "_de.low",
        "H": "_hl.high", "L": "_hl.low",
        "SP": "_sp.word",
        "d8": "*it++", "d16": "fetch_word()",
        "r8": "*it++",
        "SP+r8": "static_cast<Word>(_sp.word + *it++)"
    }

    if mnemonic == "jr" or mnemonic == "jp" or mnemonic == "call" or mnemonic == "ret":
        condprefix = "JumpCondition::"
        conditionals = {
            "C": "Carry", "NC": "NonCarry", "Z": "Zero", "NZ": "NonZero",
        }
        condreg = {
            "r8": "*it++", "a16": "fetch_word()"
        }
        cond = conditionals.get(operand)
        if cond is not None:
            return condprefix + cond
        return condreg.get(operand)

    if mnemonic == "rst":
        rst =  {
            "00H": "0x00", "08H": "0x08",
            "10H": "0x10", "18H": "0x18",
            "20H": "0x20", "28H": "0x28",
            "30H": "0x30", "38H": "0x38"
        }
        return rst.get(operand)

    reg = registers.get(operand)
    if reg is None:
        return operand
    return reg

def gen_code(opcodes):
    for key, opcode in opcodes.items():
        current_format      = None
        deref               = None
        addr                = opcode["addr"]
        mnemonic            = opcode["mnemonic"].lower()
        operand1            = opcode.get("operand1")
        operand2            = opcode.get("operand2")

        cycles              = opcode.get("cycles")
        if len(cycles) > 1:
            cycles = str(cycles[0]) + ", " + str(cycles[1])
        else:
            cycles = str(cycles[0])

        exec_instruction    = None

        first_is_deref = False
        if (operand1 and "(" in operand1) or (operand2 and ("(" in operand2)):
            deref = get_deref(mnemonic, operand1, operand2)
            if operand1 and "(" in operand1:
                first_is_deref = True

        cpp_op1 = get_reg(mnemonic, operand1)
        cpp_op2 = get_reg(mnemonic, operand2)

        # Introducing annoying instruction #1: LDH
        if mnemonic == "ldh":
            if operand1 == "A":
                exec_instruction = FORMAT_DOUBLE_BYTE.format(mnemonic + "_a_v", "_af.high", "v", "0xFF00 + *it++", cycles)
            else:
                exec_instruction = FORMAT_DOUBLE_BYTE.format(mnemonic + "_v_a", "v", "_af.high", "0xFF00 + *it++", cycles)
        elif operand1 and operand2:
            if operand2 == "SP":
                if deref:
                    exec_instruction = FORMAT_DOUBLE_WORD.format(
                            mnemonic.lower(),
                            "v" if first_is_deref else cpp_op1,
                            "v" if not first_is_deref else cpp_op2,
                            deref, cycles)
                else:
                    exec_instruction = FORMAT_DOUBLE.format(mnemonic, cpp_op1, cpp_op2, cycles)
            else:
                if deref:
                    exec_instruction = FORMAT_DOUBLE_BYTE.format(
                            mnemonic.lower(),
                            "v" if first_is_deref else cpp_op1,
                            "v" if not first_is_deref else cpp_op2,
                            deref, cycles)
                else:
                    exec_instruction = FORMAT_DOUBLE.format(mnemonic, cpp_op1, cpp_op2, cycles)
        elif operand1:
            # Thanks to Alaric's handling of these instructions
            if mnemonic == "sub" or mnemonic == "and" or mnemonic == "or" or mnemonic == "xor" or mnemonic == "cp":
                cpp_op1 = "_af.high"
                cpp_op2 = get_reg(mnemonic, operand1)
                first_is_deref = False
                if deref:
                    exec_instruction = FORMAT_DOUBLE_BYTE.format(
                            mnemonic.lower(),
                            "v" if first_is_deref else cpp_op1,
                            "v" if not first_is_deref else cpp_op2,
                            deref, cycles)
                else:
                    exec_instruction = FORMAT_DOUBLE.format(mnemonic, cpp_op1, cpp_op2, cycles)
            elif deref:
                exec_instruction = FORMAT_SINGLE_BYTE.format(mnemonic, "v", deref, cycles)
            else:
                exec_instruction = FORMAT_SINGLE.format(mnemonic, cpp_op1, cycles)
        else:
            exec_instruction = FORMAT_NONE.format(mnemonic, cycles)

        # print(addr, mnemonic, operand1, operand2, cycles, "deref: " + str(deref), exec_instruction, sep="\t")
        print("case " + addr + ":")
        print("  " + exec_instruction + ";")
        print("  break;")


opcodes = open("opcodes.json", "r").read()
opcodes = json.loads(opcodes)

del opcodes["unprefixed"]["0xcb"]

gen_code(opcodes.get("unprefixed"))
print("  case 0xCB:")
print("switch (*it++) {")
gen_code(opcodes.get("cbprefixed"))
print("}")
