#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>
#include <vector>
#include <algorithm>

template <typename T>
class Matrix
{
    public:
        // constructor and destructor
        Matrix(int row = 1, int col = 1);
        ~Matrix();

        // public getters and setters
        int getColSize() const;
        int getRowSize() const;
        T** getMatrix() const;
        void setMatrix(T**);

        // function to display the matrix
        void display();

        // overloaded operators ( *, [], =, +, - )
        Matrix<T>* operator *(const Matrix<T>& mat) const;
        T* operator [](int index) const;
        void operator =(Matrix<T>* matrix_);
        Matrix<T>* operator +(const Matrix<T>& matrix_) const;
        Matrix<T>* operator -(const Matrix<T>& matrix_) const;

        // matrix specific operations
        T tr();
        T det();
        void ref();
        void rref();
        void trans();
        void inverse();
        void adj();

        // functions needed to perform matrix operations
        bool isSquare();
        int findNonZeroEle(int col);
        void swapRows(int row1, int row2);
        void makeOne(int row, int col);
        void killDown(int startRow, int col);
        void killUp(int startRow, int col);

    private:
        // the matrix
        T** matrix;

        // matrix dimention
        int rowSize,
            colSize;

        std::vector<int>* flagedRows;

        // private setters
        void setRowSize(int);
        void setColSize(int);


};

//***************************************************************
// constructor and destructor                                   *
//***************************************************************
template <typename T>
Matrix<T>::Matrix(int row, int col)
{
    setColSize(col);
    setRowSize(row);
    matrix = new T*[rowSize];

    for(int i = 0; i < rowSize; i++)
    {
        matrix[i] = new T[colSize];
    }

    matrix[0][0] = 0;
    flagedRows = new std::vector<int>;
}

//***************************************************************
template <typename T>
Matrix<T>::~Matrix()
{
    for(int i = 0; i < rowSize; i++)
    {
        delete [] matrix[i];
    }

    delete [] matrix;
    delete flagedRows;
}

//***************************************************************
// public getters and setters                                   *
//***************************************************************
template <typename T>
int Matrix<T>::getColSize() const
{
    return colSize;
}

//***************************************************************
template <typename T>
int Matrix<T>::getRowSize() const
{
    return rowSize;
}

//***************************************************************
template <typename T>
T** Matrix<T>::getMatrix() const
{
   return matrix;
}

//***************************************************************
template <typename T>
void Matrix<T>::setMatrix(T** matrix_)
{
    matrix = matrix_;
}

//***************************************************************
// function to display the matrix                               *
//***************************************************************
template <typename T>
void Matrix<T>::display()
{
    for(int j = 0; j < rowSize; j++)
    {
        std::cout << "[ ";
        for(int i = 0; i < colSize; i++)
        {
            std::cout << matrix[j][i] << " ";
        }
        std::cout << "]" << std::endl;
    }
}

//***************************************************************
// overloaded operators ( *, [], =, +, -, ^ )                   *
//***************************************************************
template <typename T>
T* Matrix<T>::operator [](int index) const
{
    return matrix[index];
}

//***************************************************************
template <typename T>
Matrix<T>* Matrix<T>::operator *(const Matrix<T>& mat) const
{
    Matrix<T>* temp = NULL;
    T total;

    if(colSize == mat.getRowSize())
    {
        temp = new Matrix<T>(rowSize, mat.getColSize());
        for(int i = 0; i < rowSize; i++)
        {
            for(int j = 0; j < mat.getColSize(); j++)
            {
                total = 0;

                for(int k = 0; k < colSize; k++)
                {
                    total += ((*this)[i][k] * mat[k][j]);
                }

                (*temp)[i][j] = total;
            }
        }
    }

    return temp;
}

//***************************************************************
template <typename T>
void Matrix<T>::operator =(Matrix<T>* mat)
{
    if(mat)
    {
        for(int i = 0; i < rowSize; i++)
        {
            delete [] matrix[i];
        }

        delete [] matrix;

        matrix = mat->getMatrix();

        colSize = mat->getColSize();
        rowSize = mat->getRowSize();

        T** temp = new T*[mat->getRowSize()];

		for(int i = 0; i < mat->getRowSize(); i++)
		{
			temp[i] = new T[mat->getColSize()];
		}

        mat->setMatrix(temp);

        delete mat;
    }
}

//***************************************************************
template <typename T>
Matrix<T>* Matrix<T>::operator +(const Matrix<T>& matrix_) const
{
    Matrix<T>* temp = NULL;

    if(rowSize == matrix_.getRowSize() && colSize == matrix_.getColSize())
    {
        temp = new Matrix<T>(rowSize, colSize);

        for(int i = 0; i < rowSize; i++)
        {
            for(int j = 0; j < colSize; j++)
            {
                (*temp)[i][j] = (*this)[i][j] + matrix_[i][j];
            }
        }
    }

    return temp;
}

//***************************************************************
template <typename T>
Matrix<T>* Matrix<T>::operator -(const Matrix<T>& matrix_) const
{
    Matrix<T>* temp = NULL;

    if(rowSize == matrix_.getRowSize() && colSize == matrix_.getColSize())
    {
        temp = new Matrix<T>(rowSize, colSize);

        for(int i = 0; i < rowSize; i++)
        {
            for(int j = 0; j < colSize; j++)
            {
                (*temp)[i][j] = (*this)[i][j] - matrix_[i][j];
            }
        }
    }

    return temp;
}

//***************************************************************
template <typename T>
int operator ^(const Matrix<T>& matrix_, int exp)
{
    int total = 1;

    for(int i = 0; i < exp; i++)
    {
        total *= (-1);
    }

    return total;
}

//***************************************************************
// matrix specific operations                                   *
//***************************************************************
template <typename T>
T Matrix<T>::tr()
{
    T trace = 0;

    if(isSquare())
    {
        for(int i = 0; i < rowSize; i++)
        {
            trace += (*this)[i][i];
        }
    }
    else
    {
        trace = 9001;
    }

    return trace;
}

//***************************************************************
template <typename T>
T Matrix<T>::det()
{
    T value = 0; //value of the determinant
    Matrix<T>* temp; //temporary matrix to hold the expansion matrix

    if(isSquare()) //if the matrix is square
    {
        if(rowSize > 2) //if the matrix is larger than 2x2
        {
            for(int i = 0; i < rowSize; i++) //expand
            {
                temp = new Matrix<T>(rowSize - 1, colSize - 1); //create expansion matrix

                for(int j = 0; j < rowSize; j++)
                {
                    for(int k = 0; k < colSize; k++)
                    {
                        if(j == 0 || k == i){
                        }
                        else
                        {
                            if(k <= i || i == rowSize - 1)
                            {
                                (*temp)[j - 1][k] = matrix[j][k];
                            }
                            else
                            {
                                (*temp)[j - 1][k - 1] = matrix[j][k];
                            }
                        }
                    }
                }

                value += (((*this)^(1 + (i + 1))) * matrix[0][i] * temp->det()); //value = value + current expension term

                delete temp;
            }
        }
        else if(rowSize == 2) //else if the matrix is 2x2
        {
            value = ((*this)[0][0] * (*this)[1][1]) - ((*this)[0][1] * (*this)[1][0]); //compute 2x2 determinant
        }
        else
        {
            value = 9001; //not possible to compute
        }
    }
    else //otherwise
    {
        value = 9001; //not possible to compute
    }

    return value;
}

//***************************************************************
template <typename T>
void Matrix<T>::ref()
{
    bool flag = false;

    for(int i = 0; i < rowSize; i++)
    {
        for(int j = 0; j < colSize; j++)
        {
            if(i == j)
            {
                if(matrix[i][j] == 0)
                {
                    if(findNonZeroEle(j) != -1)
                    {
                        swapRows(i ,findNonZeroEle(j));
                    }
                    else
                    {
                        flag = true;
                    }
                }

                if(!flag)
                {
                    makeOne(i, j);
                    killDown(i, j);
                    flagedRows->push_back(i);
                }
            }
            else if(flag)
            {
                if(findNonZeroEle(j) != -1)
                {
                    swapRows(i ,findNonZeroEle(j));
                    flag = false;
                }
                else
                {
                    flag = true;
                }

                if(!flag)
                {
                    makeOne(i, j);
                    killDown(i, j);
                    flagedRows->push_back(i);
                }
            }
            else if(flag && j == colSize)
            {
                i = rowSize;
            }
        }
    }

    for(int i = 0; i < rowSize; i++)
    {
        for(int j = 0; j < colSize; j++)
        {
            if(matrix[i][j] == -0)
            {
                matrix[i][j] = 0;
            }
        }
    }
}

//***************************************************************
template <typename T>
void Matrix<T>::rref()
{
    ref();

    for(int i = 0; i < rowSize; i++)
    {
        for(int j = 0; j < colSize; j++)
        {
            if(matrix[i][j] == 1)
            {
                killUp(i, j);
            }
        }
    }
}

//***************************************************************
template <typename T>
void Matrix<T>::trans()
{
    Matrix<T>* temp = new Matrix<T>(colSize, rowSize);

    for(int i = 0; i < colSize; i++)
    {
        for(int j = 0; j < rowSize; j++)
        {
            (*temp)[i][j] = matrix[j][i];
        }
    }

    (*this) = temp;
}

//***************************************************************
template <typename T>
void Matrix<T>::inverse()
{
    T inValue,
        temp;
    Matrix<T>* matrix_;

    if(isSquare())
    {
        inValue = (1/this->det());

        if(rowSize == 2)
        {
            temp = matrix[0][0];
            matrix[0][0] = matrix[1][1];
            matrix[1][1] = temp;
            matrix[0][1] = -(matrix[0][1]);
            matrix[1][0] = -(matrix[1][0]);

            for(int i = 0; i < rowSize; i++)
            {
                for(int j = 0; j < colSize; j++)
                {
                    matrix[i][j] *= inValue;
                }
            }
        }
        else
        {
            matrix_ = new Matrix<T>(rowSize, 2(colSize));

            for(int i = 0; i < rowSize; i++)
            {
                (*matrix_)[i][i] = 1;
            }
        }
    }
}

//***************************************************************
template <typename T>
void Matrix<T>::adj()
{

}

//***************************************************************
// functions needed to perform matrix operations                *
//***************************************************************
template <typename T>
bool Matrix<T>::isSquare()
{
    bool isSquare = false;

    if(rowSize == colSize)
    {
        isSquare = true;
    }

    return isSquare;
}

//***************************************************************
template <typename T>
int Matrix<T>::findNonZeroEle(int col)
{
    int retRow = -1;
    std::vector<int>::iterator iter;

    for(int i = 0; i < rowSize; i++)
    {
        if(matrix[i][col] != 0)
        {
            iter = find(flagedRows->begin(), flagedRows->end(), i);

            if(iter == flagedRows->end())
            {
                retRow = i;
                i = rowSize;
            }
        }
    }

    return retRow;
}

//***************************************************************
template <typename T>
void Matrix<T>::swapRows(int row1, int row2)
{
    std::vector<T> temp(colSize);

    for(int i = 0; i < colSize; i++)
    {
        temp[i] = matrix[row1][i];
        matrix[row1][i] = matrix[row2][i];
        matrix[row2][i] = temp[i];
    }
}

//***************************************************************
template <typename T>
void Matrix<T>::makeOne(int row, int col)
{
    double oneValue = (1 / (double)matrix[row][col]);

    for(int i = 0; i < colSize; i++)
    {
        matrix[row][i] *= oneValue;
    }
}

//***************************************************************
template <typename T>
void Matrix<T>::killDown(int startRow, int col)
{
    std::vector<T> temp(colSize);
    T killValue;

    for(int i = startRow + 1; i < rowSize; i++)
    {
        killValue = -(matrix[i][col]);

        for(int j = 0; j < colSize; j++)
        {
            temp[j] = killValue*(matrix[startRow][j]);
            matrix[i][j] += temp[j];
        }
    }
}

//***************************************************************
template <typename T>
void Matrix<T>::killUp(int startRow, int col)
{
    std::vector<T> temp(colSize);
    T killValue;

    for(int i = startRow - 1; i >= 0; i--)
    {
        killValue = -(matrix[i][col]);

        for(int j = 0; j < colSize; j++)
        {
            temp[j] = killValue*(matrix[startRow][j]);
            matrix[i][j] += temp[j];
        }
    }
}

//***************************************************************
// private setters                                              *
//***************************************************************
template <typename T>
void Matrix<T>::setRowSize(int row)
{
    rowSize = row;
}

//***************************************************************
template <typename T>
void Matrix<T>::setColSize(int col)
{
    colSize = col;
}

#endif // MATRIX_H
