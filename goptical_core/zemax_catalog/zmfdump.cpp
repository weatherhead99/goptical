#include "zemax_zmf.hh"
#include <string>
#include <iostream>
#include <vector>

#include <boost/program_options.hpp>


using std::string;
using std::vector;
using std::cout;
using std::endl;

namespace po = boost::program_options;


int main(int argc, char** argv)
{
  
  po::options_description desc("dumps the contents of a ZMF file to text");
  po::positional_options_description pdesc;
  
  pdesc.add("infile",-1);
  
  desc.add_options()
    ("help", "show this help message")
    ("infile", po::value<string>(),"input ZMF file")
    ("outfile", po::value<string>(),"output file")
    ;
  
  po::variables_map vm;
  po::store(po::command_line_parser(argc,argv).options(desc).positional(pdesc).run(),vm);
  po::notify(vm);
  
  if(vm.count("help"))
  {
    cout <<"Usage: zmfdump infile [options]" << endl;
    cout << desc << endl;
    return 0;
  };
  
  if(!vm.count("infile"))
  {
    cout << "ERROR: no input file specified" << endl;
    return -1;
  };
  
  auto fname = vm["infile"].as<string>();
  cout << "file: " << fname << endl;
  
  zmfreader reader(fname.c_str());
  
  
  auto lenses = reader.getLenses();
  
  cout << "file version: " << reader.getVersion() << endl;
  cout << "read " << lenses.size() << " lenses" << endl;
  
  
  
  
};