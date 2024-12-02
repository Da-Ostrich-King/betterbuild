#include "../include/ConfigManager.hpp"
#include "../include/Helper.hpp"

#include <iostream>
#include <unistd.h>
char const * helpText = 
    "Name\n"
    "   BetterBuild\n"
    "Usage\n"
    "   bbuild {configname | \"default\"}\n"
    "Options\n"
    "   -h, --help  Display this help text\n"
    "Examples\n"
    "   bbuild /* runs the \"default\" config, commonly builds with default options */"
    "   bbuild install /* runs the \"install\" config, commonly used to install built executables to the system */"
    "   bbuild menuconfig /* runs the \"menuconfig\" config, commonly used to do build options*/";


int main( int argc, char **argv, char **envv ) {
    helper::CmdlineArgs args = helper::parseArgs( argc, argv ); // parse command line args
    char doBuild;
    if ( !args.noCheck ) {
        std::cout << "This can run arbitrary commands, read the BuildFile and ensure it isn't doing anything malicous. Are you sure you want to continue? (Y, n): ";
        std::cin.get( doBuild );        
    } else {
        doBuild = 'y'; // assume yes if noCheck is true
    }
    
    if ( doBuild == '\n' || doBuild == 'y' ) {
        if ( args.config.find( std::string( "install" ) ) == std::string::npos ) {
            if ( geteuid() != 0 ) {
                std::cout << "Must not be ran as root unless running a config with the substring \"install\"\n";
                exit( 1 );
            }
        }

        ConfigManager configMgr( args.file ); // tokenize config and create object

#ifdef debug
        if ( !args.dryRun ) {
#endif // do stuff that does stuff here
        helper::build( configMgr.getConfiguration( args.config ) ); // start build process, given tokenized non-parsed data.
#ifdef debug
        }
#endif
        return 0;
    } else {
        std::cout << "Not building\n";
        return 1;
    }

}