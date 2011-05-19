# Matrix_

# The beginnings of my Ruby translation of the Matrix class.
# This is still very rough.

class Matrix
  def initialize(rowSize, colSize)
    @rowSize = rowSize
    @colSize = colSize
    @matrix = []
    
    rowSize.times do |rowSize|
      @matrix[rowSize] = []

      colSize.times do |colSize|
        @matrix[rowSize][colSize] = 0 end
    end
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
