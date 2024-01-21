# expression

- sympy
- tensorflow
- pytorch

## code

```python
import ast


binary_op_map = {
    'Add': '+',
    'Sub': '-',
    'Mult': '*',
    'Div': '/',
    'Pow': '**'
}

unary_op_map = {
    'UAdd': '+',
    'USub': '-'
}


def get_op_name(op_node, op_type):
    op_class_name = op_node.__class__.__name__
    if op_type == 'binary':
        return binary_op_map[op_class_name]
    elif op_type == 'unary':
        return unary_op_map[op_class_name]


class Visitor(ast.NodeVisitor):
    
    def visit_Call(self, node):
        print(node.func.id, end='')
        print('(', end='')
        for arg in node.args:
            self.visit(arg)
        print(')', end='')
    
    def visit_BinOp(self, node):
        print('(', end='')
        self.visit(node.left)
        print(')', end='')
        print(get_op_name(node.op, 'binary'), end='')
        print('(', end='')
        self.visit(node.right)
        print(')', end='')
        
    def visit_UnaryOp(self, node):
        print(get_op_name(node.op, 'unary'), end='')
        print('(', end='')
        self.visit(node.operand)
        print(')', end='')
        
    def visit_Name(self, node):
        print(node.id, end='')
        
    def visit_Num(self, node):
        print(node.n, end='')


if __name__ == '__main__':
    node = ast.parse('2 * (3 + 1)', mode='eval')
    Visitor().visit(node)
```

## default runtime / eager

```python
import ast


class MyVisitor(ast.NodeVisitor):
    def visit_Str(self, node):
        print('Found string "%s"' % node.s)


class MyTransformer(ast.NodeTransformer):
    def visit_Str(self, node):
        return ast.Str('str: ' + node.s)


node = ast.parse('''
favs = ['berry', 'apple']
name = 'peter'

for item in favs:
    print('%s likes %s' % (name, item))
''')


node = MyTransformer().visit(node)
MyVisitor().visit(node)

node = ast.fix_missing_locations(node)
code = compile(node, filename='', mode='exec')

eval(code)
exec(code)
```

## new runtime / lazy

- [task_flow](https://github.com/gaoxinge/task_flow)
