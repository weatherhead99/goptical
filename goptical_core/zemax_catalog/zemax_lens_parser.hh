#pragma once


#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix_core.hpp>
#include <boost/spirit/include/phoenix_operator.hpp>
#include <boost/fusion/include/adapt_struct.hpp>
#include <stdexcept>

#include <iostream>

#include <functional>
#include <tuple>
#include <string>

#include <vector>

//TODO: surface parser needs to detect indentation
//TODO: multiline note parser


using std::string;
using std::vector;

using std::cout;
using std::endl;

namespace qi = boost::spirit::qi;
namespace ascii = boost::spirit::ascii;
namespace phoenix = boost::phoenix;


struct parsed_zemax_lens
{
  unsigned version;
  unsigned lang;
  string mode;
  string name;
  
  double enpd;
  
};


BOOST_FUSION_ADAPT_STRUCT(
  parsed_zemax_lens,
 (unsigned, version) 
 (unsigned, lang)
 (string, mode)
 (string,name)
 (double, enpd) 
 
)

template<typename It,typename Skipper = ascii::space_type> struct
LensParser : qi::grammar<It, parsed_zemax_lens(),Skipper>
{
  
  LensParser() : LensParser::base_type(lens_parse_rule)
  {
    version_parse_rule %= qi::lit("VERS") >> qi::uint_ ;
    mode_parse_rule %= qi::lit("MODE") >> qi::lexeme[ +(qi::alnum) ] ;
    
    long_name_parse_rule %= qi::lit("NAME") >> qi::lexeme[ +(qi::char_ - qi::cntrl) ]  ;
    
    lang_parse_rule %= qi::lit("LANG") >> qi::uint_;
    
    enpd_parse_rule %= qi::lit("ENPD") >> qi::double_;
    
    lens_parse_rule =   version_parse_rule  ^ lang_parse_rule ^  mode_parse_rule ^  long_name_parse_rule  ^ enpd_parse_rule
		      ;
    
  };
  
private:
  qi::rule<It,unsigned(),ascii::space_type> version_parse_rule;
  qi::rule<It,string(),ascii::space_type> mode_parse_rule;
  qi::rule<It,string(),ascii::space_type> long_name_parse_rule;
  qi::rule<It,unsigned(),ascii::space_type> lang_parse_rule;
  qi::rule<It,double(),ascii::space_type> enpd_parse_rule;
  
  
  
  qi::rule<It, parsed_zemax_lens(), ascii::space_type> lens_parse_rule;
  
};



