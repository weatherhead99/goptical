#include "zemax_zmf.hh"

#include <iostream>
#include <fstream>

#include <cmath>
#include <vector>
using std::vector;

using std::cout;
using std::endl;

zmfreader::zmfreader(const char* fname)
{
  
  std::ifstream ifs(fname, std::ios::binary);
  
  unsigned version;
  ifs.read(reinterpret_cast<char*>(&version),4);
  cout << "version: " << version << endl;
  

}


std::string zmf_description_deobfuscate(const std::string& raw_desc, double efl, double enp)
{
    auto iv = cos(6 * efl + 3 * enp);
    iv = cos(655 * M_PI / 180. * iv) + iv;
    
    
    auto char_iter = raw_desc.begin();
    std::string out;
    
    int i=0;
    for(char c : raw_desc)
    {
      double k = 13.2 * ( iv + sin ( 17 * (i+3))) * (i++ + 1);
      out += c ^ decimal_expansion_digits(k,4,7);
      
    };
  
    return out;
    

}

int decimal_expansion_digits(float val, int id1, int id2)
{
  int places = ceil(log10(val));
  val /= pow(10,places);
  
  auto k = val* pow(10,id1 - 1);
  
  double ipart;
  auto f = modf(k,&ipart);
  
  modf(f * pow(10,id2 - id1), &ipart);
  
  return ipart;
  
}


int end_swap(int i)
{
  unsigned char b1, b2, b3, b4;

  b1 = i & 255;
  b2 = ( i >> 8 ) & 255;
  b3 = ( i>>16 ) & 255;
  b4 = ( i>>24 ) & 255;

  return ((int)b1 << 24) + ((int)b2 << 16) + ((int)b3 << 8) + b4;
}

