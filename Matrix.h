struct Matrix
{
   int rows;
   int cols;
   int **matrix;

   // Default constructor
   Matrix();

   // Destructor
   ~Matrix();

   // Prevent copying and assignment
   Matrix(const Matrix &) = delete;
   Matrix& operator=(const Matrix&) = delete;

   // Allow move constructors and assignment
   Matrix(Matrix&&);
   Matrix& operator=(Matrix&&);
};
