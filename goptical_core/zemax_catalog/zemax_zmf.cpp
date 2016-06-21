#include "zemax_zmf.hh"

#include <iostream>
#include <fstream>
#include <stdexcept>
#include <cmath>
#include <vector>
#include <iomanip>


#include <algorithm>

#include <Goptical/Error>

using namespace Goptical;
using std::vector;

using std::cout;
using std::endl;

zmfreader::zmfreader(const char* fname)
{
  
  std::ifstream ifs(fname, std::ios::binary);

  if(!ifs.is_open())
  {
    throw Error("couldn't open ZMF file");
  };

 read_from_stream(ifs,_version);
  
  

  if(_version != 1001)
  {
    throw std::logic_error("goptical does not support this ZMF version");
  };
  
  zemax_lens lens(ifs);
  
  cout << "name: " << lens.name << endl;
  
  

}

unsigned int zmfreader::getVersion() const
{
  return _version;
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

zemax_lens::zemax_lens(std::istream& is)
{
    _zemax_lens_raw lr;
    is.read(reinterpret_cast<char*>(&lr),sizeof(_zemax_lens_raw));
    
    name = std::string(lr.name);
    name.erase(std::find_if(name.rbegin(), name.rend(), std::not1(std::ptr_fun<int, int>(std::isspace))).base(), name.end());
    
    elements = lr.elements;
    version = lr.version;
    shp = lr.shp;
    aspheric = lr.aspheric;
    toroidal = lr.toroidal;
    grin = lr.grin;
    efl = lr.efl;
    enp = lr.enp;
    
    
    //read description
    cout << "desclen: " << lr.desclen << endl;
    std::string raw_desc;
    raw_desc.resize(lr.desclen);
    std::copy_n(std::istreambuf_iterator<char>(is),lr.desclen,raw_desc.begin());
    
    description = zmf_description_deobfuscate(std::string(raw_desc), efl, enp);
    
    cout << "description: " << description << endl;
    
    
}

zemax_lens::zemax_lens()
{

}





