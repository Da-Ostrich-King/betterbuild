#include "../include/Config.hpp"

#include <csignal>
#include <iostream>
#include <fstream>
#include <string>

Config::Config( std::string file_path ) {
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
    std::cout << "Parsed config values\n";
    for ( ConfigValue cfgval : rawConfigValues) {
        std::cout << cfgval.first << " ";
        for ( std::string arg : cfgval.second ) {
            std::cout << arg << " ";
        }
        std::cout << "\n";
    }

    std::cout << "Config from config map\n";
    for ( std::pair< std::string, std::vector< ConfigValue > > configVecPair : configurations) {
        for ( ConfigValue configVal : configVecPair.second ) {
            std::cout << configVal.first << " ";
            for ( std::string arg : configVal.second ) {
                std::cout << arg << " ";
            }
            std::cout << "\n";
        }
    }

#endif



}

const std::vector< ConfigValue > Config::getConfiguration( std::string configName ) {
    return configurations[ configName ];
}
