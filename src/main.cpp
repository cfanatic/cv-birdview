#include "configuration.hpp"
#include "birdview.hpp"

using namespace std;

int main(int argc, char *argv[])
{
    // std::cout << "Using OpenCV: " << cv::getBuildInformation() << std::endl;
    // std::cout << "Using Boost: " << BOOST_LIB_VERSION << std::endl;

    Configuration config;

    std::cout << config.get(Configuration::INPUT) << std::endl;
    std::cout << config.get(Configuration::OUTPUT) << std::endl;

    return 0;
}