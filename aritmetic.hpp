#include <iostream>
#include <tuple>
#include <vector>
#include <map>


namespace aritmetic {
  bool find(char a, std::vector<char> b)
  {
    if(b.size()==0)
      return false;

    for(int i = 0; i < b.size(); i++)
      if (a == b[i])
        return true; 

    return false; 
  }
  std::map<char, double> creaProbabilities(std::vector<char> &arr, std::string str)
  {
    std::map<char, double> mapo; 
    int size = str.length();
    for(int i = 0; i <size; i++)
    {
      if(!find(str[i], arr))
        arr.push_back(str[i]);
      if(mapo.count(str[i]) >  0)
        mapo[str[i]]++; 
      else
        mapo[str[i]] = 1; 
    }
    for(int i = 0; i < arr.size(); i++)
    {
      mapo[arr[i]] = mapo[arr[i]]/size;
    }
    return mapo;
  }
  std::map<char, std::tuple<double, double>> creaTupla(std::string str)
  {
    std::vector<char> arr;
    std::map<char, double> napo = creaProbabilities(arr, str);
    std::vector<std::tuple<double, double>> tpl; 
    std::map<char, std::tuple<double, double>> napo2; 
    double anterior = 0, probs = 0; 
    for(int i = 0; i < arr.size(); i++)
    {
      probs += napo[arr[i]];
      napo2.emplace(arr[i], std::tuple<double, double>(anterior, probs));
      anterior = probs;
    }
    return napo2;
  }
  std::tuple<double, double> encodeAri(std::string str)
  {
    std::map<char, std::tuple<double, double>> napo = creaTupla(str); 
    double alt = 1; 
    double baix = 0; 
    for(int i = 0; i < str.length(); i++)
    {
        double rang = alt - baix; 
        alt = baix + rang * std::get<1>(napo[str[i]]);
        baix = baix + rang * std::get<0>(napo[str[i]]);
    }
    return std::tuple<double,double>(baix, alt);
  }

  std::vector<std::tuple<double, double>> creaTupla2(std::vector<double> probsL)
  {
    std::vector<std::tuple<double, double>> tpl; 
    double anterior = 0, prob = 0; 
    for(int i = 0; i < probsL.size(); i++)
    {
      prob += probsL[i]; 
      tpl.push_back(std::tuple<double,double>(anterior, prob));
      anterior = prob;
    }
    return tpl;
  }
  std::string decodeAri(double integer, std::vector<char> keys, std::vector<double> prob, int steps)
  {
    while(integer > 1)
    {
      integer = integer/10; 
    }
    std::string aux = ""; 
    double valor = integer, alt = 1, baix = 0; 
    std::vector<std::tuple<double, double>> newL = creaTupla2(prob); 
    for(int i = 0; i < steps; i++)
    {
      valor = (valor - baix)/(alt - baix); 
      for(int j = 0; j < keys.size(); j++)
      {
          if(std::get<0>(newL[j]) <= valor && valor < std::get<1>(newL[j]))
          {
            aux += keys[j];
            alt = std::get<1>(newL[j]); 
            baix = std::get<0>(newL[j]);
            break;
          }
      }
    }
    return aux; 
  }
}
