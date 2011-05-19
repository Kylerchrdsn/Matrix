# main
# not much to say

require 'Matrix_'

thing = [0, 0, 0, 0]

A = Matrix.new(2, 2)
B = Matrix.new(2, 2)

A[0][0] = 2

c = A + B

puts( c[0][0], c[0][1], c[1][0], c[1][1] )
