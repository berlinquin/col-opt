#include <vector>

// A java-style iterator to generate all combinations
// for "n-choose-k"
class combination_generator
{
public:
   // Construct a generator for all combinations in "n-choose-k"
   combination_generator(int n, int k);

   // Return k values in the range [0, n)
   // to give the indices of the elements in this combination
   std::vector<int> next();

   // True if there is another combination
   bool has_next();

private:
   const int N;
   const int K;
   std::vector<int> m_index;
};



// Return a pointer instead of an object from next()
class combination_generator_pointer
{
public:
   // Construct a generator for all combinations in "n-choose-k"
   combination_generator_pointer(int n, int k);

   // Return k values in the range [0, n)
   // to give the indices of the elements in this combination
   const int* next();

   // True if there is another combination
   bool has_next();

private:
   const int N;
   const int K;
   std::vector<int> m_index;
   std::vector<int> m_to_return;
};



// Use a double buffer
class combination_generator_ping_pong
{
public:
   // Construct a generator for all combinations in "n-choose-k"
   combination_generator_ping_pong(int n, int k);

   // Return k values in the range [0, n)
   // to give the indices of the elements in this combination
   const int* next();

   // True if there is another combination
   bool has_next();

private:
   const int N;
   const int K;
   bool m_return_A;
   std::vector<int> m_index_A;
   std::vector<int> m_index_B;
};



// Run an O(n) instead of O(n2) algorithm in next()
class combination_generator2
{
public:
   // Construct a generator for all combinations in "n-choose-k"
   combination_generator2(int n, int k);

   // Return k values in the range [0, n)
   // to give the indices of the elements in this combination
   std::vector<int> next();

   // True if there is another combination
   bool has_next();

private:
   const int N;
   const int K;
   std::vector<int> m_index;
   std::vector<int> m_max_indices;
   std::vector<int> m_max;
   
   // Invariant: for i in range [0, K-1),
   // m_sum[i] = SUM(k=0, k<i, m_index[k])
   std::vector<int> m_sum;
};
