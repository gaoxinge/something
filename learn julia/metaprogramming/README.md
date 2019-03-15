## mechanism

- parse code into surface-syntax AST
- lower this high-level AST into an intermediate AST (macro will expend in this step)
- execute and evaluate the intermediate AST

## Expr

```
julia> :(1 + 1)
julia> Meta.parse("1 + 1")
julia> Expr(:call, :+, 1, 1)
```

```
julia> quote 1 + 1 end
julia> a = 1
julia> :($a + 1)  # string interpolation and command interpolation
:(1 + 1)
julia> :($:(a = 1))  # $: = id
:(a = 1)
julia> :(f(1, $([:(a=1), :(b=2), :(c=3)]...)))  # varargs function
```

- show_sexpr
- isexpr
- eval

## Symbol

```
julia> :foo
julia> Symbol("foo")
```

## macro

```
julia> macro f() 1 end
@f (macro with 1 method)
julia> @f()
1
julia> @f
1
```

## conclusion

- interesting
- complex