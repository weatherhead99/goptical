#pragma once

#include <string>
#include <vector>
using std::vector;

enum class lens_shape
{ _, E, B, P, M};

#pragma pack(push,1)
struct _zemax_lens_raw
{
  char name[100];
  int version;
  int elements;
  lens_shape shp;
  int aspheric;
  int grin;
  int toroidal;
  unsigned desclen;
  double efl;
  double enp;
  
};
#pragma pack(pop)
  

struct zemax_lens
{
  zemax_lens(std::istream& is);
  zemax_lens();
  
  void read_from_stream(std::istream& is);
  
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
  
  void print_summary() const;
  
private:
  _zemax_lens_raw lr;
  
};


class zmfreader 
{
public:
  zmfreader(const char* fname);
  unsigned getVersion() const;
  
  const vector<zemax_lens>& getLenses() const;
  
private:
  
  vector<zemax_lens> _lenses;
  unsigned _version;
  
};


std::string zmf_description_deobfuscate(const std::string& raw_desc, double efl, double enp);

unsigned char decimal_expansion_digits(double val, int id1, int id2);

template <typename T> T end_swap(T i)
{
  unsigned char b1, b2, b3, b4;
  
  b1 = i & 255;
  b2 = ( i >> 8 ) & 255;
  b3 = ( i>>16 ) & 255;
  b4 = ( i>>24 ) & 255;
  
  return ((int)b1 << 24) + ((int)b2 << 16) + ((int)b3 << 8) + b4;
  
  
}


template <typename T, typename strm> inline void read_from_stream(strm& is, T& var)
{
  is.read(reinterpret_cast<char*>(&var),sizeof(decltype(var))); 
};

