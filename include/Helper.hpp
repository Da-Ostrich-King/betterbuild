#pragma once

#include "../include/Config.hpp"
#include "ConfigManager.hpp"

#include <filesystem>
#include <vector>


namespace helper {
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

    void compile( Binary bin, std::filesystem::path dest );
    void build( std::vector< ConfigKey > config );
    CmdlineArgs parseArgs( int argc, char **argv );
    void build( std::vector< ConfigKey > config );
}