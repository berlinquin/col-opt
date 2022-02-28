#include "combination.h"
#include <stdexcept>

combination_generator::combination_generator(int _n, int _k)
   : N(_n)
   , K(_k)
{
   // check values for N and K
   if (N < 0 || K < 0 || K > N)
   {
      throw std::domain_error("Bad values for N-choose-K");
   }
   // m_index is a vector of size K
   m_index = std::vector<int>(K);
   for (int i = 0; i < K; i++)
   {
      m_index[i] = i;
   }
}

bool combination_generator::has_next()
{
   return m_index[0] < (N-K+1);
}

std::vector<int> combination_generator::next()
{
   // Make a copy of index
   std::vector<int> to_return = m_index;

   for (int i = K-1; i >= 0; i--)
   {
      m_index[i]++;
      if (m_index[i] <= (N-K+i))
      {
         // i is good, now update all later indices
         for (int j = i+1; j < K; j++)
         {
            m_index[j] = m_index[j-1]+1;
         }
         break;
      }
   }

   return to_return;
}

// SECOND GENERATOR

combination_generator2::combination_generator2(int _n, int _k)
   : N(_n)
   , K(_k)
{
   // check values for N and K
   if (N < 1 || K < 1 || K > N)
   {
      throw std::domain_error("Bad values for N-choose-K");
   }
   if (K == 1)
   {
      m_index = std::vector<int> { 0 };
   }
   else if (K == 2)
   {
      m_index = std::vector<int> { 0, 1 };
   }
   else
   {
      // m_index is a vector of size K
      m_index = std::vector<int>(K);
      // Initialize m_index with the starting values
      for (int i = 0; i < K; i++)
      {
         m_index[i] = i;
      }

      // for 6_C_3, max_indices holds [3,4,5]
      m_max_indices = std::vector<int>(K);
      const int base_index = N-K;
      for (int i = 0; i < K; i++)
      {
         m_max_indices[i] = base_index+i;
      }
      printf("m_max_indices: [");
      for (int i : m_max_indices)
      {
         printf("%d ", i);
      }
      printf("]\n");

      // m_max[i] holds the cumulative max of indices
      //   in range [i, N)
      m_max = std::vector<int>(K-1);
      int max_index = N-1;
      m_max[K-2] = max_index;
      // for 6_C_3, m_max holds [9,5]
      for (int i = K-3; i >= 0; i--)
      {
         --max_index;
         m_max[i] = m_max[i+1] + max_index;
      }
      printf("m_max: [");
      for (int i : m_max)
      {
         printf("%d ", i);
      }
      printf("]\n");

      // initialize m_sum
      m_sum = std::vector<int>(K-1);
   }
}

bool combination_generator2::has_next()
{
   return m_index[0] < (N-K+1);
}

std::vector<int> combination_generator2::next()
{
   // Make a copy of index
   std::vector<int> to_return = m_index;

   if (K == 1)
   {
      ++m_index[0];
   }
   else if (K == 2)
   {
      // increment i
      m_index[0] += (m_index[1] == N-1);
      // increment j
      ++m_index[1];
      if (m_index[1] == N)
      {
         m_index[1] = m_index[0] + 1;
      }
   }
   else
   {
      // increment i
      m_index[0] += (m_sum[0] == m_max[0]);
      // increment j
      for (int i = 1; i < K-1; i++)
      {
         m_index[i] += (m_sum[i] == m_max[i]);
         if (m_index[i] > m_max_indices[i])
         {
            m_index[i] = m_index[i-1] + 1;
         }
      }
      // increment last index
      ++m_index[K-1];
      if (m_index[K-1] == N)
      {
         m_index[K-1] = m_index[K-2] + 1;
      }
      // Invariant: For i in range [0, K-1),
      //            m_sum[i] = SUM(j=i+1, j<K, m_index[j])
      m_sum[K-2] = m_index[K-1];
      for (int i = K-3; i >= 0; i--)
      {
         m_sum[i] = m_sum[i+1] + m_index[i+1];
      }
   }
   return to_return;
}
