## basic 

- number
- character
- string 

## array

```
julia> [1, 2, 3, 4, 5]
julia> [1 2 3 4 5]
julia> [1 2 3 4; 5 6 7 8]
julia> [1, "2", 3.0, sin, pi]
```

```
julia> Array{Int64}(undef, 5)
julia> Int64[]
julia> Vector(undef, 5)
julia> Matrix(undef, 5, 5)
julia> 1:10
```

## tuple

```
julia> (1, 2, 3, 4, 5)
julia> (a=1, b=2, c=3, d=4, e=5)
```

## dictionary

```
julia> Dict("a" => 1, "b" => 2, "c" => 3)
julia> Dict{String, Int64}()
```

## set

```
julia> Set()
julia> Set{Int64}()
```