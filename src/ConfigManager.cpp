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
        if (tmp == "") continue;
        fileBuffer += tmp; fileBuffer += "\n";
    }
    file.close();



    // fileBuffer += "\n";

    // Parse the file into rawConfigValues

    ConfigKey configBuff;

    std::string wordBuff;
    bool isComment;
    for ( char ch : fileBuffer ) {
        if ( isComment ) {
            if ( ch == '\n' ) {
                isComment = false;
            }
            continue;
        }
        if ( ch == '#' ) {
            isComment = true;
            configBuff.second.push_back( wordBuff );
            rawConfigValues.push_back( configBuff );
            configBuff = {};
            wordBuff = "";
            continue;
        } else if ( ch == '\n' ) {
            configBuff.second.push_back(wordBuff);
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


    std::vector< ConfigKey > configVecBuff;
    for (ConfigKey cfgval : rawConfigValues) {
        configVecBuff.push_back(cfgval);
        if (cfgval.first == "config") {
            configurations[ cfgval.second[ 0 ] ] = configVecBuff;
        }
    }


#ifdef debug
    // debugging shit
    for ( ConfigKey cfgval : rawConfigValues) {
        std::cout << cfgval.first << " ";
        for (std::string arg : cfgval.second) {
            std::cout << arg << " ";
        }
        std::cout << "\n";
    }
#endif

}

const std::vector< ConfigKey > ConfigManager::getConfiguration( std::string configName) {
    return configurations[ configName ];
}