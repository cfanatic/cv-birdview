#include "configuration.hpp"

Configuration::Configuration() :
    m_ptree(new boost::property_tree::ptree())
{
    std::string path = getenv("HOME") + std::string("/Library/Birdview/config.ini");
    boost::property_tree::ini_parser::read_ini(path, *m_ptree);
    this->load();
}

Configuration::~Configuration()
{
    delete m_ptree;
}

void Configuration::load()
{
    load(m_parameters);
}

void Configuration::load(Configuration::settings &parameter)
{
    parameter.path_input = m_ptree->get<std::string>("Path.input");
    parameter.path_output = m_ptree->get<std::string>("Path.output");
}

bool Configuration::valid()
{
    bool check = m_parameters.path_input.empty() || m_parameters.path_output.empty();

    return !check;
}

std::string Configuration::get(const fields &parameter)
{
    std::string value;

    switch (parameter)
    {
        case INPUT: value = m_parameters.path_input; break;
        case OUTPUT: value = m_parameters.path_output; break;
    }

    return value;
}

void Configuration::set(const fields &parameter, std::string value)
{
    switch (parameter)
    {
        case INPUT: m_parameters.path_input = value; break;
        case OUTPUT: m_parameters.path_output = value; break;
    }
}

void Configuration::debug()
{
    std::cout << "path_input:\t\t" << m_parameters.path_input;
    std::cout << "path_output:\t\t" << m_parameters.path_output;
}