struct Squares
    count::Int
end

Base.iterate(S::Squares, state=1) = state > S.count ? nothing : (state * state, state + 1)

for i in Squares(7)
    println(i)
end