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

    enum fields
    {
        INPUT,
        OUTPUT
    };

    explicit Configuration();
    ~Configuration();

public:
    void load(settings &config);
    void load();
    void save();
    bool exist();
    bool valid();
    std::string get(const fields &parameter);
    void set(const fields &parameter, std::string value);
    void debug();

private:
    boost::property_tree::ptree *m_ptree;
    settings m_parameters;
};

#endif // CONFIGURATION_HPP