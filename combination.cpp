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

