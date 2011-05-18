# Matrix_

# The beginnings of my Ruby translation of the Matrix class.
# This is still very rough.

class Matrix
  def initialize(rowSize, colSize, matrix)
    @rowSize = rowSize
    @colSize = colSize
    @matrix = matrix
  end

  def [](index)
    @matrix[index]
  end

  def []=(index, value)
    @matrix[index] = value
    @rowSize = (index > @rowSize) ? index + 1 : @rowSize
  end

  private
    attr_accessor :matrix, :rowSize, :colSize
end
