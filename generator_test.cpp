#include <iostream>
#include <chrono>

#include "combination.h"

template <typename T>
void time_generator(int N, int K)
{
   // Use the std::chrono library for timekeeping
   using clock = std::chrono::steady_clock;

   // Time the generator
   auto start = clock::now();
   int count = 0;
   T cg(N, K);
   while (cg.has_next())
   {
      std::vector<int> c = cg.next();
      /*
      printf("[");
      for (int i : c)
      {
         printf("%d ", i);
      }
      printf("]\n");
      */
      ++count;
   }
   printf("number of combinations: %d\n", count);
   auto end = clock::now();
   std::chrono::duration<double> diff = end - start;
   printf("Took %f seconds to generate\n", diff.count());
}

// Specialize for pointer class
template<>
void time_generator<combination_generator_pointer>(int N, int K)
{
   // Use the std::chrono library for timekeeping
   using clock = std::chrono::steady_clock;

   // Time the generator
   auto start = clock::now();
   int count = 0;
   combination_generator_pointer cg(N, K);
   while (cg.has_next())
   {
      const int *c = cg.next();
      /*
      printf("[");
      for (int i = 0; i < K; i++)
      {
         printf("%d ", c[i]);
      }
      printf("]\n");
      */
      ++count;
   }
   printf("number of combinations: %d\n", count);
   auto end = clock::now();
   std::chrono::duration<double> diff = end - start;
   printf("Took %f seconds to generate\n", diff.count());
}


int main(int argc, char *argv[])
{
   // Pass same args to different generators
   const int N = 30;
   const int K = 10;

   printf("O(N^2) generator\n");
   time_generator<combination_generator>(N, K);

   printf("O(N^2) pointer generator\n");
   time_generator<combination_generator_pointer>(N, K);

   printf("O(N) generator\n");
   time_generator<combination_generator2>(N, K);
   return 0;
}
