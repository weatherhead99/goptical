#include "zemax_zmf.hh"
#include <iostream>
#include <string>
#include <unistd.h>
#include <cmath>

using std::string;
using std::cout;
using std::endl;

const string thorlabs_test_file="THORLABS.ZMF";


int main(int argc, char** argv)
{
  zmfreader reader(thorlabs_test_file.c_str());
  
  cout << "pi dec exp: " << (unsigned) decimal_expansion_digits(M_PI,4,7) << " ";
  
  cout << "ZMF file version: " << reader.getVersion() << endl;
  
  //auto lenses = reader.getLenses();
  
  //print out rawdesc ords
  for(int i=0 ;i < 2; i++)
  {
    reader.getLens();
    
  };
  
  //this is the one we want
  cout << "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@" << endl;
  auto l = reader.getLens();
  
  
  cout << l.description << endl;
  
//   for (auto c : l.description)
//   {
//     cout << static_cast<unsigned> (c) << ", ";
//     
//   };
  
   
};
  