#include <string>
#include <map>
#include <vector>

typedef std::pair< std::string, std::vector< std::string > > ConfigValue;
//                     ^ keyword    ^ arguments  ^ argument 

class Config {
public:
    Config( std::string file_path );

    // returns by value
    const std::vector< ConfigValue > getConfiguration( std::string configName );

private:
    // i hate this
    // anyway, vector of pairs, each pair has a string (config keyword), and a vector of strings (keyword arguments)
    std::vector< ConfigValue > rawConfigValues;

    std::map<std::string, std::vector< ConfigValue > > configurations;
};

