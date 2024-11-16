#include "../include/Helper.hpp"
#include "../include/ConfigManager.hpp"
#include "../include/Config.hpp"

#include <cstddef>
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
        
        const std::filesystem::path objFile( objPath / ( src.filename().concat( ".o" ) ) );
        

        if ( std::filesystem::exists( objFile ) ) {
            // check if it is newer than source file
            if ( std::filesystem::last_write_time( objFile ) < std::filesystem::last_write_time( src ) ) { // if objFile is older than source, recompile
                // never used the heap before
                char **pRealCommandUnsafe = new char*[ 4 ];
                pRealCommandUnsafe[ 0 ] = ( char * ) bin.CC.c_str();
                
                int i = 1;
                

                // please don't crash
                pRealCommandUnsafe[ i ] = ( char * ) "-o";
                pRealCommandUnsafe[ ++i ] = ( char * ) std::string( src.generic_string() + ".o" ).c_str();
                pRealCommandUnsafe[ ++i ] = ( char * ) "-c";

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

            }
        }

        

    } // sig for ( std::string src : bin.sources ) {


    // resize to be the same size as child_pids
    child_stat.resize( child_pids.size() );

    for ( int i = 0; i < child_pids.size(); i++ ) {
        waitpid( child_pids[ i ], &child_stat[ i ], 0 );
        if ( WIFEXITED( child_stat[ i ] ) ) {
            if ( WEXITSTATUS( child_stat[ i ] ) != 0 ) {
                std::cerr << "error, exit status non zero on compile command, exit status is [" << WEXITSTATUS( child_stat[ i ] ) << "], pid was " << child_pids[ i ];
            }
        }
    }
    
    std::cout << "Object Compilation finished\n";
    std::cout << "Starting Final Compilation\n";

    char **pRealCommandUnsafe = new char*[ 4 + bin.args.size() + bin.sources.size() ];
    pRealCommandUnsafe[ 0 ] = ( char * ) bin.CC.c_str();
    
    int i = 1;
    for ( i = 1; i < bin.args.size(); i++ ) {
        // someone is going to kill me over this, but fuck why not
        pRealCommandUnsafe[ i ] = ( char* ) bin.args[ i - 1 ].c_str();
    }
    for ( auto src : bin.sources ) {
        pRealCommandUnsafe[ i ] = ( char * ) src.concat(".o").filename().c_str();
        i++;
    }

    pRealCommandUnsafe[ i ] = ( char * ) "-o";
    pRealCommandUnsafe[ ++i ] = ( char * ) bin.name.c_str();

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