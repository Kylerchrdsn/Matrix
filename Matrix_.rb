# Matrix_

# The beginnings of my Ruby translation of the Matrix class.
# This is still very rough.

class Matrix
  #**************************************************
  # constructor                                     *
  #**************************************************
  def initialize(rowSize = 1, colSize = 1)
    @rowSize = rowSize
    @colSize = colSize
    @matrix = []
    
    rowSize.times { |i|
      @matrix[i] = []
      
      colSize.times { |j|
        @matrix[i][j] = 0
      }
    }
  end

  #**************************************************
  # getters and setters                             *
  #**************************************************
  def getRowSize() @rowSize end

  #**************************************************
  def getColSize() @colSize end

  #**************************************************
  def setDimension(rowSize, colSize)
      
      (@rowSize - rowSize).times {
        @matrix.pop } if(rowSize < @rowSize)

      setRowSize(rowSize)

      @rowSize.times { |i|
        @matrix[i].pop(@colSize - colSize) } if(colSize < @colSize)

      @rowSize.times do |i|
        @colSize - colSize .times do |j|
          @matrix[i][j + @colSize] = 0
        end
      end if (colSize > @colSize)

      setColSize(colSize)

  end

  #**************************************************
  # functions needed to perform matrix operations   *
  #**************************************************
  def isSquare()

    truth = (@rowSize == @colSize) ? true : false
    truth

  end

  #**************************************************
  # overloaded operators ( [], + )                  *
  #**************************************************
  def [](index)

    @rowSize = (index >= @rowSize) ? index + 1 : @rowSize
    @matrix[index] = [] if (@matrix[index] == nil)
    @matrix[index]

  end

  #**************************************************
  def +(matrix)
    if (@rowSize == matrix.getRowSize && @colSize == matrix.getColSize)

      temp = Matrix.new(@rowSize, @colSize)

      @rowSize.times { |i|
       @colSize.times { |j|
         temp[i][j] = @matrix[i][j] + matrix[i][j]
       }
      }

      temp

    end
  end

  #**************************************************
  # private data members                            *
  #**************************************************
  private
    attr_accessor :matrix, :rowSize, :colSize

    #**************************************************
    def setColSize(colSize) @colSize = colSize end

    #**************************************************
    def setRowSize(rowSize) @rowSize = rowSize end

end
