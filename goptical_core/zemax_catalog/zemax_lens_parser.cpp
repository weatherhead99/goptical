#include "zemax_lens_parser.hh"


void parsed_zemax_lens::setName(const char* name)
{
  _name  = std::string(name);

}


void parsed_zemax_lens::setVersion(int vers)
{
  _version = vers;

}



string parsed_zemax_lens::getName() const
{
  return _name;

}


int parsed_zemax_lens::getVersion() const
{
  return _version

}
