## introduction

Function declaration and definition is different from function assignment in Julia.

## function declaration and definition

```julia
function f(x)
    x + 1
end

g(x) = x + 1

function (x)
    x + 1
end

x -> x + 1
```

## function assignment

```julia
f_ = f
g_ = g
h_ = function (x)
    x + 1
end
h_ = x -> x + 1
```

## repl

In repl, we can see 

```
julia> f = g(x) = x + 1
g (generic function with 1 method)

julia> g
g (generic function with 1 method)

julia> f
g (generic function with 1 method)

julia> g = 1
ERROR: invalid redefinition of constant g
Stacktrace:
 [1] top-level scope at none:0

julia> function f(x)
       x
       end
ERROR: cannot define function f; it already has a value
Stacktrace:
 [1] top-level scope at none:0
```

## conclusion

- the variable, which binds to an object by function declaration and definition, can not be reassigned
- the variable, which binds to an object by assignment, can not be function redeclared and redefined

## reference

- [julia function declaration style](https://stackoverflow.com/questions/48481547/julia-function-declaration-style)