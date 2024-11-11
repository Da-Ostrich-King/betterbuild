#include "../include/Config.hpp"

Config::Config() {
    return;
}
Config::~Config() {
    return;
}

void Config::addBinary( Binary bin ) {
    bins.push_back( bin );
}

const Binary Config::getBinary( int index ) {
    return bins[ index ];
}



Binary::Binary( std::string name, std::string CC, std::vector< std::string > args, std::vector< std::string > srcs) 
: sources(srcs),
  CC(CC),
  name(name),
  args(args) {}

Binary::~Binary() {
    return;
}
