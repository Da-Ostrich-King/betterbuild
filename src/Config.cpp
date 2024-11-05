#include "../include/Config.hpp"

#include <fstream>
#include <string>

Config::Config( std::string file_path ) {
    std::fstream file;
    file.open( file_path);
}

const std::vector< ConfigValue > Config::getConfiguration( std::string configName) {
    return configurations[ configName ];
}