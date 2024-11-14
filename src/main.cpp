#include "../include/ConfigManager.hpp"
#include "../include/Config.hpp"

#include <filesystem>
#include <vector>
#include <unistd.h>
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

void compile( Binary bin, std::filesystem::path dest) { // this funcion would get me fired because im pretending this is c
    std::vector< pid_t > child_pids;
    std::vector< int > child_stat;
    int iterator = 0;
    for ( std::string src : bin.sources ) {

        std::string command;
        
        // never used the heap before
        char **pRealCommandUnsafe = new char*[ 3 + bin.args.size() ];
        pRealCommandUnsafe[ 0 ] = ( char * ) bin.CC.c_str();
        
        int i;
        for ( i = 1; i < bin.args.size(); i++ ) {
            // someone is going to kill me over this, but fuck why not
            pRealCommandUnsafe[ i ] = ( char* ) bin.args[ i - 1 ].c_str();
        }

        // please don't crash
        pRealCommandUnsafe[ i ] = ( char * ) "-o";
        pRealCommandUnsafe[ ++i ] = ( char * ) std::string( src + ".o" ).c_str();

        child_pids[ iterator ] = fork();

        if ( child_pids[ iterator ] == 0 ) { // fork succeeded, child time
            // YOLO
            exec( ( const char * ) pRealCommandUnsafe[0], ( const char ** ) pRealCommandUnsafe);
        } else if ( child_pids[ iterator ] == -1 ) { // fork failed
            std::cerr << "Fork() Failed, i don't know how what you could do to fix this so you're on your own bud\n";
            exit( 1 );
        } else if ( child_pids[ iterator ] > 0 ) { // fork succeeded, parent time

        }  

        // yay no mem leaks, im not stupid, as long as you don't look at my cast's
        delete[] pRealCommandUnsafe;
        iterator++;
    } // sig for ( std::string src : bin.sources ) {


    // resize to be the same size as child_pids
    child_stat.resize( child_pids.size() );

    for ( int i = 0; i < child_pids.size(); i++ ) {
        waitpid( child_pids[ i ], &child_stat[ i ] );
        if ( WIFEXITED( child_stat[ i ] ) ) {
            if ( WEXITSTATUS != 0 ) {
                std::cerr << "";
            }
        }
    }
    std::cout << "Compilation finished\n";
}

void build( std::vector< ConfigValue > config /* not parsed yet */) { // config at this point is only tokenized, not parsed

}

int main( int argc, char **argv ) {
    CmdlineArgs args = parseArgs( argc, argv ); // parse command line args
    ConfigManager configMgr( args.file ); // tokenize config and create object
    build( configMgr.getConfiguration( args.config ) ); // start build process, given tokenized non-parsed data.
    return 0;
}