#pragma once

#include <string>
#include <map>
#include <vector>

typedef std::pair< std::string, std::vector< std::string > > ConfigKey;
//                     ^ keyword    ^ arguments  ^ argument 

class ConfigManager {
public:
    ConfigManager( std::string file_path );

    // returns by value
    const std::vector< ConfigKey > getConfiguration( std::string configName );

private:
    // i hate this
    // anyway, vector of pairs, each pair has a string (config keyword), and a vector of strings (keyword arguments)

    std::string fileBuffer;

    std::vector< ConfigKey > rawConfigValues;

    std::map< std::string, std::vector< ConfigKey > > configurations;
};

