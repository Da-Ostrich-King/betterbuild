#include <iostream>
#include <vector>


struct CmdlineArgs {
    bool help;
    std::string config = "default";
    std::vector< std::string > configOpts;
};

CmdlineArgs parseArgs( int argc, char **argv ) {
    CmdlineArgs args;
    for ( int arg; arg < argc; ++arg ) {
        if ( std::string( argv[ arg ] ) == std::string( "--help" ) || 
             std::string( argv[ arg ] ) == std::string( "-h" )) {
            args.help = true;

        } else if ( std::string( argv[ arg ] ) == std::string( "--config" ) ||
                    std::string ( argv[ arg ] ) == std::string( "-c" ) ) {
            args.config = std::string( argv[ ++arg ] );

        } else {
            // if arg is unkown, shove it into configOpts, notify later option is unused before any commands are run
            args.configOpts.emplace_back( argv[ arg ] );

        }
    }

    return args;
}

int main( int argc, char **argv ) {
    CmdlineArgs args = parseArgs( argc, argv );
    std::cout << "Hello World\n";
    return 0;
}