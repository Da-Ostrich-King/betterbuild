#include "../include/ConfigManager.hpp"
#include "../include/Config.hpp"

#include <filesystem>
#include <iostream>
#include <unistd.h>


struct CmdlineArgs {
    bool help;
    std::string config = "";
    std::string file = "BuildFile";
    std::vector< std::string > configOpts;
    bool noCheck;

#ifdef debug
    // debug options
    bool dryRun = false;
#endif
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
        } else if ( std::string( argv[ arg ] ) == std::string( "--nocheck" ) ) {
            args.noCheck = true;
            
#ifdef debug
        } else if ( std::string( argv[ arg ] ) == std::string( "--dryrun" ) ) {
            args.dryRun = true;
        
#endif

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

int main( int argc, char **argv, char **envv ) {
    CmdlineArgs args = parseArgs( argc, argv ); // parse command line args
    char doBuild;
    if ( !args.noCheck ) {
        std::cout << "This can run arbitrary commands, read the BuildFile and ensure it isn't doing anything malicous. Are you sure you want to continue? (Y, n): ";
        std::cin.get(doBuild);        
    } else {
        doBuild = 'y'; // assume yes if noCheck is true
    }
    
    if ( doBuild == '\n' || doBuild == 'y' ) {
        if ( args.config.find( std::string( "install" ) ) == std::string::npos ) {
            if ( !geteuid() ) {
                std::cout << "Must not be ran as root unless running a config with the substring \"install\"\n";
                exit( 1 );
            }
        }

        ConfigManager configMgr( args.file ); // tokenize config and create object

#ifdef debug
        if ( !args.dryRun ) {
#endif // do stuff that does stuff here
        build( configMgr.getConfiguration( args.config ) ); // start build process, given tokenized non-parsed data.
#ifdef debug
        }
#endif
        return 0;
    } else {
        std::cout << "Not building\n";
        return 1;
    }

}