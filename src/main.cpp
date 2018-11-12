#include "configuration.hpp"
#include "birdview.hpp"

using namespace std;

int main(int argc, char *argv[])
{
    // std::cout << "Using OpenCV: " << cv::getBuildInformation() << std::endl;
    // std::cout << "Using Boost: " << BOOST_LIB_VERSION << std::endl;

    Configuration config;
    config.debug();

    Birdview image;
    image.load(config.get(Configuration::INPUT) + "/a.jpg");
    image.preprocess();
    image.contours();
    image.boundingbox();
    image.debug();

    return 0;
}