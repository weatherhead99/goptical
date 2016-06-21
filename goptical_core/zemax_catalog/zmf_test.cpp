#include "zemax_zmf.hh"
#include <iostream>
#include <string>
#include <unistd.h>

using std::string;
using std::cout;
using std::endl;

const string thorlabs_test_file="THORLABS.ZMF";


int main(int argc, char** argv)
{
  zmfreader reader(thorlabs_test_file.c_str());
  
  cout << "ZMF file version: " << reader.getVersion() << endl;
  
};
  