#include "../include/ConfigManager.hpp"
#include "../include/Config.hpp"

#include <filesystem>
#include <iostream>


struct CmdlineArgs {
    bool help;
    std::string config = "";
    std::string file = "BuildFile";
    std::vector< std::string > configOpts;
};

CmdlineArgs parseArgs( int argc, char **argv ) {
    CmdlineArgs args;
    for ( int arg; arg < argc; ++arg ) {
        if ( std::string( argv[ arg ] ) == std::string( "--help" ) || 
             std::string( argv[ arg ] ) == std::string( "-h" )) {
            args.help = true;

        } else if ( std::string( argv[ arg ] ) == std::string( "--file" ) ||
                    std::string ( argv[ arg ] ) == std::string( "-f" ) ) {
            args.file = std::string( argv[ ++arg ] );

        } else {
            if ( args.config != "" ) {
                args.configOpts.emplace_back( argv[ arg ] );
            }
            args.config = std::string( argv[ arg ] );
        }
    }


    return args;
}



void build( std::vector< ConfigValue > config /* not parsed yet */) { // config at this point is only tokenized, not parsed

}

int main( int argc, char **argv ) {
    CmdlineArgs args = parseArgs( argc, argv ); // parse command line args
    ConfigManager configMgr( args.file ); // tokenize config and create object
    build( configMgr.getConfiguration( args.config ) ); // start build process, given tokenized non-parsed data.
    return 0;
}