#pragma once

#include <filesystem>
#include <filesystem>
#include <vector>
#include <string>

class Binary {
public:
    Binary( std::string name, std::string CC, std::vector< std::string > args, std::vector< std::filesystem::path > sources);
    ~Binary();


    std::string name;
    std::string CC;
    std::vector< std::filesystem::path > sources;
    std::vector< std::string > args;
private:

};


class Config {
public:
    Config();
    ~Config();
    void addBinary( Binary bin );
    const Binary getBinary( int index );

private:
    std::vector< Binary > bins;
};