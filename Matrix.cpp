#include "Matrix.h"

Matrix::Matrix()
   : rows(0)
   , cols(0)
   , matrix(nullptr)
{}

Matrix::~Matrix()
{
   delete matrix;
}

Matrix::Matrix(Matrix &&other)
{
   // Do a member-wise copy from other
   rows = other.rows;
   cols = other.cols;
   matrix = other.matrix;
   // Zero out the pointer in the moved-from object
   other.matrix = nullptr;
}

Matrix& Matrix::operator=(Matrix&& other)
{
   // Do a member-wise copy from other
   rows = other.rows;
   cols = other.cols;
   matrix = other.matrix;
   // Zero out the pointer in the moved-from object
   other.matrix = nullptr;
   return *this;
}
