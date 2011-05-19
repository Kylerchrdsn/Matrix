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

puts( D[0][0] )

