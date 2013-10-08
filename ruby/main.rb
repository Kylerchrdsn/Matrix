# main
# not much to say

require 'Matrix_'

A = Matrix.new(2, 2)
B = Matrix.new(2, 2)

A[0][0] = 2

C = A + B

puts( "#{C[0][0]}, #{C[0][1]}" )
puts( "#{C[1][0]}, #{C[1][1]}" )

D = Matrix.new

print(D.getRowSize, D.getColSize)
puts(" ")

D[0][0] = 1

print(D.getColSize, D[0][0])
puts(" ")

D[0][1] = 2

print(D.getColSize, D[0][1])
puts(" ")

D[1] [0]=  2

print(D.getRowSize, D[1][0])




