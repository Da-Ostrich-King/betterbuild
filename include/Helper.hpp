#pragma once

#include "../include/Config.hpp"
#include "ConfigManager.hpp"

#include <filesystem>


namespace helper {
    void compile( Binary bin, std::filesystem::path dest);
    void build( std::vector< ConfigValue > config );
}