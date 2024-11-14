#include "../include/Helper.hpp"
#include "../include/ConfigManager.hpp"
#include "../include/Config.hpp"

#include <filesystem>
#include <vector>
#include <iostream>
#include <unistd.h>
#include <cstdlib>
#include <sys/wait.h>
#include <string>

void helper::compile( Binary bin, std::filesystem::path dest) { // this funcion would get me fired because im pretending this is c
    std::vector< pid_t > child_pids;
    std::vector< int > child_stat;
    int iterator = 0;
    for ( std::filesystem::path src : bin.sources ) {
        std::filesystem::path objPath( dest / "objects/" );
        
        if ( std::filesystem::exists( objPath / ( src.filename().concat( ".o" ) ) ) ) {
            // check if it is newer than source file
        }

        

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
            execvp( ( const char * ) pRealCommandUnsafe[0], ( char *const * ) pRealCommandUnsafe);
            exit( 0 ); // unreachable but safety
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
        waitpid( child_pids[ i ], &child_stat[ i ], 0 );
        if ( WIFEXITED( child_stat[ i ] ) ) {
            if ( WEXITSTATUS( child_stat[ i ] ) != 0 ) {
                std::cerr << "error, exit status non zero on compile command" << WEXITSTATUS( child_stat[ i ] ) << "\n";
            }
        }
    }
    std::cout << "Compilation finished\n";
}

void helper::build( std::vector< ConfigValue > config /* not parsed yet */) { // config at this point is only tokenized, not parsed
    /* make the required directories if they don't exist */

    /* build folder */
    if ( !std::filesystem::exists( "./build/" ) ) {
        std::filesystem::create_directory( "./build" );
    }

    /* config specific build folder */
    if ( !std::filesystem::exists( std::filesystem::path( "./build" ) / config[ 0 ].second[ 0 ] ) ) {
        std::filesystem::create_directory( std::filesystem::path( "./build" ) / config[ 0 ].second[ 0 ] ) ;
    }

    /* objects folder for .o files */
    if ( !std::filesystem::exists( std::filesystem::path( "./build./" ) / config[ 0 ].second[ 0 ] / "objects" ) ) {
        std::filesystem::create_directory( std::filesystem::path( "./build./" ) / config[ 0 ].second[ 0 ] / "objects" );
    }

}