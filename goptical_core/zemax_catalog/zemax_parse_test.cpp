#include "zemax_lens_parser.hh"
#include <iostream>
#include <string>

#include "zemax_zmf.hh"



using std::cout;
using std::endl;
using std::string;

int main(int argc, char** argv)
{
  cout << "parse test" << endl;
  
  
  cout << "reading a lens from THORLABS.ZMF" << endl;
  zmfreader reader("THORLABS.ZMF");
  
  auto raw_lens = reader.getLens();
    
    LensParser<string::iterator> parser;
  
    parsed_zemax_lens parsed_lens;
    
     qi::phrase_parse(raw_lens.description.begin(), raw_lens.description.end(), parser, ascii::space, parsed_lens);
     
     
     cout << "version: " << parsed_lens.version << endl;
     cout << "mode: " << parsed_lens.mode << endl;
  
};