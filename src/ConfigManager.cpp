#include "../include/ConfigManager.hpp"

#include <csignal>
#include <iostream>
#include <fstream>
#include <string>

ConfigManager::ConfigManager( std::string file_path ) {
    std::ifstream file;
    file.open( file_path );

    if ( !file.is_open() ) {
        std::cerr << "Build file not found, make one or specify at command line" << std::endl;
        exit( 1 );
    }

    std::string tmp;

    while ( std::getline( file,  tmp ) ) {
        fileBuffer += tmp += "\n";
    }
    file.close();



    fileBuffer += "\n";

    // Parse the file into rawConfigValues

    ConfigValue configBuff;

    std::string wordBuff;
    for ( char ch : fileBuffer ) {
        if ( ch == '\n' ) {
            rawConfigValues.push_back( configBuff );
            configBuff = {};
            wordBuff = "";
        } else if ( ch == ' ' ) {
            if ( configBuff.first == "" ) {
                configBuff.first = wordBuff;
            } else {
                configBuff.second.push_back( wordBuff );
            }
            wordBuff = "";
        } else {
            wordBuff += ch;
        }
    }

    std::vector< ConfigValue > configBuffVec;
    for ( auto searchForConfig : rawConfigValues ) {
        if ( searchForConfig.first == "config" ) {
            configurations[ configBuffVec[ 0 ].second[ 0 ] ] = configBuffVec;
            configBuffVec = {};
        }
        configBuffVec.push_back( searchForConfig );
    }

#ifdef debug
    // debugging shit
    for ( ConfigValue cfgval : rawConfigValues) {
        std::cout << cfgval.first << " ";
        for (std::string arg : cfgval.second) {
            std::cout << arg << " ";
        }
        std::cout << "\n";
    }
#endif

}

const std::vector< ConfigValue > ConfigManager::getConfiguration( std::string configName) {
    return configurations[ configName ];
}