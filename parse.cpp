#include <boost/spirit/include/qi.hpp>
#include <boost/fusion/include/std_pair.hpp>

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <iostream>
#include "parse.h"

namespace qi = boost::spirit::qi;

template <typename Iterator>
struct keys_and_values : qi::grammar<Iterator, std::map<std::string, std::string>()>
{
    keys_and_values() : keys_and_values::base_type(query)
    {
        query =  pair >> *(qi::lit(':') >> pair);
        pair  =  key >> -('=' >> value);
        key   =  +qi::char_("a-zA-Z");
        value = +qi::char_("a-zA-Z0-9");
    }
    qi::rule<Iterator, std::map<std::string, std::string>()> query;
    qi::rule<Iterator, std::pair<std::string, std::string>()> pair;
    qi::rule<Iterator, std::string()> key, value;
};

bool parse(Request &request, char *buf) {
    string input(buf);
    string::iterator begin = input.begin();
    string::iterator end = input.end();

    keys_and_values<string::iterator> i;
    map<string, string> map;
    bool result = qi::parse(begin, end, i, map);

    if (result) {
        request.addQuery(map);
    }
    return result;
}
