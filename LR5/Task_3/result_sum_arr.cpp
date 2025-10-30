#include <iostream>
#include "result_sum_arr.h"
using namespace std;

#define BRED "\033[91m"
#define GREEN "\033[32m"
#define BBLUE "\033[94m"
#define RESET "\033[0m"
#define BYELLOW "\033[93m"


int count_el(int **array, int a, int b)
{
   int count = 0;
   for (int i = 0; i < a; i++)
   {
      for(int j = 0; j < b; j++)
      {
         if (i == j and array[i][j]%2 == 0) 
         {
            count++;
         }         

      }
   }
   
  return count;
}


void diag(int *array1, int a, int **array2, int b, int c)
{
   int k = 0;
   for (int i = 0; i < b; i++)
   {
      for(int j = 0; j < c; j++)
      {
         if (i == j and array2[i][j]%2 == 0) 
         {
           if (k<a)
            {
               array1[k] = array2[i][j];
               k++;
            }
         }         

      }
   }
   
   cout << GREEN << "Элементы диагонали: " << RESET;

   for(int i = 0; i < k; i++)
   {
      cout << array1[i] << " ";
   }

   return;
}

int product(int *array, int a)
{
   int result = 1;
   for(int i = 0; i < a; i ++) result *= array[i];
   return result;
}