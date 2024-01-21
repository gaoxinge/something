from ctypes import CFUNCTYPE, c_int64
from llvmlite import ir
import llvmlite.binding as llvm


# Generate fibonacci function:
#
# f(n) = 1 if n <= 1 else f(n-1) + f(n-2)
module = ir.Module()
func_type = ir.FunctionType(ir.IntType(64), [ir.IntType(64)])
func = ir.Function(module, func_type, name="fibonacci")
block = func.append_basic_block()
builder = ir.IRBuilder(block)
const_1 = ir.Constant(ir.IntType(64), 1)
const_2 = ir.Constant(ir.IntType(64), 2)
icmp = builder.icmp_signed(cmpop="<=", lhs=func.args[0], rhs=const_1)
with builder.if_then(icmp):
    builder.ret(const_1)
arg_1 = builder.sub(func.args[0], const_1)
arg_2 = builder.sub(func.args[0], const_2)
func_1 = builder.call(func, [arg_1])
func_2 = builder.call(func, [arg_2])
_ = builder.add(func_1, func_2)
_ = builder.ret(_)

print("===================== LLVM IR =====================")
print(module)
print("===================================================")

llvm.initialize()
llvm.initialize_native_target()
llvm.initialize_native_asmprinter()

llvm_module = llvm.parse_assembly(str(module))
target_machine = llvm.Target.from_default_triple().create_target_machine()
with llvm.create_mcjit_compiler(llvm_module, target_machine) as engine:
    engine.finalize_object()

    print("===================== Assembly =====================")
    print(target_machine.emit_assembly(llvm_module))
    print("====================================================")

    func_ptr = engine.get_function_address("fibonacci")
    func_py = CFUNCTYPE(c_int64, c_int64)(func_ptr)
    for n in range(0, 10):
        result = func_py(n)
        print("c_fn_fib({0}) = {1}".format(n, result))
