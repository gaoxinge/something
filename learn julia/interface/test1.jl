mutable struct SquaresVector <: AbstractArray{Int, 1}
    count::Int
    st::Int
end

Base.size(S::SquaresVector) = (S.count,)
Base.IndexStyle(::Type{<:SquaresVector}) = IndexLinear()
Base.getindex(S::SquaresVector, i::Int) = i*i + S.st
Base.setindex!(S::SquaresVector, v, i::Int) = (S.st = v * i)

s = SquaresVector(4, 0)
println(s)
println(size(s))

s[1] = 1
println(s)
println(size(s))

s[2] = 1
println(s)
println(size(s))