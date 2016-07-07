#include "zemax_zmf.hh"
#include <string>
#include <iostream>
#include <vector>
#include <locale>

#include <fstream>

#include <boost/program_options.hpp>
#include <boost/filesystem.hpp>

using std::string;
using std::vector;
using std::cout;
using std::endl;

namespace po = boost::program_options;


int main(int argc, char** argv)
{
  
  po::options_description desc("dumps the contents of a ZMF file to text");
  po::positional_options_description pdesc;
  
  pdesc.add("infile",1);
  pdesc.add("outfile",1);
  
  desc.add_options()
    ("help", "show this help message")
    ("infile", po::value<string>(),"input ZMF file")
    ("outfile", po::value<string>(),"output file")
    ("force,f", po::bool_switch()->default_value(false),"force overwrite of output file")
    ;
  
  po::variables_map vm;
  po::store(po::command_line_parser(argc,argv).options(desc).positional(pdesc).run(),vm);
  po::notify(vm);
  
  if(vm.count("help"))
  {
    cout <<"Usage: zmfdump infile outfile [options]" << endl;
    cout << desc << endl;
    return 0;
  };
  
  if(!vm.count("infile"))
  {
    cout << "ERROR: no input file specified" << endl;
    return -1;
  };
  
  if(!vm.count("outfile"))
  {
    cout << "ERROR: no output file specified" << endl;
    return -1;
  };
  
  auto fname = vm["infile"].as<string>();
  auto outfname = vm["outfile"].as<string>();
  cout << "ZMF file: " << fname << endl;
  
  //check if output file exists
  cout << "output file: " << outfname << endl;
  
  if(boost::filesystem::exists(outfname))
  {
    if(!vm["force"].as<bool>())
    {
      cout <<"ERROR: File exists (specify -f to overwrite)" << endl;
      return -1;
    }
    else
    {
      cout << "overwriting " << outfname << endl;
      boost::system::error_code errc;
      boost::filesystem::remove(outfname,errc);
      
      if(errc)
      {
	cout << errc << endl;
	return -1;
      };
      
    }
  }
  
  zmfreader reader(fname.c_str());
  
  
  auto lenses = reader.getLenses();
  
  
  cout << "file version: " << reader.getVersion() << endl;
  cout << "read " << lenses.size() << " lenses" << endl;
  
  
  std::ofstream ofs(outfname);

  if(!ofs.is_open())
  {
    cout << "ERROR: couldn't open output file" << endl;
  }
  
  for( const auto& l : lenses)
  {
    ofs << l.description << endl;
  };
  
  cout << "written to " << outfname << endl;
  
};