def compile(f):
    pos = -1
    ops = []
    stack = []

    while True:
        c = f.read(1)
        if c == "":
            if stack:
                raise Exception("no corresponding ] for [ at pos %s" % stack[-1])
            break
        pos += 1

        if c == ">":
            ops.append((">", -1))
        elif c == "<":
            ops.append(("<", -1))
        elif c == "+":
            ops.append(("+", -1))
        elif c == "-":
            ops.append(("-", -1))
        elif c == ".":
            ops.append((".", -1))
        elif c == ",":
            ops.append((",", -1))
        elif c == "[":
            ops.append(("[", -1))
            stack.append(pos)
        elif c == "]":
            if not stack:
                raise Exception("no corresponding [ for ] at pos %s" % pos)
            left_pos = stack.pop()
            ops[left_pos] = ("[", pos)
            ops.append(("]", left_pos))
        else:
            raise Exception("invalid operator at pos %s" % pos)

    return ops


def vm(ops):
    memory = [0]
    index = 0

    pos = 0
    while True:
        if pos == len(ops):
            break
        op = ops[pos]

        if op[0] == ">":
            index += 1
            if index == len(memory):
                memory.append(0)
            pos += 1 
        elif op[0] == "<":
            index -= 1
            if index == -1:
                raise Exception("invalid memory index")
            pos += 1
        elif op[0] == "+":
            memory[index] += 1
            if memory[index] == 128:
                raise Exception("overflow: bigger than upper bound")
            pos += 1
        elif op[0] == "-":
            memory[index] -= 1
            if memory[index] == -1:
                raise Exception("overflow: smaller than lower bound")
            pos += 1
        elif op[0] == ".":
            print(chr(memory[index]), end="")
            pos += 1
        elif op[0] == ",":
            memory[index] = ord(input())
            pos += 1
        elif op[0] == "[":
            if memory[index] == 0:
                pos = op[1] + 1
            else:
                pos += 1
        elif op[0] == "]":
            pos = op[1]
        else:
            pass


if __name__ == "__main__":
    with open("../test/integer.bf") as f:
        ops = compile(f)
        vm(ops)
    print()

    with open("../test/cycle.bf") as f:
        ops = compile(f)
        vm(ops)
    print()

    with open("../test/helloworld.bf") as f:
        ops = compile(f)
        vm(ops)
    print()
