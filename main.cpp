#include "aritmetic.hpp"
#include "RLE.hpp"
#include "Huffman.hpp"
#include <time.h>


int main() 
{    
  clock_t begin1 = clock();
  std::vector<std::tuple<char, std::string>> arr = huffman::HuffmanCodes("GAGAGCCGCACGAGTCGT");
  clock_t end1 = clock();
  double time_spent = 0.0;
  time_spent += (double)(end1 - begin1) / CLOCKS_PER_SEC;
  for(int i = 0; i < arr.size(); i++)
    std::cout<<std::get<0>(arr[i]) <<" "<<std::get<1>(arr[i]) <<"\n";
	printf("\nClock: %f\n", time_spent);
  return 0;  
}