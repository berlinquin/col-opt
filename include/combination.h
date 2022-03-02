#include <vector>

// This namespace holds different implementations of java-style iterators
// to generate all combinations for "n-choose-k"
namespace combination_generator
{
   // Return a std::vector from next(),
   // based on a simple O(K^2) algorithm
   class simple_vector;

   // Return a pointer from next(),
   // based on a simple O(K^2) algorithm
   class simple_pointer;

   // Return a std::vector from next(),
   // implemented with a single-pass O(K) algorithm
   class single_pass;

   // Return a pointer from next(),
   // where the O(K^2) algorithm is optimized with a double buffer
   class ping_pong;



   class simple_vector
   {
      public:
         // Construct a generator for all combinations in "n-choose-k"
         simple_vector(int n, int k);

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



   class simple_pointer
   {
      public:
         // Construct a generator for all combinations in "n-choose-k"
         simple_pointer(int n, int k);

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



   class single_pass
   {
      public:
         // Construct a generator for all combinations in "n-choose-k"
         single_pass(int n, int k);

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



   class ping_pong
   {
      public:
         // Construct a generator for all combinations in "n-choose-k"
         ping_pong(int n, int k);

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

}
