#include <queue>
#include <vector> 
#include <iostream>
#include <tuple>
#include <map> 
#include <algorithm>
#include <cmath>

namespace huffman {
  template<class T>
  T sum(std::vector<T> arr)
  {
    T result = 0; 
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

  struct MinHeapNode {
    char data;
    unsigned freq;
    MinHeapNode *left, *right;
    MinHeapNode(char data, unsigned freq) {
        left = right = NULL;
        this->data = data;
        this->freq = freq; 
    }
  };
  struct compare {
    bool operator()(MinHeapNode* l, MinHeapNode* r) {
      return (l->freq > r->freq); 
  }  
};

  void saveCodes(struct MinHeapNode* root, std::string str, std::vector<std::tuple<char, std::string>> &asd) 
  { 
      if (!root) 
          return; 
      if (root->data != '$') {
          asd.push_back(std::tuple<char, std::string>(root->data, str));
      }
      saveCodes(root->left, str + "0", asd); 
      saveCodes(root->right, str + "1", asd); 
  } 
  std::map<char, unsigned> mk_dct(std::vector<char> &keys, std::string str)
  {
    std::map<char, unsigned> dct; 
    for(int i = 0; i < str.length(); i++)
    {
      if(std::count(keys.begin(), keys.end(), str[i]) == 0)
        keys.push_back(str[i]);
      if(dct.count(str[i]) > 0)
        dct[str[i]]++;
      else
        dct[str[i]] = 1;
    }
    return dct;
  }

  std::vector<std::tuple<char, std::string>> HuffmanCodes(std::string str) 
  { 
      struct MinHeapNode *left, *right, *top; 
      std::vector<std::tuple<char, std::string>> asd;
      std::vector<char> data;
      std::priority_queue<MinHeapNode*, std::vector<MinHeapNode*>, compare> minHeap; 
      std::map<char,unsigned> probs = mk_dct(data,str);
      for (int i = 0; i < data.size(); ++i) 
          minHeap.push(new MinHeapNode(data[i], probs[data[i]])); 
      while (minHeap.size() != 1) { 
          left = minHeap.top(); 
          minHeap.pop(); 
          right = minHeap.top(); 
          minHeap.pop(); 
          top = new MinHeapNode('$', left->freq + right->freq); 
          top->left = left; 
          top->right = right; 
          minHeap.push(top); 
      } 
      saveCodes(minHeap.top(), "", asd); 
      return asd; 
  } 
  double Entropy(std::string str)
  {
    std::vector<char> keys;
    std::map<char, unsigned> mapo = mk_dct(keys, str);
    std::vector<int> probs1;
    std::vector<double> probs2; 

    for(int i = 0; i < keys.size(); i++)
      probs1.push_back(mapo[keys[i]]);

    int total = sum(probs1);

    for(int i = 0; i < keys.size(); i++)
    {
      double prob = (double)mapo[keys[i]]/total; 
      probs2.push_back(prob*std::log2(std::pow(prob, -1)));
    }
    return sum(probs2);
  }
/*
  double av_cwlen(std::string str)
  {
    std::vector<std::tuple<char, std::string>> dct = HuffmanCodes(str);
    std::vector<char> keys;
    std::map<char, unsigned> mapo = mk_dct(keys, str);
    std::vector<int> probs1;
    std::vector<double> probs2; 


    for(int i = 0; i < keys.size(); i++)
      probs1.push_back(mapo[keys[i]]);

    int total = sum(probs1);

    for(int i = 0; i < keys.size(); i++)
    {
      double prob = (double)mapo[keys[i]]/total; 
      probs2.push_back(prob*);
    }
    return sum(probs2);
  }
  */
}

/*import numpy as np

def av_cwlen(dct1, dct2):
  return sum([len(dct1[i])*dct2[i] for i in dct1.keys()])

def efficiency(string):
  d=mk_dct(string)
  return Entropy(d.values())/av_cwlen(huffman(d),d)

def Slen(string):
  return len(bin(len(string)-1)[2:]*/
