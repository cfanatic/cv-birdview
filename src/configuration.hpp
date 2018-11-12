#ifndef CONFIGURATION_HPP
#define CONFIGURATION_HPP

#include <iostream>
#include <string>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/ini_parser.hpp>
#include <boost/version.hpp>

class Configuration
{

public:
    struct settings
    {
        std::string path_input;
        std::string path_output;
    };

    enum parameters
    {
        INPUT,
        OUTPUT
    };

    explicit Configuration();
    ~Configuration();

    void load(settings &config);
    void load();
    void save();
    bool exist();
    bool valid();
    std::string get(const parameters &parameter);
    void set(const parameters &parameter, std::string value);
    void debug();

private:
    boost::property_tree::ptree *m_ptree;
    settings m_parameters;
};

#endif // CONFIGURATION_HPP