#include <string> 
#include <vector>

namespace RLE {

  std::string stringMul(int num, char caracter)
  {
    std::string res = "";
    for(int i = 0; i < num; i++)
      res += caracter;
    return res; 
  }
  int sum(std::vector<int> arr)
  {
    int result = 0; 
    for(int i = 0; i < arr.size(); i++)
      result += arr[i];
    return result; 
  }
  std::string bin(int n)
  {
    std::string r = "";
    while (n != 0){
      r = ( n % 2 == 0 ? "0" : "1" ) + r;
      n /= 2;
    }
    return r;
  }
  int peso(std::vector<int> arr)
  {
    return bin(arr[0]).length() * arr.size();
  }
  int pesoOriginal(std::vector<std::string> arr)
  {
    return arr.size() * arr[0].length() + bin(arr[0].length()).length();
  }
  int bitMaprows(std::vector<int> arr)
  {
    int j = 0; 
    std::vector<int> aux; 
    for(int i = 0; i < arr.size(); i++)
    {
      if(sum(aux) == arr[0])
      {
        aux = std::vector<int>();
        j++;
      }
      aux.push_back(arr[i]);
    }
    return j;
  }
  int cerosRle(std::vector<int> arr)
  {
    std::vector<int> arr1;
    std::vector<std::vector<int>> arr2; 
    for(int i = 1; i < arr.size(); i++)
    {
      arr1.push_back(arr[i]);
      if(sum(arr1) == arr[0])
      {
        arr2.push_back(arr1);
        arr1 = std::vector<int>(); 
      }
    }
    int par = 1;
    std::vector<std::string> arr3;
    std::vector<std::vector<std::string>> arr4;
    for(int i = 0; i < arr2.size(); i++)
    {
      for(int j = 0; j < arr2[i].size(); j++)
      {
        if(arr2[i][j] != 0)
        {
          if(par%2 == 0)
            arr3.push_back(stringMul(arr2[i][j], 'x'));
          else
            arr3.push_back(stringMul(arr2[i][j], 'y')); 
        }
        par++;
      }
      arr4.push_back(arr3);
      arr3 = std::vector<std::string>();
      par = 1; 
    }
    par = 0;
    for(int i = 0; i < arr4.size(); i++)
    {
      for(int j = 0; j < arr4[i].size(); j++)
      {
        for(int k = 0; k < arr4[i][j].length(); k++)
        {
          if(arr4[i][j][k] == 'y')
          {
            par++;
          }
        }
      }
    }
    return par;
  } 
  std::vector<int> auxEndode(std::string str)
  {
    int n = str.length();
    std::vector<int> arr;
    for (int i = 0; i < n; i++) 
    {
        int count = 1;
        while (i < n - 1 && str[i] == str[i + 1]) {
            count++;
            i++;
        }
        arr.push_back(count);
    }
    return arr;
  }

  std::vector<int> encodeRLE(std::vector<std::string> arr)
  {
    std::vector<int> arr2 = { (int)arr[0].length() }; 
    for(int i = 0; i < arr.size(); i++)
    {
      if(arr[i][0] == 'X')
        arr2.push_back(0);
      std::vector<int> aux = auxEndode(arr[i]);
      for(int j = 0; j < aux.size(); j++)
      {
        arr2.push_back(aux[j]);
      }
      aux = std::vector<int>();
    }
    return arr2;
  }
}