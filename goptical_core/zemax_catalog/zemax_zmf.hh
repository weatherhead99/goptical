#pragma once

#include <string>

enum class lens_shape
{ _, E, B, P, M};


struct zemax_lens
{
  
  std::string name;
  lens_shape shp;
  int elements;
  int aspheric;
  int version;
  int grin;
  int toroidal;
  double efl;
  double enp;
  std::string description;
  
};

class zmfreader 
{
public:
  zmfreader(const char* fname);
  
  
  
  
};


std::string zmf_description_deobfuscate(const std::string& raw_desc, double efl, double enp);

int decimal_expansion_digits(float val, int id1, int id2);
int end_swap(int in);