# Matrix_

# The beginnings of my Ruby translation of the Matrix class.
# This is still very rough.

class Matrix
  def initialize(rowSize, colSize)
    @rowSize = rowSize
    @colSize = colSize
    @matrix = []
    
    rowSize.times { |number|
      @matrix[number] = []
      
      colSize.times { |numberToo|
        @matrix[number][numberToo] = 0
      }
    }
  end
  
  def getRowSize() @rowSize end
  
  def getColSize() @colSize end

  def isSquare()
    truth = (@rowSize == @colSize) ? true : false
    truth
  end

  def [](index)
    @rowSize = (index > @rowSize) ? index + 1 : @rowSize
    @matrix[index]
  end

  def []=(index, value)
    @matrix[index] = value
    @colSize = (index > @colSize) ? index + 1 : @colSize
  end

  def +(matrix)
    if (@rowSize == matrix.getRowSize && @colSize == matrix.getColSize)
      temp = Matrix.new(@rowSize, @colSize)

      @rowSize.times { |number|
       @colSize.times { |numberToo|
         temp[number][numberToo] = @matrix[number][numberToo] + matrix[number][numberToo]
       }
      }

      temp
    end
  end

  private
    attr_accessor :matrix, :rowSize, :colSize
end
