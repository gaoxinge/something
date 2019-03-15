## basic

- the basic integer and float types (signed and unsigned): `Int8`, `UInt8`, `Int16`, `UInt16`, `Int32`, `UInt32`, `Int64`, `UInt64`, `Int128`, `UInt128`, `Float16`, `Float32`, and `Float64`
- more advanced numeric types: `BigFloat`, `BigInt`
- Boolean and character types: `Bool` and `Char`
- Text string types: `String`

### number

![1](https://github.com/gaoxinge/dive-into-coding/blob/master/julia/type%20system/1.png)
![2](https://github.com/gaoxinge/dive-into-coding/blob/master/julia/type%20system/2.png)

### char

```
Char ---> AbstractChar ---> Any
```

### string

```
String ---> AbstractString ---> Any
```

## special

```
Any     # all objects are of this type
Union{} # subtype of all types, no object can have this type
Nothing # type indicating nothing, subtype of Any
nothing # only instance of Nothing
Missing # type indicating missing value
missing # only instance of Missing
```

## abstract type

```julia
abstract type Number end
abstract type Real <: Number end
```

```julia
# Pointy{1} <: Pointy
# Pointy{Int64} <: Pointy
# Pointy{Float64} <: Pointy
# Pointy{Real} <: Pointy
abstract type Pointy{T} end

# Pointy{Int64} <: Pointy
# Pointy{Float64} <: Pointy
# Pointy{Real} <: Pointy
abstract type Pointy{T<:Real} end
```

## struct type

```julia
struct Foo
    bar
    baz::Int
    qux::Float64
end
```

```julia
mutable struct Bar
    baz
    qux::Float64
end
```

```julia
# Point{Float64} <: Point
# Point{AbstractString} <: Point
struct Point{T}
    x::T
    y::T
end
```

```julia
struct OrderedPair
    x::Real
    y::Real
    OrderedPair(x, y) = x > y ? error("out of order") : new(x, y)
end
```

```julia
struct Point{T<:Real}
    x::T
    y::T
    Point{T}(x, y) where {T<:Real} = new(x, y)
    # right !!!
    # Point(x::T, y::T) where {T<:Real} = Point{T}(x,y)
    # wrong !!!
    # Point{T<:Real}(x, y) = new(x, y)
end
```
