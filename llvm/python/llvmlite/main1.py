from ctypes import CFUNCTYPE, c_int
from llvmlite import ir
import llvmlite.binding as llvm


# Create a new module with a function implementing this:
#
# int sum(int a, int b) {
#   return a + b;
# }
module = ir.Module()
func_type = ir.FunctionType(ir.IntType(32), [ir.IntType(32), ir.IntType(32)])
func = ir.Function(module, func_type, name="sum")
# func.args[0].name = "a"
# func.args[1].name = "b"
block = func.append_basic_block()
# block.name = "entry"
builder = ir.IRBuilder(block)
_ = builder.add(func.args[0], func.args[1])
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

    func_ptr = engine.get_function_address("sum")
    func_py = CFUNCTYPE(c_int, c_int, c_int)(func_ptr)
    res = func_py(17, 42)
    print("The result is", res)
