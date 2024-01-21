# compile in python

## flow

From [PEP 339 -- Design of the CPython Compiler](https://www.python.org/dev/peps/pep-0339/), we have

- Parse source code into a parse tree (Parser/pgen.c)
- Transform parse tree into an Abstract Syntax Tree (Python/ast.c)
- Transform AST into a Control Flow Graph (Python/compile.c)
- Emit bytecode based on the Control Flow Graph (Python/compile.c)

## abstract syntax tree

From [ast — Abstract Syntax Trees](https://docs.python.org/3/library/ast.html#abstract-grammar), we can operate on ast easily.

### get a node / AST class

```python
import ast

node = ast.UnaryOp(ast.USub(), ast.Num(5, lineno=0, col_offset=0), lineno=0, col_offset=0) 

node = ast.BinOp(ast.Str('xy'), ast.Mult(), ast.Num(3))
node = ast.fix_missing_locations(node)  # fill lineno and col_offset

node = ast.parse('1+2', mode='eval')  # equivalent to compile('1+2', filename='<string>', mode='eval', flags=ast.PyCF_ONLY_AST)
```

### operate on node / AST class

```python
import ast

class MyVisitor(ast.NodeVisitor):
    def visit_Str(self, node):
        print 'Found string "%s"' % node.s


node = ast.parse('''
favs = ['berry', 'apple']
name = 'peter'

for item in favs:
    print '%s likes %s' % (name, item)
''')

MyVisitor().visit(node)
```

```python
import ast

class MyVisitor(ast.NodeVisitor):
    def visit_Str(self, node):
        print 'Found string "%s"' % node.s


class MyTransformer(ast.NodeTransformer):
    def visit_Str(self, node):
        return ast.Str('str: ' + node.s)


node = ast.parse('''
favs = ['berry', 'apple']
name = 'peter'

for item in favs:
    print '%s likes %s' % (name, item)
''')

MyTransformer().visit(node)
MyVisitor().visit(node)
```

### generate code from ast

- [andreif/codegen](https://github.com/andreif/codegen)
- [berkerpeksag/astor](https://github.com/berkerpeksag/astor)

## symbol table

Symbol tabel is created in step3 and used to generate byte code in step4. From [symtable — Access to the compiler’s symbol tables](https://docs.python.org/3.7/library/symtable.html), we can operate on ast easily.

### get a symbol table

```python
import symtable
table = symtable.symtable("def some_func(): pass", "<string>", "exec")
table = symtable.symtable("""
def outer(aa):
    def inner():
        bb = 1
        return aa + bb + cc
    return inner
""", "<string>", "exec")
```

### operate a symbol table

```python
import symtable


def describe_symbol(sym):
    assert type(sym) == symtable.Symbol
    print("Symbol:", sym.get_name())

    for prop in [
            'referenced', 'imported', 'parameter',
            'global', 'declared_global', 'local',
            'free', 'assigned', 'namespace']:
        if getattr(sym, 'is_' + prop)():
            print('    is', prop)


# test1
table = symtable.symtable("""
def outer(aa):
    def inner():
        bb = 1
        return aa + bb + cc
    return inner
""", "<string>", "exec")

inner_table = table.get_children()[0].get_children()[0]
aa_symbol = inner_table.lookup("aa")
bb_symbol = inner_table.lookup("bb")
cc_symbol = inner_table.lookup("cc")
describe_symbol(aa_symbol)
describe_symbol(bb_symbol)
describe_symbol(cc_symbol)

print("=======================================================")

# test2 
table =  symtable.symtable("""
def outer():
    global gg
    return ff + gg
""", "<string>", "exec")

outer_table = table.get_children()[0]
ff_symbol = outer_table.lookup("ff")
gg_symbol = outer_table.lookup("gg")
describe_symbol(ff_symbol)
describe_symbol(gg_symbol)
```

```python
import symtable


def describe_symtable(st, recursive=True, indent=0):
    def print_d(s, *args):
        prefix = ' ' * indent
        print(prefix + s, *args)

    assert isinstance(st, symtable.SymbolTable)
    print_d('Symtable: type=%s, id=%s, name=%s' % (
                st.get_type(), st.get_id(), st.get_name()))
    print_d('  nested:', st.is_nested())
    print_d('  has children:', st.has_children())
    print_d('  identifiers:', list(st.get_identifiers()))

    if recursive:
        for child_st in st.get_children():
            describe_symtable(child_st, recursive, indent + 5)


table = symtable.symtable("""
def outer(aa):
    def inner():
        bb = 1
        return aa + bb + cc
    return inner
""", "<string>", "exec")


describe_symtable(table)
```

## code object / byte code

### get code object / byte code

```python
import dis


def f(a):
    return a
    
    
class A:
    
    def __init__(self, a):
        self.a = a
        
    def f(self, b):
        return self.a + b
        
        
dis.dis(f)       # dis.dis(f.__code__) or dis.dis(f.func_code)
dis.dis(A.f)     # dis.dis(A.f.__code__) or dis.dis(A.f.func_code)
dis.dis(A(1).f)  # dis.dis(A(1).f.__code__) or dis.dis(A(1).f.func_code)
```

```python
# compile(source_code, ...) or compile(ast, ...)
a = compile("""
sum([1, 2])""", "<string>", "eval")
print(eval(a))


a = compile("""
print 'hello world1'
print 'hello world2'
""", "<string>", "single")
exec a


a = compile("""
print 'hello world1'
print 'hello world2'
""", "<string>", "exec")
exec a
```

```python
# int == types.IntType
import types

def f():
    print 1
    
print(isinstance(f.__code__, types.CodeType))
```

```python
import dis
import opcode

print(dis.opname[100])
print(dis.opname[1])
print(opcode.opname[100])
print(opcode.opname[1])
```

### generate code from bytecode

- [Exploring and decompiling python bytecode [closed]](https://stackoverflow.com/questions/1149513/exploring-and-decompiling-python-bytecode)

### reference

- [python笔记_codeobject](https://www.jianshu.com/p/649ba6219d06)
- [Exploring Python Code Objects](https://late.am/post/2012/03/26/exploring-python-code-objects.html)
- [What is a Python code object?](https://stackoverflow.com/questions/5768684/what-is-a-python-code-object)
- [How to create a code object in python?](https://stackoverflow.com/questions/16064409/how-to-create-a-code-object-in-python)

## pyc

### code

- eval
  - [ceval.c](https://github.com/gaoxinge/cpython/blob/master/Python/ceval.c)
- frame
  - [frameobject.c](https://github.com/gaoxinge/cpython/blob/master/Objects/frameobject.c)
  - [frameobject.h](https://github.com/gaoxinge/cpython/blob/master/Include/frameobject.h)
- module
  - [moduleobject.c](https://github.com/gaoxinge/cpython/blob/master/Objects/moduleobject.c)
  - [moduleobject.h](https://github.com/gaoxinge/cpython/blob/master/Include/moduleobject.h)
  - [moduleobject.c.h](https://github.com/gaoxinge/cpython/blob/master/Objects/clinic/moduleobject.c.h)
- import
  - [import.c](https://github.com/gaoxinge/cpython/blob/master/Python/import.c)
  - [import.c.h](https://github.com/gaoxinge/cpython/blob/master/Python/clinic/import.c.h)
- marshal
  - [marshal.c](https://github.com/gaoxinge/cpython/blob/master/Python/marshal.c)
  - [marshal.h](https://github.com/gaoxinge/cpython/blob/master/Include/marshal.h)
  - [marshal.c.h](https://github.com/gaoxinge/cpython/blob/master/Python/clinic/marshal.c.h)
  
### eval

Eval is python virtual machine, it creates frame object to compute or calculate code object based on the bytecode of the code object. This happens after compile procedure, and in the import or call procedure.

### import

- find the file
- check the file need to compile or recompile
- if need, compile the file to pyc
- unmarshal the pyc, and extract the code object from the result
- eval the code object

Here is some references:

- [How to generate byte code file in python ?](https://www.geeksforgeeks.org/generate-byte-code-file-python/)
- [Compiling Python Code](http://effbot.org/zone/python-compile.htm)
- [imp — Access the import internals](https://docs.python.org/3.7/library/imp.html)
- [importlib — The implementation of import](https://docs.python.org/3.7/library/importlib.html)

### marshal

- marshal and unmarshal is used between codeobject and pyc
- marshal and pickle is different

Here is some references:

- [The marshal module](http://effbot.org/librarybook/marshal.htm)
- [marshal — Internal Python object serialization](https://docs.python.org/2/library/marshal.html)