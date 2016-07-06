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
  
  
  while(!ifs.eof())
  {
//     cout << "position: "<< ifs.tellg() << endl;
    zemax_lens l(ifs);
    
//     cout << "lens read: " << l.name << endl;
    _lenses.push_back(std::move(l));
    
  }
  
    
}

unsigned int zmfreader::getVersion() const
{
  return _version;
}

const vector< zemax_lens >& zmfreader::getLenses() const
{
  return _lenses;

}





std::string zmf_description_deobfuscate(const std::string& raw_desc, double efl, double enp)
{
    auto iv = cos(6 * efl + 3 * enp);
    iv = cos(655 * M_PI / 180. * iv) + iv;
    
    auto char_iter = raw_desc.begin();
    std::string out;
    
    int i=0;
    for(unsigned char c : raw_desc)
    {
      double k = 13.2 * ( iv + sin ( 17 * (i+3))) * (i++ + 1);
      out += (char) (c ^ decimal_expansion_digits(k,4,7));
      
    };
  
    return out;
    

}

unsigned char decimal_expansion_digits(double val, int id1, int id2)
{
  
//   cout << "raw val: " << val << endl;
  int places = ceil(log10(abs(val)));
  val /= pow(10,places);
  
//   cout << "val: " << val << endl;
  
  auto k = val* pow(10,id1 - 1);
  
  double ipart;
  auto f = modf(k,&ipart);
  
  modf(f * pow(10,id2 - id1), &ipart);
  
  
  return floor(ipart);
  
}

zemax_lens::zemax_lens(std::istream& is)
{
    
    //check valid description
    
      read_from_stream(is);
    
    
}


void zemax_lens::print_summary() const
{
  cout << "name: " << name << " elements: " << elements << " desclen: " << lr.desclen << endl;
  
}



zemax_lens::zemax_lens()
{

}


void zemax_lens::read_from_stream(std::istream& is)
{
      is.read(reinterpret_cast<char*>(&lr),sizeof(lr));
    
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
    std::string raw_desc;
    raw_desc.resize(lr.desclen);
    std::copy_n(std::istreambuf_iterator<char>(is),lr.desclen+1,raw_desc.begin());
    
    if(raw_desc.size() != lr.desclen)
    {
      throw std::logic_error("description size mismatch");
    };
    
    description = zmf_description_deobfuscate(std::string(raw_desc), efl, enp);


}




